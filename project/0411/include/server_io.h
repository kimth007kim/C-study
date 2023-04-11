#include "../include/protocol.h"
#include "../include/user.h"
#include <sys/epoll.h>

void destination_handler(int fd, int epfd, struct protocol *protocol_ptr);

void broadcast_handler(int fd, int epfd, struct protocol *protocol_ptr);

void enter_handler(int fd, int epfd, struct protocol *protocol_ptr);

void server_write(int host_type, int epfd, int fd);