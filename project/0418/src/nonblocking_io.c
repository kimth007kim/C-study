#include<errno.h>
#include "../include/util.h"
#include "../include/protocol.h"
#include "../include/server_io.h"
#include "../include/nonblocking_io.h"
#include "../include/epoll.h"
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <stdlib.h>

struct protocol *temp_protocol;
int nio_init_flag = 0;

int server_write(int host_type, int epfd, int fd, char *write_buf, int length) {
    int write_cnt = write(fd, write_buf, length);
    if (write_cnt < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        } else {
            error_handling("write() error");
        }
    } else if (write_cnt == length) {

//        create_modify_event(epfd, fd, EPOLLIN);
    }
    return write_cnt;
}

//int nio_write(int host_type, int epfd, int fd, char *write_buf, int *write_offset) {
//    int target_length = strlen(write_buf);
//    int write_cnt = write(fd, write_buf, target_length);
//
//    if (write_cnt <= 0) {
//        if (errno == EAGAIN || errno == EWOULDBLOCK) {
//            return 0;
//        } else {
//            error_handling("write() error");
//        }
//    } else if (write_cnt < target_length) {
//        switch_buffer(write_buf, write_offset);
//    } else {
//        switch_buffer(write_buf, write_offset);
//        create_modify_event(epfd, fd, EPOLLIN);
//    }
//    return write_cnt;
//}

int nio_read(int host_type, int epfd, int fd, char *buf, int *offset, int total_length) {
    int read_cnt = read(fd, buf + *offset, total_length);

    if (read_cnt < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        } else {
            error_handling("read()시 에러 발생");
        }
    } else if (read_cnt == 0) {
        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
        if (host_type == SERVER) {
            exit_user(epfd, fd);
            return 0;
        } else if (host_type == CLIENT) {
            close(fd);
            exit(1);
        }
    }
    *offset += read_cnt;

    return read_cnt;
}


int stdin_nio_read(int host_type, int epfd, int fd, char *buf) {
    int read_cnt = read(fd, buf, BUF_SIZE);

    if (read_cnt < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        } else {
            error_handling("read()시 에러 발생");
        }
    }
//    else if (read_cnt == 0) {
//        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
//        if (host_type == SERVER) {
//            exit_user(epfd, fd);
//            return 0;
//        } else if (host_type == CLIENT) {
//            close(fd);
//            exit(1);
//        }
//    }
    else {
        if (buf[read_cnt - 1] == '\n') {
            buf[read_cnt - 1] = '\0';
            read_cnt--;
        }
    }
    return read_cnt;
}

void
client_nio_read_parse(int host_type, int epfd, int fd, char *read_buf, int *read_offset,
                      int *read_status) {


    struct protocol *new_protocol = malloc(sizeof(struct protocol));

    char *message = malloc(BUF_SIZE);
    memset(message, 0, BUF_SIZE);

    int message_offset = 0;


    int read_cnt = nio_read(host_type, epfd, fd, read_buf, read_offset, TEST_READ_SIZE);
    int result = client_protocol_handler(host_type, epfd, fd, new_protocol, read_status,
                                          read_buf, *read_offset);
    if (new_protocol->message == NULL) {
        memset(new_protocol, 0, sizeof(new_protocol));
        free(message);
        message = NULL;
        return;
    } else {
//        memset(new_protocol, 0, sizeof(new_protocol));
//        char *new_read_buf = malloc(BUF_SIZE);
//        memset(new_read_buf, 0, BUF_SIZE);
//
//        memcpy(new_read_buf, read_buf + result, strlen(read_buf) - result);
//        *read_offset -= result;
//
//        memcpy(read_buf, new_read_buf, BUF_SIZE);
//
//        if (new_read_buf != NULL) {
//            free(new_read_buf);
//            new_read_buf = NULL;
//        }
        memmove(read_buf, read_buf + *read_offset, *read_offset - result);
        *read_offset -= result;
//
    }
}


void
server_nio_read_parse(int host_type, int epfd, int fd, char *read_buf, int *read_offset, int *read_current_idx,
                      int *read_status) {


    struct protocol *new_protocol = malloc(sizeof(struct protocol));
    struct user *this_user;
    char *message = malloc(BUF_SIZE);
    memset(message, 0, BUF_SIZE);

    int message_offset = 0;


    int read_cnt = nio_read(host_type, epfd, fd, read_buf, read_offset, TEST_READ_SIZE);

    int result = server_protocol_handler( epfd, fd, new_protocol, read_status,
                                            read_buf, strlen(read_buf), message, &message_offset, read_current_idx);
    if (new_protocol->message == NULL) {
        memset(new_protocol, 0, sizeof(new_protocol));
        free(message);
        message = NULL;
        return;

    } else {
        memset(new_protocol, 0, sizeof(new_protocol));

        ptrnode_head = add_ptrnode(ptrnode_head, current_users, message, strlen(message));

        memmove(read_buf, read_buf + *read_offset, *read_offset - result);
        *read_offset -= result;


        Node *temp_user_link = user_link;
        while (temp_user_link != NULL) {
            this_user = user_list[temp_user_link->fd];
            if (this_user->registration == REGISTERED_DONE) {
                create_modify_event(epfd, this_user->fd, EPOLLIN | EPOLLOUT);
            }
            temp_user_link = temp_user_link->next;
        }
    }
}

