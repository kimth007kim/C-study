#include <netinet/in.h>
#include <arpa/inet.h>


void server_epoll(int server_socket, int epfd, int fd, char *read_buf, char *write_buf, int *read_length);

void server_network(struct sockaddr_in server_address, int server_socket, char *name);

