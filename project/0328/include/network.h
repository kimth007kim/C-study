

void node_network(struct sockaddr_in server_address, int server_socket, char *name);

int network_setup(void(*node_network)(struct sockaddr_in, int, char *), char *name);
