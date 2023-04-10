#include<errno.h>
#include "../include/util.h"
#include "../include/protocol.h"
#include "../include/chat.h"
#include "../include/nonblocking_io.h"
#include "../include/epoll.h"
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>

void server_write(int host_type, int epfd, int fd, char *write_buf, int *write_offset, char *broadcast_buf,
                  int *broadcast_offset) {
    Ptr_node *current_node = ptrnode_link;
    struct user *this_user;
    this_user = user_list[fd];


    int write_cnt = n_write(host_type, epfd, fd, this_user->char_start);
    char *changed_char_start = this_user->char_start + write_cnt;
//    while (current_node != NULL) {
//
//        if (current_node->char_ptr <= this_user->char_start) {
//            current_node = current_node->next;
//            continue;
//        } else if (current_node->char_ptr > changed_char_start) {
//            break;
//        } else if (this_user->char_start < current_node->char_ptr && current_node->char_ptr <= changed_char_start) {
//            current_node->cnt -= 1;
//            current_node = current_node->next;
//        }
//
//    }
//    this_user->char_start = changed_char_start;
    while (current_node != NULL) {
        if (current_node->char_ptr <= this_user->char_start) {
            current_node = current_node->next;
            continue;
        } else if (current_node->char_ptr > changed_char_start) {
            break;
        } else if (this_user->char_start < current_node->char_ptr && current_node->char_ptr <= changed_char_start) {
            current_node->cnt -= 1;
            if (current_node->cnt == 0) {
                // remove the current_node from the linked list
                Ptr_node *prev_node = NULL;
                Ptr_node *temp_node = ptrnode_link;
                while (temp_node != NULL && temp_node != current_node) {
                    prev_node = temp_node;
                    temp_node = temp_node->next;
                }
                if (prev_node == NULL) {
                    // current_node is the head node
                    ptrnode_link = current_node->next;
                } else {
                    // current_node is not the head node
                    prev_node->next = current_node->next;
                }
                int broadcast_length = strlen(broadcast_buf);
                memmove(broadcast_buf, current_node->char_ptr, broadcast_length-strlen(current_node->char_ptr));
                free(current_node);
                current_node = (prev_node == NULL) ? ptrnode_link : prev_node->next;
            } else {
                current_node = current_node->next;
            }
        }
    }
    this_user->char_start = changed_char_start;
}

int n_write(int host_type, int epfd, int fd, char *write_buf) {


    int target_length = strlen(write_buf);
    int write_cnt = write(fd, write_buf, target_length);
//    user_list[fd]->char_start = write_buf;
    if (write_cnt <= 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        } else {
            error_handling("write() error");
        }

    } else if (write_cnt == target_length) {
        create_modify_event(epfd, fd, EPOLLIN);
    }
    return write_cnt;
}

int nio_write(int host_type, int epfd, int fd, char *write_buf, int *write_offset) {
    int target_length = strlen(write_buf);
    int write_cnt = write(fd, write_buf, target_length);

    if (write_cnt <= 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        } else {
            error_handling("write() error");
        }
    } else if (write_cnt < target_length) {
        switch_buffer(write_buf, write_offset);
    } else {
        switch_buffer(write_buf, write_offset);
        create_modify_event(epfd, fd, EPOLLIN);
    }
    return write_cnt;
}

int nio_read(int host_type, int epfd, int fd, char *buf, int *offset) {
    int read_cnt = read(fd, buf + *offset, BUF_SIZE);


    if (read_cnt < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        } else {
            error_handling("read()시 에러 발생");
        }
    } else if (read_cnt == 0) {
        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
        if (host_type == SERVER) {
            exit_user(fd);
            return 0;
        } else if (host_type == CLIENT) {
            close(fd);
            exit(1);
        }
    }
    return read_cnt;
}

void nio_read_stdin(int epfd, int fd, char *client_buf, char *write_buf, int *write_offset,
                    int *registered) {
    int offset = 0;
    int read_cnt = nio_read(CLIENT, epfd, STDIN_FILENO, client_buf, &offset);
    char *new_protocol = malloc(BUF_SIZE);
    if (*registered == FALSE) {
        new_protocol = encode_protocol(client_buf, CHAR_REGISTER, 9999);
        *registered = TRUE;
    } else {
        new_protocol = encode_protocol(client_buf, CHAR_BROADCAST, 9999);
    }
    int target_length = strlen(new_protocol);
    //new_protocol write_buf에 write_offset이후에 copy 하기
    strncpy(write_buf + *write_offset, new_protocol, target_length);
    memset(client_buf, 0, BUF_SIZE);
    *write_offset += target_length;
    // TODO client_buf 에 복사 하기.
    create_modify_event(epfd, fd, EPOLLIN | EPOLLOUT);
}


void
nio_read_parse(int host_type, int epfd, int fd, char *read_buf, int *read_offset, int *read_status, char *broadcast_buf,
               int *broadcast_offset) {
    struct protocol *new_protocol = malloc(sizeof(struct protocol));
    int protocol_read = 0;
    int read_cnt = nio_read(host_type, epfd, fd, read_buf, read_offset);
    protocol_read += read_cnt;
    handle_protocol_decoding(host_type, epfd, fd, new_protocol, &protocol_read, read_status,
                             read_offset,
                             read_buf, broadcast_buf, broadcast_offset);

}
