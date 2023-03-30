#ifndef MY_PROGRAM_USER_H
#define MY_PROGRAM_USER_H

#include "util.h"
#include "linkedlist.h"

#define LISTEN_NONE 0
#define LISTEN_BROADCAST 1



//#include "protocol.h"
extern Node *user_link;
extern struct user *user_list[MAX_USERS];
extern int current_users;

struct user {
    //TODO 각각의 유저별로 read_buf 와 write_buf를 따로 두는 식으로 설계

    char *name;
    int fd;
    int read_status;        // 숫자가 다들어 왔는지 확인하는 변수
    int start_offset;
    int end_offset;
    char read_buf[PROTOCOL_SIZE];
    char write_buf[PROTOCOL_SIZE];
    int write_offset;
    int write_idx;
//    struct protocol user_protocol;

};


char *generate_greeting(int fd, int flag);

void write_message(int fd, char *buf, int len);

void show_users();

char *generate_time();

char *generate_message(int fd, char *buf);

void enter_user(int fd);

void exit_user(int fd);

void switch_buffer(struct user *user);

#endif //MY_PROGRAM_USER_H