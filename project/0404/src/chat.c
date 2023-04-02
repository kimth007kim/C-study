//
// Created by kim on 23. 3. 21.
//
#include <stdio.h>
#include <unistd.h>
#include<string.h>
#include <errno.h>
#include <sys/epoll.h>
#include <stdlib.h>

#include "../include/chat.h"
#include "../include/epoll.h"

#define READ_AGAIN 1
#define READ_FIRST_TIME 0

void broadcast_error_handling(char *message, int fd) {
    fputs(message, stderr);
    fputc('\n', stderr);
    close(fd);
}
//
//void chat(int fd, int epfd, struct protocol *protocol_ptr, struct user *user_ptr, int read_again) {
//    printf("message = %.*s, total = %d, dest = %.*s\n",
//           protocol_ptr->message_length, protocol_ptr->message,
//           protocol_ptr->message_length,
//           4, protocol_ptr->destination);
//    broadcast_mode(fd, epfd, protocol_ptr, user_ptr, read_again);
//}


void switch_write_buf(struct user *user) {
    int new_length = strlen(user->write_buf) - user->write_offset;
    char *new_buf = malloc(BUF_SIZE);
    strncpy(new_buf, user->write_buf + user->write_offset, new_length);
    memset(user->write_buf, 0, BUF_SIZE);
    strncpy(user->write_buf, new_buf, new_length);
    user->write_offset = 0;
}

void set_write_buf(int fd, int epfd, struct protocol *protocol_ptr) {

    Node *temp_user_link = user_link;
    struct user *this_user;
    char message[PROTOCOL_SIZE + 30];
    char *time_str = generate_time();
    sprintf(message, "[%s] %s : %.*s", time_str, user_list[fd]->name, protocol_ptr->message_length,
            protocol_ptr->message);
    char *protocol = encode_protocol(message, 0);
    int protocol_length = strlen(protocol);
    while (temp_user_link != NULL) {

        this_user = user_list[temp_user_link->fd];
        if (this_user->fd != fd) {
            strncpy(this_user->write_buf + this_user->write_offset, protocol, protocol_length);
            struct epoll_event ev;
            ev.events |= EPOLLOUT;
            ev.data.fd = this_user->fd;
            epoll_ctl(epfd, EPOLL_CTL_MOD, this_user->fd, &ev);
//            create_modify_event(epfd, this_user->fd, EPOLLIN | EPOLLOUT);

        }

        temp_user_link = temp_user_link->next;
    }
}


void write_nonblocking(int fd, int epfd, struct epoll_event event) {

    int write_cnt;
    struct user *new_user;

    if (user_list[event.data.fd] == NULL) {
        return;
    }
    new_user = user_list[event.data.fd];
    int protocol_length = strlen(new_user->write_buf);

    write_cnt = write(event.data.fd, new_user->write_buf, protocol_length);
    if (write_cnt <= 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK || write_cnt == 0) {
            return;
        } else {
            error_handling("write() error");
        }
    } else if (write_cnt < protocol_length) {
        user_list[event.data.fd]->write_offset += write_cnt;
        switch_write_buf(new_user);

    } else {
        user_list[event.data.fd]->write_offset += protocol_length;
        struct epoll_event ev;
        switch_write_buf(new_user);
        ev.events = EPOLLIN;
        ev.data.fd = event.data.fd;
        epoll_ctl(epfd, EPOLL_CTL_MOD, event.data.fd, &ev);
    }

}
//
//void broadcast_mode(int fd, int epfd, struct protocol *protocol_ptr, struct user *user_ptr, int read_again) {
//
//    char *time_str = generate_time();
//    struct user *this_user;
//    int write_cnt;
//    int message_length;
//
//    if (read_again == READ_FIRST_TIME) {
//        // broadcast_mode가 첫번째 호출되었을때
//
//        char message[PROTOCOL_SIZE + 30];
//        sprintf(message, "[%s] %s : %.*s", time_str, user_list[fd]->name, protocol_ptr->message_length,
//                protocol_ptr->message);
//        char *protocol = encode_protocol(message, 0);
//        Node *temp_user_link = user_link;
//        message_length = strlen(protocol);
//
//
//        while (temp_user_link != NULL) {
//            this_user = user_list[temp_user_link->fd];
//            if (this_user->fd != fd) {
//
//                //  포인터로 write_buf에 등록해놓으려 했으나, 나중에 free 하는 과정에서 Nullpointer 참조 할수도 있어서 일단 복사
//
//                write_cnt = write(this_user->fd, user_list[temp_user_link->fd]->write_buf, message_length);
//
//                if (write_cnt < 0) {
//                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
//                        strncpy(this_user->write_buf + this_user->write_offset, protocol, message_length);
//                        this_user->write_offset += message_length;
//
//                        struct epoll_event ev;
//                        ev.events = EPOLLOUT;
//                        epoll_ctl(epfd, EPOLL_CTL_ADD, this_user->fd, &ev);
//                    } else {
//                        error_handling("write() error");
//                    }
//                } else if (write_cnt < message_length) {
//                    strncpy(this_user->write_buf + this_user->write_offset,
//                            protocol, write_cnt);
//                    this_user->write_offset += write_cnt;
//
//                    struct epoll_event ev;
//                    ev.events = EPOLLOUT;
//                    epoll_ctl(epfd, EPOLL_CTL_ADD, this_user->fd, &ev);
//
//                }
//
//            }
//            temp_user_link = temp_user_link->next;
////            printf("\n");
//        }
//
//    } else {
//        // 메세지를 다 읽어오지 못했거나, 버퍼가 가득차있어서 쓸수 없는 상황이어서 재호출되었을때
//        Node *temp_user_link = user_link;
//        while (temp_user_link != NULL) {
//            this_user = user_list[temp_user_link->fd];
//            if (this_user->fd != fd) {
//                message_length = strlen(this_user->write_buf);
//                //  포인터로 write_buf에 등록해놓으려 했으나, 나중에 free 하는 과정에서 Nullpointer 참조 할수도 있어서 일단 복사
//                write_cnt = write(this_user->fd, this_user->write_buf, message_length);
//
//                if (write_cnt < 0) {
//                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
//                        continue;
//                    } else {
//                        broadcast_error_handling("write() error", this_user->fd);
//                    }
//
//                } else if (write_cnt == message_length) {
//                    // 버퍼 비우기
//                    switch_write_buf(this_user);
//                    struct epoll_event ev;
//                    ev.events = EPOLLOUT;
//                    epoll_ctl(epfd, EPOLL_CTL_DEL, this_user->fd, &ev);
//
//                } else if (write_cnt < message_length) {
//                    this_user->write_offset += write_cnt;
//
//                }
//
//                temp_user_link = temp_user_link->next;
//            }
////            printf("\n");
//        }
//
//    }
//}


void whisper_mode() {

}


void command_mode() {


}