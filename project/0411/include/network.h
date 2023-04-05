
void accept_socket(int epfd, int server_socket);

int socket_setup(void(*endpoint_setup)(struct sockaddr_in, int, char *), char *name);

void set_nonblocking_fd(int fd);