#include "../include/protocol.h"
#include "../include/user.h"
#include <sys/epoll.h>

void set_broadcast_write_buf(int fd, int epfd, struct protocol *protocol_ptr);
