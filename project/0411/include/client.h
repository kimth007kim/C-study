#include <netinet/in.h>
#include <arpa/inet.h>
#include "client_message_linkedlist.h"


extern Message_node *message_node_link;

void client_epoll(int server_socket, int epfd, struct epoll_event event);

void client_network(struct sockaddr_in server_address, int server_socket);

void init_global_vars();
