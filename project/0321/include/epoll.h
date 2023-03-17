


struct epoll_event *generate_event(int fd, int event);

void create_add_event(int epfd, int fd, int event);

//
//void server_epoll(int flag, int server_socket, int epfd, int fd, char *read_buf, char *write_buf);
//
//void client_epoll(int flag, int server_socket, int epfd, int fd, char *read_buf, char *write_buf);

void event_loop(void(*func)(int, int, int, int, char *, char *,int *), int server_socket, int epfd);
