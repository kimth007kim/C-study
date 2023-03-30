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

#define READ_AGAIN 1
#define READ_FIRST_TIME 0

void broadcast_error_handling(char *message, int fd) {
    fputs(message, stderr);
    fputc('\n', stderr);
    close(fd);
}

void chat(int fd, int epfd, struct protocol *protocol_ptr, struct user *user_ptr, int read_again) {
    printf("message = %.*s, total = %d, dest = %.*s\n",
           protocol_ptr->message_length, protocol_ptr->message,
           protocol_ptr->message_length,
           4, protocol_ptr->destination);
    broadcast_mode(fd, epfd, protocol_ptr, user_ptr, read_again);
}


void switch_write_buf(struct user *user) {
    char *new_buf = malloc(BUF_SIZE);
    memset(new_buf, 0, BUF_SIZE);
    for (int i = 0; i < user->write_offset; i++) {
        new_buf[i] = user->read_buf[i];
    }
    memcpy(user->read_buf, new_buf, user->write_offset);
    user->write_offset = 0;
    free(new_buf);
}

void set_write_buf(){



}

void broadcast_mode(int fd, int epfd, struct protocol *protocol_ptr, struct user *user_ptr, int read_again) {

    char *time_str = generate_time();
    struct user *target_user;
    int write_cnt;
    int message_length;

    if (read_again == READ_FIRST_TIME) {
        // broadcast_mode가 첫번째 호출되었을때

        char message[PROTOCOL_SIZE + 30];
        sprintf(message, "[%s] %s : %.*s", time_str, user_list[fd]->name, protocol_ptr->message_length,
                protocol_ptr->message);
        char *protocol = encode_protocol(message, 0);
        Node *temp_user_link = user_link;
        message_length = strlen(protocol);
        while (temp_user_link != NULL) {
            target_user = user_list[temp_user_link->fd];
            if (target_user->fd != fd) {

                //  포인터로 write_buf에 등록해놓으려 했으나, 나중에 free 하는 과정에서 Nullpointer 참조 할수도 있어서 일단 복사

                write_cnt = write(target_user->fd, user_list[temp_user_link->fd]->write_buf, message_length);

                if (write_cnt < 0) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        strncpy(target_user->write_buf + target_user->write_offset, protocol, message_length);
                        target_user->write_offset += message_length;

                        struct epoll_event ev;
                        ev.events = EPOLLOUT;
                        epoll_ctl(epfd, EPOLL_CTL_ADD, target_user->fd, &ev);
                    } else {
                        error_handling("write() error");
                    }
                } else if (write_cnt < message_length) {
                    strncpy(target_user->write_buf + target_user->write_offset,
                            protocol, write_cnt);
                    target_user->write_offset += write_cnt;

                    struct epoll_event ev;
                    ev.events = EPOLLOUT;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, target_user->fd, &ev);

                }

            }
            temp_user_link = temp_user_link->next;
            printf("\n");
        }

    } else {
        // 메세지를 다 읽어오지 못했거나, 버퍼가 가득차있어서 쓸수 없는 상황이어서 재호출되었을때
        Node *temp_user_link = user_link;
        while (temp_user_link != NULL) {
            target_user = user_list[temp_user_link->fd];
            if (target_user->fd != fd) {
                message_length = strlen(target_user->write_buf);
                //  포인터로 write_buf에 등록해놓으려 했으나, 나중에 free 하는 과정에서 Nullpointer 참조 할수도 있어서 일단 복사
                write_cnt = write(target_user->fd, target_user->write_buf, message_length);

                if (write_cnt < 0) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        continue;
                    } else {
                        broadcast_error_handling("write() error", target_user->fd);
                    }

                } else if (write_cnt == message_length) {
                    // 버퍼 비우기
                    switch_write_buf(target_user);
                    struct epoll_event ev;
                    ev.events = EPOLLOUT;
                    epoll_ctl(epfd, EPOLL_CTL_DEL, target_user->fd, &ev);

                } else if (write_cnt < message_length) {
                    target_user->write_offset += write_cnt;

                }

                temp_user_link = temp_user_link->next;
            }
            printf("\n");
        }

    }
}


void whisper_mode() {

}


void command_mode() {


}