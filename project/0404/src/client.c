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


#define REQUIRE_HEADER 0
#define REQUIRE_BODY 1

#define REQUIRE_INIT 0
#define ALREADY_INIT 1
/**
 *
 * @param server_socket server_socket은 서버의 경우 자기 자신을 의미합니다. 이것을 토대로 stdin인지 , 아니면 서버와의 통신인지 구별합니다.
 * @param epfd          epfd는 epollevent를 감지하는 fd입니다.
 * @param fd            fd 는 이벤트가 발생한 fd를 가리킵니다.
 *
 */

int init_flag = REQUIRE_INIT;
int read_status = REQUIRE_HEADER;
int target_length = 0;
int write_cnt = 0;
int read_cnt = 0;
int protocol_read = 0;
int read_offset = 0;
int write_length = 0;
char *protocol;


char *write_buf;
char *read_buf;

//void client_epoll(int server_socket, int epfd, int fd, char *read_buf, char *write_buf, int *write_length) {
void
client_epoll(int server_socket, int epfd, struct epoll_event event) {
    if (init_flag == REQUIRE_INIT) {
        read_buf = malloc(BUF_SIZE);
        write_buf = malloc(BUF_SIZE);
        init_flag = ALREADY_INIT;
    }

    errno = 0;
    int fd = event.data.fd;
    struct protocol *new_protocol = malloc(sizeof(struct protocol));

    if (event.events & EPOLLOUT) {
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
            memset(read_buf, 0, sizeof(write_buf));
            write_length = 0;
            struct epoll_event ev;
            ev.events = EPOLLIN;
            epoll_ctl(epfd, EPOLL_CTL_MOD, server_socket, &ev);
        }

    } else {
        if (server_socket == fd) {
            read_cnt = read(server_socket, read_buf, BUF_SIZE);
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
            protocol_read += read_cnt;
            while (protocol_read > 0) {
                if (read_status == REQUIRE_HEADER) {
                    if (protocol_read < 8) {
                        return;
                    } else {
                        memset(new_protocol, 0, sizeof(struct protocol));
                        char temp_length[5];

                        strncpy(temp_length, read_buf, 4);
                        temp_length[4] = '\n';
                        int total_length = atoi(temp_length);
                        new_protocol->message_length = total_length;

                        read_status = REQUIRE_BODY;
                        memset(temp_length, 0, 5);
                        read_offset += 8;
                        protocol_read -= 8;
                    }
                } else {
                    if (protocol_read < new_protocol->message_length) {
                        return;
                    } else {
                        char *output_message = malloc(BUF_SIZE);

                        new_protocol->message = read_buf + 8;


                        sprintf(output_message, "%.*s", new_protocol->message_length, new_protocol->message);
                        fputs(output_message, stdout);
                        protocol_read -= new_protocol->message_length;
                        read_offset += new_protocol->message_length;
                        switch_read_buf(read_buf, &read_offset);
                        read_status = REQUIRE_HEADER;

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
                if (temp != '\n' && write_length < BUF_SIZE - 1) {
                    write_buf[write_length] = temp;
                    write_length += 1;
                    return;
                }
                write_buf[write_length] = '\n';
                protocol = encode_protocol(write_buf, 0);

                //여기서 일단 write 를 합니다.
                target_length = strlen(protocol);

                write_cnt = write(server_socket, protocol, strlen(protocol));

                if (write_cnt < 0) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        struct epoll_event ev;
                        ev.events |= EPOLLOUT;
                        ev.data.fd = server_socket;
                        epoll_ctl(epfd, EPOLL_CTL_ADD, server_socket, &ev);
//                        }
                        return;
                    } else {
                        error_handling("write() error");
                    }
                } else if (write_cnt < target_length) {
                    target_length -= write_cnt;
                    struct epoll_event ev;
                    ev.events |= EPOLLOUT;
                    ev.data.fd = server_socket;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, server_socket, &ev);


                } else {
                    memset(write_buf, 0, sizeof(write_buf));
                    write_length = 0;

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

//
void switch_read_buf(char *read_buf, int *read_offset) {

    char *new_buf = malloc(BUF_SIZE);
    int new_length = strlen(read_buf) - *read_offset;
    strncpy(new_buf, read_buf + *read_offset, new_length);
    memset(read_buf, 0, BUF_SIZE);
    strncpy(read_buf, new_buf, new_length);
    *read_offset = new_length;
}
