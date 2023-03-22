//
// Created by kim on 23. 3. 21.
//
#include <stdio.h>

#include "../include/chat.h"

void chat(int fd,struct protocol * protocol_ptr, struct user * user_ptr) {
    printf("message = %.*s, total = %d, dest = %.*s\n",
           protocol_ptr->message_length,protocol_ptr->message,
           protocol_ptr->message_length,
           4, protocol_ptr->destination);

}


void broadcast_mode() {

}


void whisper_mode() {

}


void command_mode() {


}