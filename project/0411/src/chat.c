#include <stdio.h>
#include<string.h>
#include <sys/epoll.h>
#include <malloc.h>
#include <stdlib.h>

#include "../include/chat.h"
#include "../include/epoll.h"


struct destination_function {
    char *destination;

    void (*handler)(int fd, int epfd, struct protocol *protocol_ptr);
};

struct destination_function destination_handlers[] = {
        {DESTINATION_ENTER,     enter_handler},
        {DESTINATION_BROADCAST, broadcast_handler},
};

void destination_handler(int fd, int epfd, struct protocol *protocol_ptr) {
//    char *destination = malloc(4);
    char *mode = malloc(1);
    sprintf(mode, "%.*s", 1, protocol_ptr->mode);
    int integer_mode = atoi(mode);
    destination_handlers[integer_mode].handler(fd, epfd, protocol_ptr);
    printf("mode  = %s \n", mode);
    memset(mode, 0, 1);

}

void broadcast_handler(int fd, int epfd, struct protocol *protocol_ptr) {
    int ptr_cnt = 0;
    printf("broadcast_handler 호출\n");
    Node *temp_user_link = user_link;
    struct user *this_user;
    char *message = generate_message(fd, protocol_ptr->message, protocol_ptr->message_length);

    // 메세지를 프로토콜로 변경한다.
    char *protocol = encode_protocol(message, CHAR_BROADCAST, 9999);


    int target_length = strlen(protocol);
    while (temp_user_link != NULL) {

        this_user = user_list[temp_user_link->fd];
        if (this_user->fd != fd & this_user->registration == REGISTERED_DONE) {
            strncpy(this_user->write_buf + this_user->write_offset, protocol, target_length);
            this_user->write_offset += target_length;
            struct epoll_event ev;
            ev.events |= EPOLLOUT;
            ev.data.fd = this_user->fd;
            epoll_ctl(epfd, EPOLL_CTL_MOD, this_user->fd, &ev);
            ptr_cnt += 1;
        }

        temp_user_link = temp_user_link->next;
    }
    if (ptr_cnt > 0)
        ptrnode_link = add_ptrnode(ptrnode_link, ptr_cnt, protocol);

}

void enter_handler(int fd, int epfd, struct protocol *protocol_ptr) {
    printf(" enter_handler 호출한다. \n");
    char *name = malloc(protocol_ptr->message_length);
    sprintf(name, "%.*s", protocol_ptr->message_length - 1, protocol_ptr->message);

    user_list[fd]->name = name;
    if (user_list[fd]->registration == NOT_REGISTERED)
        user_list[fd]->registration = REGISTERED_DONE;
}


