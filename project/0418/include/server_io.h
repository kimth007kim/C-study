#include "../include/protocol.h"
#include "../include/user.h"
#include <sys/epoll.h>

void destination_handler(int fd, int epfd, struct protocol *protocol_ptr, char *message, int *message_offset ,int * current_read_idx);

void broadcast_handler(int fd, int epfd, struct protocol *protocol_ptr, char *message, int *message_offset,int * current_read_idx);

void enter_handler(int fd, int epfd, struct protocol *protocol_ptr, char *message, int *message_offset,int * current_read_idx);

void exit_handler(int fd, int epfd, struct protocol *protocol_ptr, char *message, int *message_offset,
                  int *current_read_idx);

//void server_write(int host_type, int epfd, int fd);
void server_nio_write(int host_type, int epfd, int fd);