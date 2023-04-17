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

int nio_server_write(int host_type, int epfd, int fd, char *write_buf, int length) {
    int write_cnt = write(fd, write_buf, length);
    if (write_cnt <= 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        } else {
            error_handling("write() error");
        }
    } else if (write_cnt == length) {
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
            exit_user(fd);
            return 0;
        } else if (host_type == CLIENT) {
            close(fd);
            exit(1);
        }
    }
    *offset += read_cnt;

    return read_cnt;
}
//int nio_read(int host_type, int epfd, int fd, char *buf, int *offset, int total_length) {
//    int read_cnt = read(fd, buf + *offset, total_length);
//
//    if (read_cnt < 0) {
//        if (errno == EAGAIN || errno == EWOULDBLOCK) {
//            return 0;
//        } else {
//            error_handling("read()시 에러 발생");
//        }
//    } else if (read_cnt == 0) {
//        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
//        if (host_type == SERVER) {
//            exit_user(fd);
//            return 0;
//        } else if (host_type == CLIENT) {
//            close(fd);
//            exit(1);
//        }
//    }
//    *offset += read_cnt;
//
//    return read_cnt;
//}


int stdin_nio_read(int host_type, int epfd, int fd, char *buf) {
    int read_cnt = read(fd, buf, BUF_SIZE);

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


//void
//nio_read_parse_server(int host_type, int epfd, int fd, char *read_buf, int *read_offset, int *read_current_idx,
//                      int *read_status) {
//    if (nio_init_flag == 0) {
//        temp_protocol = malloc(sizeof(struct protocol));
//        nio_init_flag = 1;
//    }
////    struct protocol *new_protocol = malloc(sizeof(struct protocol));
//    char *message = malloc(BUF_SIZE);
//    int read_cnt = nio_read(host_type, epfd, fd, read_buf, read_offset, BUF_SIZE);
//    handle_protocol_decoding(host_type, epfd, fd, temp_protocol, read_status,
//                             read_buf, read_offset);
//
//}


void
nio_read_parse(int host_type, int epfd, int fd, char *read_buf, int *read_offset,
               int *read_status) {


    struct protocol *new_protocol = malloc(sizeof(struct protocol));

    char *message = malloc(BUF_SIZE);
    memset(message, 0, BUF_SIZE);

    int message_offset = 0;


//    int read_cnt = nio_read(host_type, epfd, fd, read_buf, read_offset, BUF_SIZE);
    int read_cnt = nio_read(host_type, epfd, fd, read_buf, read_offset, 10);
    int result = handle_protocol_decoding(host_type, epfd, fd, new_protocol, read_status,
                                          read_buf, read_offset, strlen(read_buf), message, &message_offset);
    if (new_protocol->message == NULL) {
        memset(new_protocol, 0, sizeof(new_protocol));
        free(message);
        message = NULL;
        return;
    } else {
        char *new_read_buf = malloc(BUF_SIZE);
        memset(new_read_buf, 0, BUF_SIZE);
        memcpy(new_read_buf, read_buf + result, strlen(read_buf) - result);
        *read_offset -= result;

//    *read_offset -= decoded;
        memcpy(read_buf, new_read_buf, BUF_SIZE);
        free(new_read_buf);

    }
//    char *new_read_buf = malloc(BUF_SIZE);
//    memset(new_read_buf, 0, BUF_SIZE);
//    memcpy(new_read_buf, read_buf + read_cnt, strlen(read_buf) - read_cnt);
//    *read_offset -= read_cnt;
////        free(read_buf);
//    memcpy(read_buf, new_read_buf, BUF_SIZE);
//    free(new_read_buf);
//    Node *temp_user_link = user_link;


}


void
nio_read_parse_server(int host_type, int epfd, int fd, char *read_buf, int *read_offset, int *read_current_idx,
                      int *read_status) {


    struct protocol *new_protocol = malloc(sizeof(struct protocol));

    char *message = malloc(BUF_SIZE);
    memset(message, 0, BUF_SIZE);

    int message_offset = 0;


//    int read_cnt = nio_read(host_type, epfd, fd, read_buf, read_offset, BUF_SIZE);
    int read_cnt = nio_read(host_type, epfd, fd, read_buf, read_offset, 10);
    int result = decode_and_handle_protocol(host_type, epfd, fd, new_protocol, read_status,
                                            read_buf, strlen(read_buf), message, &message_offset);
//    if (result ==0) {
//        if (message != NULL) {
//            free(message);
//            message = NULL;
//            return;
//        }

    if (new_protocol->message == NULL) {
        memset(new_protocol, 0, sizeof(new_protocol));
        free(message);
        message = NULL;
        return;
    } else {
        memset(new_protocol, 0, sizeof(new_protocol));
        struct user *this_user;
        ptrnode_head = add_ptrnode(ptrnode_head, current_users, message, strlen(message));
        char *new_read_buf = malloc(BUF_SIZE);
        memset(new_read_buf, 0, BUF_SIZE);
        memcpy(new_read_buf, read_buf + result, strlen(read_buf) - result);
        *read_offset -= result;
//        free(read_buf);
        memcpy(read_buf, new_read_buf, BUF_SIZE);
        free(new_read_buf);
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

