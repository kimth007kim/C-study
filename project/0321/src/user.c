//
// Created by kim on 23. 3. 15.
//

#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../include/user.h"


Node *user_link = NULL;
struct user *user_list[MAX_USERS];
int current_users = 0;


char *generate_greeting(int fd, int flag) {
    char *message = malloc(sizeof(char) * PROTOCOL_SIZE);
    char *time_str;
    char *hey = "입장하셨습니다";
    char *bye = "퇴장하셨습니다";

    time_str = generate_time();
    if (flag == 0) {
        sprintf(message, "[%s] %s 님이 %s.\n", time_str, user_list[fd]->name, hey);
    } else {
        sprintf(message, "[%s] %s 님이 %s.\n", time_str, user_list[fd]->name, bye);
    }
    int message_length = strlen(message);
    return message;
}

void write_message(int fd, char *buf, int len) {
    Node *temp_user_link = user_link;
    while (temp_user_link != NULL) {
//        if (user_list[temp_user_link->fd]->fd != fd) {
            write(user_list[temp_user_link->fd]->fd, buf, len);
//        }
        temp_user_link = temp_user_link->next;
    }
    printf("\n");
}

void show_users() {
    Node *temp_user_link = user_link;
    while (temp_user_link != NULL) {
        printf(" %d번의 %s님", user_list[temp_user_link->fd]->fd, user_list[temp_user_link->fd]->name);
        temp_user_link = temp_user_link->next;
    }
    printf("\n");

}

char *generate_time() {
    time_t timer = time(NULL);
    struct tm *t = localtime(&timer);
    char *result = malloc(30);
    strftime(result, BUF_SIZE, "%Y/%m/%d %H:%M:%S", t);

    return result;
}

char *generate_message(int fd, char *buf) {
    char *message = malloc(sizeof(char) * PROTOCOL_SIZE);
    char *time_str;
    time_str = generate_time();
    sprintf(message, "[%s] %s : %s", time_str, user_list[fd]->name, buf);
    int message_length = strlen(message);
//    write_message(fd, message, message_length);

    return message;
}

void enter_user(int fd) {
    current_users += 1;
    struct user *new_user = malloc(sizeof(struct user));
    new_user->fd = fd;
    new_user->name = malloc(MAX_NAME_SIZE);
    int str_len = read(fd, new_user->name, MAX_NAME_SIZE);
    new_user->name[str_len] = '\0';
    user_list[fd] = new_user;

    user_link = add_node(user_link, fd);
    show_users();
}

void exit_user(int fd) {
    if (user_link == NULL) {
        return;
    }
    if (user_list[fd]->fd == fd) {
        user_list[fd] = NULL;
        // 링크드리스트에 해당 소켓을 제거
        user_link = remove_node(user_link, fd);
        current_users -= 1;
        close(fd);
    }

}