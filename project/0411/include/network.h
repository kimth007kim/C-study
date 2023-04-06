
void accept_socket(int epfd, int server_socket);

int socket_setup(void(*endpoint_setup)(struct sockaddr_in, int));

void set_nonblocking_fd(int fd);