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


void nio_write(int host_type, int epfd, int fd, char *write_buf, int *write_offset) {
    int target_length = strlen(write_buf);
    int write_cnt = write(fd, write_buf, target_length);

    if (write_cnt <= 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return;
        } else {
            error_handling("write() error");
        }
    } else if (write_cnt < target_length) {
        switch_buffer(write_buf, write_offset);
    } else {
        switch_buffer(write_buf, write_offset);
        create_modify_event(epfd, fd, EPOLLIN);
    }
}

int nio_read(int host_type, int epfd, int fd, char *buf, int *offset) {
    int read_cnt = read(fd, buf + *offset, BUF_SIZE);


    if (read_cnt < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return -1;
        } else {
            error_handling("read()시 에러 발생");
        }
    } else if (read_cnt == 0) {
        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
        if (host_type == SERVER) {
            exit_user(fd);
            return -1;
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


void nio_read_parse(int host_type, int epfd, int fd, char *read_buf, int *read_offset, int *read_status) {
    struct protocol *new_protocol = malloc(sizeof(struct protocol));
    int protocol_read = 0;
    int read_cnt = nio_read(host_type, epfd, fd, read_buf, read_offset);
    protocol_read += read_cnt;
    decode_and_handle_protocol(host_type, epfd, fd, new_protocol, &protocol_read, read_status,
                               read_offset,
                               read_buf);

}
