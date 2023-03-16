#include<sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include "../include/util.h"
#include "../include/protocol.h"
#include "../include/server.h"
#include "../include/epoll.h"
#include "../include/user.h"

void server_epoll(int flag, int server_socket, int epfd, int fd, char *read_buf, char *write_buf) {
    socklen_t address_size;
    int str_len = 0;
    int client_socket;
    int client_address;
    char * greeting;
    if (flag == 0) {
        address_size = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr *) &client_address, &address_size);
        if (client_socket == -1) {
            puts("accept() error!");
            return;
        }
        create_add_event(epfd, client_socket, EPOLLIN);
        enter_user(client_socket);
        greeting=generate_greeting(client_socket, 0);
    } else {
        str_len = read(fd, read_buf, BUF_SIZE);
        if (str_len == 0) {
            // Ctrl + c 로 인한 종료 요청
            greeting =generate_greeting(fd, 1);

            epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
            exit_user(fd);


        } else {
            //TODO 프로토콜을 파싱하는 함수를 만들고, 파싱한 정보를 토대로 분기 처리
//            struct protocol *new_protocol = decode_protocol(fd, read_buf);
            generate_message(fd, read_buf);
            memset(read_buf, 0, sizeof(read_buf));
        }

    }
}

void server_network(struct sockaddr_in server_address, int server_socket, char *name) {
    int option = 1;
    int option_len= sizeof(option);
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (void *) &option, option_len);



    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        error_handling("bind() error");
    }

    if (listen(server_socket, MAX_USERS) == -1) {
        error_handling("listen() error");
    }
}