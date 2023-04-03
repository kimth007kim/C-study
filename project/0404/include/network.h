
void accept_socket(int epfd, int server_socket);

int network_setup(void(*node_network)(struct sockaddr_in, int, char *), char *name);

void set_nonblocking_fd(int fd);