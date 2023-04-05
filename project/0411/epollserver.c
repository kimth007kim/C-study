#include<string.h>
#include<unistd.h>
#include <sys/epoll.h>
#include"include/util.h"
#include "include/epoll.h"
#include "include/server.h"
#include "include/user.h"
#include "include/network.h"

int main() {

    int server_socket;
    int epfd;

    for (int i = 0; i < MAX_USERS; i++) {
        user_list[i] = NULL;
    }

    //네트워크 연결
    server_socket = socket_setup(server_network, NULL);

    epfd = epoll_create(EPOLL_SIZE);
    create_add_event(epfd, server_socket, EPOLLIN);


    //이벤트 루프
    event_loop(server_epoll, server_socket, epfd, NULL);

    close(server_socket);
    return 0;

}
