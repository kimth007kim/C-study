#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <errno.h>
#include <stdio.h>
#include "../include/nonblocking_io.h"
//#include "../include/client_message_linkedlist.h"
#include "../include/util.h"
#include "../include/client.h"
#include "../include/epoll.h"
#include "../include/protocol.h"
#include "../include/client_io.h"

void client_nio_read_stdin(int epfd, int fd, char *client_buf, char *write_buf, int *write_offset,
                           int *registered) {


    char *message = malloc(BUF_SIZE);
    memset(message, 0, BUF_SIZE);
    int read_cnt = stdin_nio_read(CLIENT, epfd, STDIN_FILENO, message);
    if(read_cnt==0){
        return;
    }
    printf("읽어온 read_cnt= %d\n", read_cnt);
    char *new_protocol = malloc(PROTOCOL_SIZE);
    if (*registered == FALSE) {
        new_protocol = encode_protocol(message, read_cnt, CHAR_REGISTER, 9999);
        *registered = TRUE;
    } else {
        new_protocol = encode_protocol(message, read_cnt, CHAR_BROADCAST, 9999);
    }
    free(message);

    int protocol_length = strlen(new_protocol);


    strncpy(write_buf + *write_offset, new_protocol, protocol_length);
    *write_offset += protocol_length;
    create_modify_event(epfd, fd, EPOLLIN | EPOLLOUT);



//    message_node_link = add_message_node(message_node_link, new_protocol, protocol_length);
//    // TODO client_buf 에 복사 하기.
//    create_modify_event(epfd, fd, EPOLLIN | EPOLLOUT);
}


int client_write(int host_type, int epfd, int fd, char *message, int *write_offset, int *total_length) {
//int client_nio_write(int host_type, int epfd, int fd, char *message, int *write_offset, int *total_length) {
//    int target_length = strlen(write_buf);

    int target_length = *total_length - *write_offset;
    int write_cnt = write(fd, message + *write_offset, target_length);

    if (write_cnt <= 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        } else {
            error_handling("write() error");
        }
    } else if (write_cnt == target_length) {
        *write_offset = 0;
        message_node_link = remove_message_node(message_node_link);
        if (message_node_link == NULL) {
            create_modify_event(epfd, fd, EPOLLIN);
        }
    } else if (write_cnt < target_length) {
        *write_offset += write_cnt;
    }
    return write_cnt;

}

int test_client_write(int host_type, int epfd, int fd, char *write_buf, int *write_offset) {
//    int target_length = *total_length - *write_offset;
    int write_cnt = write(fd, write_buf, *write_offset);

    if (write_cnt <= 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        } else {
            error_handling("write() error");
        }
    } else if (write_cnt <= *write_offset) {
        memmove(write_buf, write_buf + write_cnt, *write_offset - write_cnt);
        *write_offset -= write_cnt;
    }
    return write_cnt;

}

//void client_write(int epfd, int fd) {
void client_nio_write(int epfd, int fd) {
//    if (message_node_link == NULL) {
//        create_modify_event(epfd, fd, EPOLLIN);
//        return;
//    }
    Message_node *current_message_node = message_node_link;

    client_write(CLIENT, epfd, fd, current_message_node->char_ptr, &current_message_node->offset,
                 &current_message_node->length);

//    test_client_write(CLIENT, epfd, fd, current_message_node->char_ptr);
}

void test_client_nio_write(int epfd, int fd, char *write_buf, int *write_offset) {
    test_client_write(CLIENT, epfd, fd, write_buf, write_offset);
    if (*write_offset == 0)
        create_modify_event(epfd, fd, EPOLLIN);
}