#include "../include/protocol.h"
#include "../include/user.h"

void broadcast_error_handling(char *message, int fd);

void switch_write_buf(struct user *user);

void chat(int fd, int epfd, struct protocol *protocol_ptr, struct user *user_ptr, int read_again);

void broadcast_mode(int fd, int epfd, struct protocol *protocol_ptr, struct user *user_ptr, int read_again);

void set_write_buf(int fd, int epfd, struct protocol *protocol_ptr);

void write_nonblocking(int fd, int epfd, struct epoll_event event);

void whisper_mode();

void command_mode();