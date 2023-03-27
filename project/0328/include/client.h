#include <netinet/in.h>
#include <arpa/inet.h>

//void client_epoll(int server_socket, int epfd, int fd, char *read_buf, char *write_buf, int *read_length);
void client_epoll(int server_socket, int epfd, struct epoll_event event, char *read_buf, char *write_buf, int *read_length);

void client_network(struct sockaddr_in server_address, int server_socket, char *name);