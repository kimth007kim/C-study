#include <stdio.h>
#include<string.h>
#include <sys/epoll.h>
#include <malloc.h>
#include <stdlib.h>

#include "../include/server_io.h"
#include "../include/epoll.h"
#include "../include/nonblocking_io.h"


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
    printf("broadcast_handler 호출\n");

    // 메세지를 프로토콜로 변경한다.

    struct user *this_user;
    char *message = generate_message(fd, protocol_ptr->message, protocol_ptr->message_length);
    char *protocol = encode_protocol(message, strlen(message), CHAR_BROADCAST, 9999);


    int target_length = strlen(protocol);

    ptrnode_link = add_ptrnode(ptrnode_link, current_users, protocol, target_length);
    Node *temp_user_link = user_link;
    while (temp_user_link != NULL) {
        this_user = user_list[temp_user_link->fd];
//
        if (this_user->registration == REGISTERED_DONE) {
            create_modify_event(epfd, this_user->fd, EPOLLIN | EPOLLOUT);
        }
//
        temp_user_link = temp_user_link->next;
    }


}

void enter_handler(int fd, int epfd, struct protocol *protocol_ptr) {
    printf(" enter_handler 호출한다. \n");
    char *name = malloc(protocol_ptr->message_length);
    sprintf(name, "%.*s", protocol_ptr->message_length - 1, protocol_ptr->message);

    user_list[fd]->name = name;
    if (user_list[fd]->registration == NOT_REGISTERED)
        user_list[fd]->registration = REGISTERED_DONE;
    current_users += 1;

    show_users();
}


void server_write(int host_type, int epfd, int fd) {
    struct user *this_user;
    this_user = user_list[fd];

    set_ptr(this_user, ptrnode_link);
    Ptr_node *current_node = find_ptrnode(ptrnode_link, this_user->current_message);
    int write_cnt = nio_server_write(host_type, epfd, fd, this_user->current_message + this_user->offset,
                                     current_node->length - this_user->offset);
    this_user->offset += write_cnt;
    if (this_user->offset == current_node->length) {
        this_user->offset = 0;
        Ptr_node *next_node = get_next(&ptrnode_link, this_user);
        ptrnode_link = next_node;
    }
}



