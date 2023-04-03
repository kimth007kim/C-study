#include <stdio.h>
#include<string.h>
#include <sys/epoll.h>

#include "../include/chat.h"
#include "../include/epoll.h"

void set_broadcast_write_buf(int fd, int epfd, struct protocol *protocol_ptr) {

    Node *temp_user_link = user_link;
    struct user *this_user;
    char *message = generate_message(fd, protocol_ptr->message);

    // 메세지를 프로토콜로 변경한다.
    char *protocol = encode_protocol(message, 0);


    int target_length = strlen(protocol);
    while (temp_user_link != NULL) {

        this_user = user_list[temp_user_link->fd];
        if (this_user->fd != fd) {
            strncpy(this_user->write_buf + this_user->write_offset, protocol, target_length);
            this_user->write_offset += target_length;
            struct epoll_event ev;
            ev.events |= EPOLLOUT;
            ev.data.fd = this_user->fd;
            epoll_ctl(epfd, EPOLL_CTL_MOD, this_user->fd, &ev);

        }

        temp_user_link = temp_user_link->next;
    }
}

