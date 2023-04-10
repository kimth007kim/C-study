#include <stdio.h>
#include<string.h>
#include <sys/epoll.h>
#include <malloc.h>
#include <stdlib.h>

#include "../include/chat.h"
#include "../include/epoll.h"


struct destination_function {
    char *destination;

    void (*handler)(int fd, int epfd, struct protocol *protocol_ptr, char *broadcast_buf, int *broadcast_offset);
};

struct destination_function destination_handlers[] = {
        {DESTINATION_ENTER,     enter_handler},
        {DESTINATION_BROADCAST, broadcast_handler},
};

void destination_handler(int fd, int epfd, struct protocol *protocol_ptr, char *broadcast_buf, int *broadcast_offset) {
//    char *destination = malloc(4);
    char *mode = malloc(1);
    sprintf(mode, "%.*s", 1, protocol_ptr->mode);
    int integer_mode = atoi(mode);
    destination_handlers[integer_mode].handler(fd, epfd, protocol_ptr, broadcast_buf, broadcast_offset);
    printf("mode  = %s \n", mode);
    memset(mode, 0, 1);

}

void broadcast_handler(int fd, int epfd, struct protocol *protocol_ptr, char *broadcast_buf, int *broadcast_offset) {
    printf("broadcast_handler 호출\n");

    // 메세지를 프로토콜로 변경한다.

    if (current_users >= 2) {
        int ptr_cnt = 0;
        struct user *this_user;
        Node *temp_user_link = user_link;
        char *message = generate_message(fd, protocol_ptr->message, protocol_ptr->message_length);
        char *protocol = encode_protocol(message, CHAR_BROADCAST, 9999);


        int target_length = strlen(protocol);

        strncpy(broadcast_buf + *broadcast_offset, protocol, target_length);
        *broadcast_offset += target_length;
        while (temp_user_link != NULL) {
            this_user = user_list[temp_user_link->fd];

            if (this_user->registration == REGISTERED_DONE) {
//            strncpy(this_user->write_buf + this_user->write_offset, protocol, target_length);
//            this_user->write_offset += target_length;
                create_modify_event(epfd, this_user->fd, EPOLLIN | EPOLLOUT);
                ptr_cnt += 1;
                if (this_user->char_start == NULL) {
                    this_user->char_start = broadcast_buf;
                }
            }

            temp_user_link = temp_user_link->next;
        }


        ptrnode_link = add_ptrnode(ptrnode_link, ptr_cnt, broadcast_buf + *broadcast_offset);
    }
//
//    int target_length = strlen(protocol);
//    while (temp_user_link != NULL) {
//
//        this_user = user_list[temp_user_link->fd];
//        if (this_user->fd != fd & this_user->registration == REGISTERED_DONE) {
//            strncpy(this_user->write_buf + this_user->write_offset, protocol, target_length);
//            this_user->write_offset += target_length;
//            create_modify_event(epfd, this_user->fd, EPOLLIN | EPOLLOUT);
//            ptr_cnt += 1;
//        }
//
//        temp_user_link = temp_user_link->next;
//    }
//    if (ptr_cnt > 0)
//        ptrnode_link = add_ptrnode(ptrnode_link, ptr_cnt, protocol);

}

void enter_handler(int fd, int epfd, struct protocol *protocol_ptr, char *broadcast_buf, int *broadcast_offset) {
    printf(" enter_handler 호출한다. \n");
    char *name = malloc(protocol_ptr->message_length);
    sprintf(name, "%.*s", protocol_ptr->message_length - 1, protocol_ptr->message);

    user_list[fd]->name = name;
    if (user_list[fd]->registration == NOT_REGISTERED)
        user_list[fd]->registration = REGISTERED_DONE;
    current_users += 1;
}


