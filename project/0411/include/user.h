#ifndef MY_PROGRAM_USER_H
#define MY_PROGRAM_USER_H

#include "util.h"
#include "linkedlist.h"

//#include "protocol.h"
extern Node *user_link;
extern struct user *user_list[MAX_USERS];
extern int current_users;

struct user {
    //TODO 각각의 유저별로 read_buf 와 write_buf를 따로 두는 식으로 설계

    char *name;
    int fd;
    int read_status;        // 숫자가 다들어 왔는지 확인하는 변수
    char read_buf[PROTOCOL_SIZE];
    char write_buf[PROTOCOL_SIZE];
    int write_offset;
    int read_offset;
    int registration;
//    struct protocol user_protocol;

};


void write_message(int fd, char *buf, int len);

void show_users();

void enter_user(int fd);

void exit_user(int fd);


#endif //MY_PROGRAM_USER_H