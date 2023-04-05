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
//    sprintf(destination, "%.*s", 4, protocol_ptr->destination);
//    for (int i = 0; i < sizeof(destination_handlers) / sizeof(destination_handlers[0]); i++) {
//        if (strcmp(destination, destination_handlers[i].destination) == 0) {
//            destination_handlers[i].handler(fd, epfd, protocol_ptr);
//            break;
//        }
//    }
    int integer_mode = atoi(mode);
    destination_handlers[integer_mode].handler(fd, epfd, protocol_ptr);
    printf("mode  = %s \n", mode);
    memset(mode, 0, 1);

}

void broadcast_handler(int fd, int epfd, struct protocol *protocol_ptr) {
    printf("broadcast_handler 호출\n");
    Node *temp_user_link = user_link;
    struct user *this_user;
    char *message = generate_message(fd, protocol_ptr->message, protocol_ptr->message_length);

    // 메세지를 프로토콜로 변경한다.
    char *protocol = encode_protocol(message, "A", 9999);


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

void enter_handler(int fd, int epfd, struct protocol *protocol_ptr) {
    printf(" enter_handler 호출한다. \n");
    char *name = malloc(protocol_ptr->message_length);
    sprintf(name, "%.*s", protocol_ptr->message_length-1, protocol_ptr->message);

    Node *temp_user_link = user_link;
    while (temp_user_link != NULL) {

        user_list[temp_user_link->fd] = user_list[temp_user_link->fd];
        if (user_list[temp_user_link->fd]->fd == fd) {
            user_list[temp_user_link->fd]->name = name;
            return;
        }
        temp_user_link = temp_user_link->next;
    }
//    enter_user(fd);
}


