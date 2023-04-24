//
// Created by kim on 23. 3. 15.
//

#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "../include/user.h"
#include "../include/protocol.h"
#include "../include/epoll.h"


Node *user_link = NULL;
Ptr_node *ptrnode_head = NULL;
Ptr_node *ptrnode_tail = NULL;
struct user *user_list[MAX_USERS];
int current_users = 0;


void show_users() {
    printf("현재 접속 중인 유저 : ");
    Node *temp_user_link = user_link;
    while (temp_user_link != NULL) {
        printf(" %d번의 %s님", user_list[temp_user_link->fd]->fd, user_list[temp_user_link->fd]->name);
        temp_user_link = temp_user_link->next;
    }
    printf("\n");

}

void enter_user(int fd) {
    struct user *new_user = malloc(sizeof(struct user));
    new_user->fd = fd;
    new_user->name = NULL;
    new_user->read_status = REQUIRE_HEADER;
    new_user->write_status = WRITE_COMPLETED;
    new_user->read_offset = 0;
    new_user->registration = NOT_REGISTERED;
    new_user->current_message = NULL;
    user_list[fd] = new_user;

    user_link = add_node(user_link, fd);
    show_users();
}

void exit_user(int epfd, int fd) {

    Ptr_node *prev_node;

    int find = FALSE;

    Ptr_node *temp_ptr_node = ptrnode_head;
//            user_list[fd]->current_message;
    while (temp_ptr_node != NULL) {
        if (find == FALSE) {
            if (temp_ptr_node->char_ptr == user_list[fd]->current_message) {
                find = TRUE;
            } else {
                continue;
            }
        }
        temp_ptr_node->cnt -= 1;

        if (temp_ptr_node->cnt == 0) {
            prev_node = temp_ptr_node;
            if (ptrnode_head == prev_node) {
                temp_ptr_node = temp_ptr_node->next;
                ptrnode_head = ptrnode_head->next;
                if (ptrnode_head == NULL)
                    ptrnode_tail = NULL;
                free(prev_node);
                prev_node = NULL;
            }
        } else {
            temp_ptr_node = temp_ptr_node->next;
        }
    }
    // 현재 유저 빼기

    //  퇴장  메시지 생성
    char *protocol = generate_greeting_protocol(fd, 1);
    int target_length = strlen(protocol);


    if (user_list[fd]->fd == fd) {
        printf("%d번 %s님  퇴장\n", user_list[fd]->fd, user_list[fd]->name);
//        user_list[fd] = NULL;
        // 링크드리스트에 해당 소켓을 제거
        user_link = remove_node(user_link, fd);
        current_users -= 1;
        if (current_users > 0) {
            ptrnode_head = add_ptrnode(ptrnode_head, current_users, protocol, target_length);
            Node *temp_user_link = user_link;
            while (temp_user_link != NULL) {
                create_modify_event(epfd, temp_user_link->fd, EPOLLIN | EPOLLOUT);
                temp_user_link = temp_user_link->next;
            }
        }
        safe_free((void **) &user_list[fd]->name);
        safe_free((void **) &user_list[fd]);
    }

    safe_free((void **) &protocol);
    close(fd);
    show_users();
}
