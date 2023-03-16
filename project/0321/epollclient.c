#include<unistd.h>
#include <sys/epoll.h>
#include"include/util.h"
#include "include/epoll.h"
#include "include/client.h"
#include "include/network.h"

int main(int argc, char *argv[]) {

    int server_socket;
    int epfd;

    if (argc != 2) {
        error_handling("닉네임을 입력 해주세요");
    }

    //네트워크 연결
    server_socket = network_setup(client_network, argv[1]);

    epfd = epoll_create(EPOLL_SIZE);
    create_add_event(epfd, server_socket, EPOLLIN);
    create_add_event(epfd, STDIN_FILENO, EPOLLIN);

    //TODO EPOLL에다가 EPOLLOUT이벤트를 붙여서 처리하는 방법
    // EPOLLOUT의 경우에는 네트워크 버퍼가 비어있을경우 이벤트를 발생 시킨다.



    event_loop(client_epoll, server_socket, epfd);
}
