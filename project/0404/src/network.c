//
// Created by kim on 23. 3. 16.
//


#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include "../include/util.h"
#include "../include/epoll.h"
#include "../include/user.h"


void set_nonblocking_fd(int fd) {
    int flag = fcntl(fd, F_GETFL, 0);
    fcntl(F_SETFL, flag | O_NONBLOCK);
}

int network_setup(void(*node_network)(struct sockaddr_in, int, char *), char *name) {
    int server_socket;
    struct sockaddr_in server_address;

    server_socket = socket(PF_INET, SOCK_STREAM, 0);

    set_nonblocking_fd(server_socket);

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = PORT_NUM;

    node_network(server_address, server_socket, name);

    return server_socket;
}

void accept_socket(int epfd, int server_socket) {
    socklen_t address_size;
    int client_socket;
    struct sockaddr_in client_address;

    address_size = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *) &client_address, &address_size);
    set_nonblocking_fd(client_socket);
    if (client_socket == -1) {
        puts("accept() error!");
        exit(1);
    }
    create_add_event(epfd, client_socket, EPOLLIN);
    enter_user(client_socket);


}