//
// Created by kim on 23. 3. 16.
//


#include <string.h>
#include <arpa/inet.h>
#include "../include/util.h"


int network_setup(void(*node_network)(struct sockaddr_in, int, char *), char *name) {
    int server_socket;
    struct sockaddr_in server_address;

    server_socket = socket(PF_INET, SOCK_STREAM, 0);

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = PORT_NUM;

    node_network(server_address, server_socket, name);

    return server_socket;
}