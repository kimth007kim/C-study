#include<sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include "../include/util.h"
#include "../include/protocol.h"
#include "../include/server.h"
#include "../include/epoll.h"
#include "../include/user.h"
#include "../include/chat.h"
#include "../include/network.h"

#define REQUIRE_HEADER 0
#define REQUIRE_BODY 1


/**
 *
 * @param server_socket server_socket은 서버의 경우 자기 자신을 의미합니다. 이것을 토대로 연결요청인지, 아니면 클라이언트와의 통신인지 구별합니다.
 * @param epfd          epfd는 epollevent를 감지하는 fd입니다.
 * @param fd            fd 는 이벤트가 발생한 fd를 가리킵니다.
 * @param read_buf      epoll_event가 발생할때 read_buf도 받습니다. 서버에서는 read_buf가 사용되지않습니다.
 * @param write_buf     epoll_event가 발생할때 write_buf도 받습니다. 서버에서는 write_buf가 사용되지않습니다.
 * @param read_length   epoll_event가 발생할때 read_length 받습니다. 서버에서는 read_length 가 사용되지않습니다.
 */
void
server_epoll(int server_socket, int epfd, struct epoll_event event, char *read_buf, char *write_buf, int *read_length,
             int *protocol_read,int *read_status) {
    socklen_t address_size;
    int read_cnt;
    int client_socket;
    struct sockaddr_in client_address;
    struct protocol *new_protocol = malloc(sizeof(struct protocol));
    int fd = event.data.fd;
    struct user *user_ptr = user_list[fd];

    if (event.events == EPOLLOUT) {
        //epoll 에서 감시하는 이벤트중에서 EPOLLOUT의 이벤트가 발생 했을경우
        chat(fd, epfd, NULL, user_ptr, 0);
    } else {
        //epoll 에서 감시하는 이벤트중에서 EPOLLIN의 이벤트가 발생 했을경우

        if (server_socket == fd) {
            // 서버 소켓으로 수신된 데이터가 존재한다는것은 연결 요청(connect)이 있다는 것이다.

            address_size = sizeof(client_address);
            client_socket = accept(server_socket, (struct sockaddr *) &client_address, &address_size);
            set_nonblocking_fd(client_socket);
            if (client_socket == -1) {
                puts("accept() error!");
                exit(1);
            }
            create_add_event(epfd, client_socket, EPOLLIN);
            enter_user(client_socket);
        } else {
            // 클라이언트 소켓으로 부터 수신된 데이터가 존재한다는것.
            read_cnt = read(fd, user_list[fd]->read_buf + user_list[fd]->end_offset, BUF_SIZE);

            if (read_cnt < 0) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    return;
                } else {
                    error_handling("read()시 에러 발생");
                }

            } else if (read_cnt == 0) {
                epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                exit_user(fd);
                return;
            }

            int total_read = read_cnt + user_ptr->end_offset - user_ptr->start_offset;
            user_ptr->end_offset += total_read;


            while (total_read > 0) {
                if (user_ptr->read_status == REQUIRE_HEADER) {
                    if (total_read < 8) {
                        return;
                    } else {
                        memset(new_protocol, 0, sizeof(struct protocol));
                        char temp_length[5];

                        strncpy(temp_length, user_ptr->read_buf + user_ptr->start_offset, 4);
                        temp_length[4] = '\n';
                        int total_length = atoi(temp_length);
                        user_ptr->start_offset += 4;
                        new_protocol->message_length = total_length;


                        new_protocol->destination = user_ptr->read_buf + user_ptr->start_offset;
                        user_ptr->start_offset += 4;
                        user_ptr->read_status = REQUIRE_BODY;

                        memset(temp_length, 0, 5);

                        total_read -= 8;
                    }
                } else {
                    if (total_read < new_protocol->message_length) {
                        return;
                    } else {
                        char temp_message[BUF_SIZE];
//                        strncpy(temp_message, user_ptr->read_buf + user_ptr->start_offset,
//                                new_protocol->message_length);

                        new_protocol->message = user_ptr->read_buf + user_ptr->start_offset;
                        user_ptr->start_offset += new_protocol->message_length;
                        total_read -= new_protocol->message_length;
                        user_ptr->read_status = REQUIRE_HEADER;

//                        read가 끝나고 나면 write를 하도록 한다.
                        chat(fd, epfd, new_protocol, user_ptr, 0);
                        switch_buffer(user_ptr);

                    }

                }
            }

        }
    }
}

void server_network(struct sockaddr_in server_address, int server_socket, char *name) {
    int option = 1;
    int option_len = sizeof(option);
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (void *) &option, option_len);


    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        error_handling("bind() error");
    }

    if (listen(server_socket, MAX_USERS) == -1) {
        error_handling("listen() error");
    }
}

void switch_buffer(struct user *user) {
    char *new_buf = malloc(BUF_SIZE);
    memset(new_buf, 0, BUF_SIZE);
    int idx = 0;
    for (int i = user->start_offset; i < user->end_offset; i++) {
        new_buf[idx] = user->read_buf[i];
        idx++;
    }
    memcpy(user->read_buf + user->start_offset, new_buf, user->end_offset - user->start_offset);
    user->start_offset = 0;
    user->end_offset = idx;
    free(new_buf);

}