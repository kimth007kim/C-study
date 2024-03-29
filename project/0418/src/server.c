#include<sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "../include/util.h"
#include "../include/server.h"
#include "../include/epoll.h"
#include "../include/user.h"
#include "../include/server_io.h"
#include "../include/network.h"
#include "../include/nonblocking_io.h"

/**
 *
 * @param server_socket server_socket은 서버의 경우 자기 자신을 의미합니다. 이것을 토대로 연결요청인지, 아니면 클라이언트와의 통신인지 구별합니다.
 * @param epfd          epfd는 epollevent를 감지하는 fd입니다.
 * @param fd            fd 는 이벤트가 발생한 fd를 가리킵니다.
 *
 */

int server_init = 0;

void server_epoll(int server_socket, int epfd, struct epoll_event event) {
    if (server_init == 0) {
        server_init = 1;
    }
    if (event.events & EPOLLOUT) {
        // epoll 에서 감시하는 이벤트중에서 EPOLLOUT의 이벤트가 발생 했을경우
        server_nio_write(SERVER, epfd, user_list[event.data.fd]->fd);
    } else {
        if (server_socket == event.data.fd) {
            // 서버 소켓으로 수신된 데이터가 존재한다는것은 연결 요청(connect)이 있다는 것이다.
            accept_socket(epfd, server_socket);
        } else {
            // 클라이언트 소켓으로 부터 수신된 데이터가 존재한다는것.
            server_nio_read_parse(SERVER, epfd, event.data.fd,
                                  user_list[event.data.fd]->read_buffer,
                                  &user_list[event.data.fd]->read_offset,
                                  &user_list[event.data.fd]->read_current_idx,
                                  &user_list[event.data.fd]->read_status);
        }
    }
    delay_check(server_socket, epfd);


}

void server_network(struct sockaddr_in server_address, int server_socket) {
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

void delay_check(int server_socket, int epfd) {
    Node *traverse_user_link = user_link;

    for (int i = 0; i < MAX_USERS; i++) {
        struct user *this_user = user_list[i];
        if (this_user == NULL) {
            continue;
        }
        if (this_user->read_delay_time > 5 || this_user->write_delay_time > 5) {
            exit_user(epfd, i);
        }
    }
}
