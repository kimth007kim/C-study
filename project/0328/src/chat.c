//
// Created by kim on 23. 3. 21.
//
#include <stdio.h>
#include <unistd.h>
#include<string.h>

#include "../include/chat.h"

void chat(int fd, struct protocol *protocol_ptr, struct user *user_ptr) {
    printf("message = %.*s, total = %d, dest = %.*s\n",
           protocol_ptr->message_length, protocol_ptr->message,
           protocol_ptr->message_length,
           4, protocol_ptr->destination);
    broadcast_mode(fd,protocol_ptr,user_ptr);
}


void broadcast_mode(int fd, struct protocol *protocol_ptr, struct user *user_ptr) {
    char message[PROTOCOL_SIZE + 30];
    char *time_str = generate_time();
    sprintf(message, "[%s] %s : %.*s", time_str, user_list[fd]->name, protocol_ptr->message_length, protocol_ptr->message);

   char *protocol= encode_protocol(message,0);

    Node *temp_user_link = user_link;
    while (temp_user_link != NULL) {
        if (user_list[temp_user_link->fd]->fd != fd) {
        write(user_list[temp_user_link->fd]->fd, protocol, strlen(protocol));
        }
        temp_user_link = temp_user_link->next;
    }
    printf("\n");
}


void whisper_mode() {

}


void command_mode() {


}