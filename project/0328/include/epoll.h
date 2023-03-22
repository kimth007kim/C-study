


struct epoll_event *generate_event(int fd, int event);

void create_add_event(int epfd, int fd, int event);

void event_loop(void(*func)( int, int, int, char *, char *,int *), int server_socket, int epfd);
