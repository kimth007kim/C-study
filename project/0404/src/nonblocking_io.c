#include<errno.h>
#include "../include/util.h"
#include "../include/protocol.h"
#include "../include/chat.h"
#include "../include/nonblocking_io.h"
#include "../include/epoll.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <stdlib.h>


void nio_read(int host_type, int epfd, int fd, char *read_buf, int *read_offset, int *read_status) {
    struct protocol *new_protocol = malloc(sizeof(struct protocol));
    int protocol_read = 0;
    int read_cnt = read(fd, read_buf + *read_offset, BUF_SIZE);
    if (read_cnt < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return;
        } else {
            error_handling("read()시 에러 발생");
        }
    } else if (read_cnt == 0) {
        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
        if (host_type == SERVER) {
            exit_user(fd);
            return;
        } else if (host_type == CLIENT) {
            close(fd);
            exit(1);
        }
    }
    protocol_read += read_cnt;
    while (protocol_read > 0) {
        if (*read_status == REQUIRE_HEADER) {
            if (protocol_read < 8) {
                return;
            } else {
                memset(new_protocol, 0, sizeof(struct protocol));
                char temp_length[5];

                strncpy(temp_length, read_buf, 4);
                temp_length[4] = '\n';
                int total_length = atoi(temp_length);
                new_protocol->message_length = total_length;

                new_protocol->destination = read_buf + 4;
                memset(temp_length, 0, 5);
                *read_offset += 8;
                protocol_read -= 8;
                *read_status = REQUIRE_BODY;
            }
        } else {
            if (protocol_read < new_protocol->message_length) {
                return;
            } else {
                char *output_message = malloc(BUF_SIZE);

                new_protocol->message = read_buf + *read_offset;
                *read_offset += new_protocol->message_length;
                protocol_read -= new_protocol->message_length;

                if (host_type == SERVER) {
                    // TODO 추후에는 프로토콜 을 파싱하는 과정을 거치는것으로 수정해야한다.
                    // 만약에 호출 대상이  서버라면 read() 해온 protocol 을 write_buf 에 복사해주는 역할을 하는 과정을 가진다.
                    destination_handler(fd, epfd, new_protocol);

                } else if (host_type == CLIENT) {
                    // 만약에 호출 대상이 클라이언트 라면 read() 해온 protocl 을 write_buf 에 복사해주는 역할을 하는 과정을 가진다.
                    sprintf(output_message, "%.*s", new_protocol->message_length, new_protocol->message);
                    fputs(output_message, stdout);

                }
                switch_buffer(read_buf, read_offset);
                *read_status = REQUIRE_HEADER;
                *read_offset = 0;

            }
        }
    }
}

void nio_write(int host_type, int epfd, int fd, char *write_buf, int *write_offset) {
    int target_length = strlen(write_buf);
    int write_cnt = write(fd, write_buf, target_length);

    if (write_cnt <= 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return;
        } else {
            error_handling("write() error");
        }
    } else if (write_cnt < target_length) {
        switch_buffer(write_buf, write_offset);
    } else {
        switch_buffer(write_buf, write_offset);
        create_modify_event(epfd, fd, EPOLLIN);
    }
}

void nio_stdin_read(int epfd, int fd, char *client_buf, char *write_buf, int *write_length, int *write_offset) {
    char *new_protocol = malloc(BUF_SIZE);
    char temp;
    int read_cnt = read(STDIN_FILENO, &temp, 1);


    // client_buf-> write_buf로이동
    // client_buf에 문자열 담고 프로토콜 만들어서 write_buf에 담는작업
    if (read_cnt < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return;
        } else {
            error_handling("read()시 에러 발생");
        }
    } else if (read_cnt == 0) {
        epoll_ctl(epfd, EPOLL_CTL_DEL, STDIN_FILENO, NULL);
        close(STDIN_FILENO);
        exit(1);
    } else {
        if (temp != '\n' && *write_length < BUF_SIZE - 1) {
            client_buf[*write_length] = temp;
            *write_length += 1;
            return;
        }
        client_buf[*write_length] = '\n';
        // client 버퍼에서 읽어온것을 토대로 new_protocol 생성완료
        new_protocol = encode_protocol(client_buf, 9999);
        int target_length = strlen(new_protocol);

        //new_protocol write_buf에 write_offset이후에 copy 하기
        strncpy(write_buf + *write_offset, new_protocol, target_length);
        memset(client_buf, 0, BUF_SIZE);
        *write_length = 0;
        *write_offset += target_length;

        // TODO client_buf 에 복사 하기.

        create_modify_event(epfd, fd, EPOLLIN | EPOLLOUT);
    }
}

