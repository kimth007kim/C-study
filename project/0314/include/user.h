
#include "util.h"
#include "linkedlist.h"

struct user {
    //TODO 각각의 유저별로 read_buf 와 write_buf를 따로 두는 식으로 설계

    char *name;
    int fd;
    int total_read_length;
    int num_end;        // 숫자가 다들어 왔는지 확인하는 변수
    int current_read_pos;
    char *read_buf[PROTOCOL_SIZE];
    char *write_buf[PROTOCOL_SIZE];
};

#ifndef MY_PROGRAM_USER_H
#define MY_PROGRAM_USER_H

Node *user_link;
struct user *user_list[MAX_USERS];
int current_users = 0;

#endif //MY_PROGRAM_USER_H
