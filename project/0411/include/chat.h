#include "../include/protocol.h"
#include "../include/user.h"
#include <sys/epoll.h>

void destination_handler(int fd, int epfd, struct protocol *protocol_ptr, char *broadcast_buf, int *broadcast_offset);

void broadcast_handler(int fd, int epfd, struct protocol *protocol_ptr, char *broadcast_buf, int *broadcast_offset);

void enter_handler(int fd, int epfd, struct protocol *protocol_ptr, char *broadcast_buf, int *broadcast_offset);