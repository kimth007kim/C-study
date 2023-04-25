#include <netinet/in.h>
#include <arpa/inet.h>


void server_epoll(int server_socket, int epfd, struct epoll_event event);

void server_network(struct sockaddr_in server_address, int server_socket);


void delay_check(int server_socket, int epfd) ;
