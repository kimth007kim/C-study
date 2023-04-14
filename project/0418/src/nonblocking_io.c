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


void
nio_read_parse_server(int host_type, int epfd, int fd, char *read_buf, int *read_offset, int *read_current_idx,
                      int *read_status) {
    if (nio_init_flag == 0) {
        temp_protocol = malloc(sizeof(struct protocol));
        nio_init_flag = 1;
    }
//    struct protocol *new_protocol = malloc(sizeof(struct protocol));
    char *message = malloc(BUF_SIZE);
    int read_cnt = nio_read(host_type, epfd, fd, read_buf, read_offset, BUF_SIZE);
    handle_protocol_decoding(host_type, epfd, fd, temp_protocol, read_status,
                             read_buf, read_offset);

}

void
nio_read_parse(int host_type, int epfd, int fd, char *read_buf, int *read_offset, int *read_current_idx,
               int *read_status) {


    struct protocol *new_protocol = malloc(sizeof(struct protocol));
    new_protocol->message_length = 0;
//    struct protocol *new_protocol = malloc(sizeof(struct protocol));

    char *message = malloc(BUF_SIZE);
    memset(message, 0, BUF_SIZE);

//    if (new_protocol->message_length == 0)
//        read_cnt = nio_read(host_type, epfd, fd, message, read_offset, BUF_SIZE);
//    else
//        read_cnt = nio_read(host_type, epfd, fd, message, read_offset, 9 + temp_protocol->message_length);

    int read_cnt = nio_read(host_type, epfd, fd, read_buf, read_offset, BUF_SIZE);
    int result = decode_and_handle_protocol(host_type, epfd, fd, new_protocol, read_status,
                                            read_buf, strlen(read_buf));
}

