#include <netinet/in.h>
#include <arpa/inet.h>

void client_epoll(int server_socket, int epfd, struct epoll_event event, char *name);

void client_network(struct sockaddr_in server_address, int server_socket, char *name);

void init_global_vars();

void client_hello(int epfd, int fd, char *name, int *write_offset);