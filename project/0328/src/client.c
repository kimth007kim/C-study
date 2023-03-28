#include<sys/epoll.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <errno.h>
#include "../include/util.h"
#include "../include/protocol.h"
#include "../include/linkedlist.h"
#include "../include/client.h"
#include "../include/epoll.h"


/**
 *
 * @param server_socket server_socket은 서버의 경우 자기 자신을 의미합니다. 이것을 토대로 stdin인지 , 아니면 서버와의 통신인지 구별합니다.
 * @param epfd          epfd는 epollevent를 감지하는 fd입니다.
 * @param fd            fd 는 이벤트가 발생한 fd를 가리킵니다.
 * @param read_buf      epoll_event가 발생할때 read_buf도 받습니다.
 * @param write_buf     epoll_event가 발생할때 write_buf도 받습니다.
 * @param read_length   epoll_event가 발생할때 read_length 받습니다. read_buf에서 어디까지 읽었는지 기록하기위한 변수입니다.
 */

int number = 0;
int start_offset = 0;
int end_offset = 0;
int target_length;
int write_cnt;
int read_cnt;

char *protocol;

#define REQUIRE_HEADER 0
#define REQUIRE_BODY 1

//void client_epoll(int server_socket, int epfd, int fd, char *read_buf, char *write_buf, int *read_length) {
void
client_epoll(int server_socket, int epfd, struct epoll_event event, char *read_buf, char *write_buf, int *read_length,
             int *protocol_read, int *read_status) {
    errno = 0;
    int fd = event.data.fd;
    struct protocol *new_protocol = malloc(sizeof(struct protocol));

    printf("전역변수 number = %d \n", number);

    if (event.events == EPOLLOUT) {
        write_cnt = write(server_socket, protocol, target_length);
        if (write_cnt < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return;
            } else {
                error_handling("write() error");
            }
        } else if (write_cnt < target_length) {
            target_length -= write_cnt;

        } else if (write_cnt == target_length) {
            memset(read_buf, 0, sizeof(read_buf));
            *read_length = 0;
            number += 1;
            printf("올라간 전역변수 number = %d \n", number);
            struct epoll_event ev;
            ev.events = EPOLLOUT;
            epoll_ctl(epfd, EPOLL_CTL_DEL, server_socket, &ev);
        }

    } else {

        if (server_socket == fd) {
//            memset(write_buf, 0, sizeof(write_buf));
//            read_cnt = read(server_socket, write_buf, BUF_SIZE);
//
//
//            printf("read 후에 errno 호출 = %d   EAGAIN의 값 = %d\n", errno, EAGAIN);
//
//            if (read_cnt < 0) {
//                if (errno == EAGAIN || errno == EWOULDBLOCK) {
//                    return;
//                } else {
//                    error_handling("read()시 에러 발생");
//                }
//            } else if (read_cnt == 0) {
//                epoll_ctl(epfd, EPOLL_CTL_DEL, server_socket, NULL);
//                close(server_socket);
//                exit(1);
//            }
//
//            write_buf[read_cnt] = '\n';
//            fputs(write_buf, stdout);
//            memset(write_buf, 0, sizeof(write_buf));
            read_cnt = read(server_socket, write_buf, BUF_SIZE);

            if (read_cnt < 0) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    return;
                } else {
                    error_handling("read()시 에러 발생");
                }

            } else if (read_cnt == 0) {
                epoll_ctl(epfd, EPOLL_CTL_DEL, server_socket, NULL);
                close(server_socket);
                exit(1);
            }

            *protocol_read += read_cnt;
            while (*protocol_read > 0) {
                if (*read_status == REQUIRE_HEADER) {
                    if (*protocol_read < 8) {
                        return;
                    } else {
                        memset(new_protocol, 0, sizeof(struct protocol));
                        char temp_length[5];

                        strncpy(temp_length, write_buf, 4);
                        temp_length[4] = '\n';
                        int total_length = atoi(temp_length);
                        new_protocol->message_length = total_length;


//                new_protocol->destination = user_ptr->read_buf + user_ptr->start_offset;
//                user_ptr->start_offset += 4;
//                user_ptr->read_status = REQUIRE_BODY;

                        memset(temp_length, 0, 5);

                        *protocol_read -= 8;
                    }
                } else {
                    if (*protocol_read < new_protocol->message_length) {
                        return;
                    } else {
                        char temp_message[BUF_SIZE];

                        new_protocol->message = write_buf + 8;
//                        user_ptr->start_offset += new_protocol->message_length;
                        *protocol_read -= new_protocol->message_length;
                        *read_status = REQUIRE_HEADER;

//                        read가 끝나고 나면 write를 하도록 한다.
                        fputs(write_buf, stdout);
                        printf("write_buf: %s\n",write_buf);
                        memset(write_buf, 0, sizeof(write_buf));

                    }

                }

            }
        } else {
            char temp;
            read_cnt = read(STDIN_FILENO, &temp, 1);


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
                if (temp != '\n' && *read_length < BUF_SIZE - 1) {
                    read_buf[*read_length] = temp;
                    *read_length += 1;
                    return;
                }
                read_buf[*read_length] = '\n';
                protocol = encode_protocol(read_buf, 0);
                char *output = malloc(1000);
//            encode_kd_protocol(read_buf, 0,output);
                printf("%s\n", output);

                //여기서 일단 write 를 합니다.
                target_length = strlen(protocol);

                write_cnt = write(server_socket, protocol, strlen(protocol));

                if (write_cnt < 0) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        // 이미 이벤트가 확인하는 작업
//                        if (check_event(epfd, server_socket, EPOLLOUT) == 0) {
                        struct epoll_event ev;
                        ev.events = EPOLLOUT;
                        epoll_ctl(epfd, EPOLL_CTL_ADD, server_socket, &ev);
//                        }
                        return;
                    } else {
                        error_handling("write() error");
                    }
                } else if (write_cnt < target_length) {
                    target_length -= write_cnt;
                    struct epoll_event ev;
                    ev.events = EPOLLOUT;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, server_socket, &ev);

                } else {
                    memset(read_buf, 0, sizeof(read_buf));
                    *read_length = 0;
                    number += 1;
                    printf("올라간 전역변수 number = %d \n", number);

                }

            }
        }

    }


}

void client_network(struct sockaddr_in server_address, int server_socket, char *name) {
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (server_socket == -1) {
        error_handling("socket() error");
    }
    if (connect(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        error_handling("connect error");
    } else {
        puts("Connected");
        write(server_socket, name, strlen(name));
    }
}