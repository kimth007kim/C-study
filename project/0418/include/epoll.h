


struct epoll_event *generate_event(int fd, int event);

void create_add_event(int epfd, int fd, int event);

void event_loop(void(*func)(int, int, struct epoll_event), int server_socket, int epfd);

int check_event(int epfd, int fd_to_check, int event);

void create_modify_event(int epfd, int fd, int event);