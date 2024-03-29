#ifndef MY_PROGRAM_USER_H
#define MY_PROGRAM_USER_H

#include "util.h"
#include "linkedlist.h"
#include "ptr_linkedlist.h"
#include <sys/time.h>

#define NOT_REGISTERED 0
#define REGISTERED_DONE 1

#define WRITE_COMPLETED 0
#define WRITE_UNCOMPLETED 1


extern Node *user_link;
extern Ptr_node *ptrnode_head;
extern Ptr_node *ptrnode_tail;
extern struct user *user_list[MAX_USERS];
extern int current_users;

struct user {
    //TODO 각각의 유저별로 read_buf 와 write_buf를 따로 두는 식으로 설계

    char *name;
    int fd;
    int read_status;        // 숫자가 다들어 왔는지 확인하는 변수
    char read_buf[PROTOCOL_SIZE];
    char read_buffer[PROTOCOL_SIZE];
    int read_current_idx;
    int read_offset;
    int registration;
    char *current_message;
    int offset;


    int write_delay;
    int read_delay;
    int read_delay_time;
    int write_delay_time;

    struct timeval start_time;
    // 전에 프로토콜이 완성되었는지 여부를 판별한다.
//    int prev_read_done;

//    struct protocol user_protocol;

};


void write_message(int fd, char *buf, int len);

void show_users();

void enter_user(int fd);

void exit_user(int epfd, int fd);

void set_ptr(struct user *this_user, Ptr_node *head);

#endif //MY_PROGRAM_USER_H