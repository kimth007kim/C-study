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

    void (*handler)(int fd, int epfd, struct protocol *protocol_ptr, char *message, int *message_offset,
                    int *current_read_idx);
};

struct destination_function destination_handlers[] = {
        {DESTINATION_ENTER,     enter_handler},
        {DESTINATION_BROADCAST, broadcast_handler},
//        {DESTINATION_EXIT,      exit_handler},
};

void destination_handler(int fd, int epfd, struct protocol *protocol_ptr, char *message, int *message_offset,
                         int *current_read_idx) {
//    char *destination = malloc(4);
//    char *mode = malloc(1);
    char mode[2];
    sprintf(mode, "%.*s", 1, protocol_ptr->mode);
    int integer_mode = atoi(mode);
    destination_handlers[integer_mode].handler(fd, epfd, protocol_ptr, message, message_offset,
                                               current_read_idx);
    printf("mode  = %s \n", mode);
//    memset(mode, 0, 1);

}

void broadcast_handler(int fd, int epfd, struct protocol *protocol_ptr, char *message, int *message_offset,
                       int *current_read_idx) {
    printf("broadcast_handler 호출\n");

    // 메세지를 프로토콜로 변경한다.

    struct user *this_user;
    char *new_message = generate_message(fd, protocol_ptr->message, protocol_ptr->message_length);
    char *protocol = encode_protocol(new_message, strlen(new_message), CHAR_BROADCAST, 9999);


    int target_length = strlen(protocol);

    strncpy(message + *message_offset, protocol, target_length);
    *message_offset += target_length;

    safe_free((void **) &protocol);
    safe_free((void **) &new_message);


}

void enter_handler(int fd, int epfd, struct protocol *protocol_ptr, char *message, int *message_offset,
                   int *current_read_idx) {
    char *name = malloc(protocol_ptr->message_length + 1);
    printf(" enter_handler 호출한다. %d 길이의 message_length \n", protocol_ptr->message_length);

    sprintf(name, "%.*s", protocol_ptr->message_length, protocol_ptr->message);
    name[protocol_ptr->message_length] = '\0';

    user_list[fd]->name = name;
    printf("==== user_list[fd]->name:%s\n", user_list[fd]->name);
    if (user_list[fd]->registration == NOT_REGISTERED)
        user_list[fd]->registration = REGISTERED_DONE;
    current_users += 1;
    char *protocol = generate_greeting_protocol(fd, 0);
    int target_length = strlen(protocol);

    strncpy(message + *message_offset, protocol, target_length);
    *message_offset += target_length;
//    user_list[fd]->current_message = protocol;
    user_list[fd]->offset = 0;

//    *current_read_idx += target_length - 9;
    show_users();
    safe_free((void **) &protocol);
}

void exit_handler(int fd, int epfd, struct protocol *protocol_ptr, char *message, int *message_offset,
                  int *current_read_idx) {
    printf(" enter_handler 호출한다. \n");
    char *name = malloc(protocol_ptr->message_length);
    sprintf(name, "%.*s", protocol_ptr->message_length, protocol_ptr->message);
    user_list[fd]->name = name;


    if (user_list[fd]->registration == NOT_REGISTERED)
        user_list[fd]->registration = REGISTERED_DONE;
    current_users += 1;


    char *protocol = generate_greeting_protocol(fd, 1);

    int target_length = strlen(protocol);


    strncpy(message + *message_offset, protocol, target_length);

    *message_offset += target_length;
//    user_list[fd]->current_message = protocol;
    user_list[fd]->offset = 0;

//    *current_read_idx += target_length - 9;
    show_users();
}

void server_nio_write(int host_type, int epfd, int fd) {
    struct user *this_user;
    this_user = user_list[fd];

    Ptr_node *current_node = find_ptrnode(ptrnode_head, this_user->current_message);
    if (current_node == NULL) {
        create_modify_event(epfd, fd, EPOLLIN);
        return;
    }
//    int write_cnt = server_write(host_type, epfd, fd, current_node->char_ptr + this_user->offset,
//                                 current_node->length - this_user->offset);
    int write_cnt = server_write_test(host_type, epfd, fd, current_node->char_ptr + this_user->offset,
                                      current_node->length, this_user->offset, 100);
    this_user->offset += write_cnt;

    if (this_user->offset == current_node->length) {
        this_user->write_delay_time = 0;

//        this_user->write_delay = WRITE_COMPLETED;
//        this_user->offset = 0;
        Ptr_node *next_node = get_next(&ptrnode_head, this_user, epfd);
        ptrnode_head = next_node;

        current_node = find_ptrnode(ptrnode_head, this_user->current_message);
        if (current_node == NULL)
            create_modify_event(epfd, fd, EPOLLIN);

    } else {
        // write를 덜한경우
        this_user->write_delay_time += 1;
//        if (this_user->write_delay == WRITE_COMPLETED) {
//            gettimeofday(&this_user->start_time, NULL);
//        } else {
//            int timeout_ms = 5000;
//            struct timeval current_time;
//            gettimeofday(&current_time, NULL);
//
//            long elapsed_ms = (current_time.tv_sec - this_user->start_time.tv_sec) * 1000 +
//                              (current_time.tv_usec - this_user->start_time.tv_usec) / 1000;
//            if (elapsed_ms >= timeout_ms) {
//                exit_user(epfd, fd);
//            }
//
//        }
//        this_user->write_delay = WRITE_UNCOMPLETED;
    }

}