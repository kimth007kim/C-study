#include "../include/user.h"
#include "../include/epoll.h"
//#include "../include/ptr_linkedlist.h"
#include<stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>

Ptr_node *add_ptrnode(Ptr_node *head, int cnt, char *char_ptr, int length) {
    Ptr_node *new_node = malloc(sizeof(Ptr_node));
    new_node->cnt = cnt;
    new_node->char_ptr = char_ptr;
    new_node->length = length;
    new_node->next = NULL;  // set the next pointer to NULL


    Ptr_node *prev_tail = ptrnode_tail;
    if (head == NULL) {
        // if the linked list is empty, make the new node the head
        ptrnode_tail = new_node;
        head = new_node;
    } else {
        // traverse the linked list to find the last node

        ptrnode_tail->next = new_node;
        ptrnode_tail = new_node;
//        Ptr_node *last_node = head;
//        while (last_node->next != NULL) {
//            last_node = last_node->next;
//        }
//        // set the next pointer of the last node to the new node
//        last_node->next = new_node;
//        ptrnode_tail = new_node;
    }
    struct user *current_user = NULL;
    Node *temp_user_link = user_link;
    while (temp_user_link != NULL) {
        current_user = user_list[temp_user_link->fd];
        if (current_user->registration == REGISTERED_DONE) {
            if (current_user->current_message == NULL) {
                current_user->current_message = ptrnode_tail->char_ptr;
                current_user->offset = 0;

            }
        }
        temp_user_link = temp_user_link->next;
    }


    return head;
}

Ptr_node *remove_ptrnode(Ptr_node *head, char *char_ptr) {
    if (head == NULL) {
        return NULL;
    }
    if (head->char_ptr == char_ptr) {
        Ptr_node *next_node = head->next;
        free(head);
        return next_node;
    }
    Ptr_node *current_node = head;
    while (current_node->next != NULL && current_node->next->char_ptr != char_ptr) {
        current_node = current_node->next;
    }
    if (current_node->next != NULL) {
        current_node->cnt -= 1;
        if (current_node->cnt == 0) {
            Ptr_node *node_to_remove = current_node->next;
            current_node->next = node_to_remove->next;
            free(node_to_remove);
        }

    }
    return head;
}

void free_ptrnode(Ptr_node *head) {
    while (head != NULL) {
        Ptr_node *next_node = head->next;
        free(head);
        head = next_node;
    }
}

void print_ptrnode(Ptr_node *head) {
    printf("Node list:\n");
    if (head == NULL) {
        return;
    }
    while (head != NULL) {
//        Node *next_node = head->next;
        printf(" - fd : %p\n", head->char_ptr);
        head = head->next;
    }
}

Ptr_node *find_ptrnode(Ptr_node *head, char *target) {
    Ptr_node *current_node = head;
    while (current_node != NULL) {
        if (current_node->char_ptr == target) {
            return current_node;
        }
        current_node = current_node->next;
    }
    return NULL;  // target not found in linked list
}

Ptr_node *get_next(Ptr_node **head_ptr, struct user *this_user, int epfd) {
    Ptr_node *head = *head_ptr;
    Ptr_node *next_node;
    Ptr_node *node_to_remove;
    Ptr_node *current_node;
    this_user->offset = 0;


    if (ptrnode_head->char_ptr == this_user->current_message) {
        head->cnt -= 1;

        if (head->next == NULL) {
            next_node = NULL;
        } else {
            next_node = head->next;
        }

        if (head->cnt == 0) { // 현재 노드를 삭제하는 경우
            node_to_remove = head;
            *head_ptr = head->next;

            if (node_to_remove == ptrnode_tail) {
                ptrnode_tail = NULL;
                ptrnode_head = NULL;
                this_user->current_message = NULL;
                create_modify_event(epfd, this_user->fd, EPOLLIN);

                return NULL;
            } else {

//            Node *temp_user_link = user_link;
//            while (temp_user_link!=NULL){
//
//            }
                this_user->current_message = next_node->char_ptr;

            }
            free(node_to_remove->char_ptr); // 할당된 메모리를 해제
            free(node_to_remove); // 노드를 삭제
            return next_node;
        } else {
            current_node = head;
//        this_user->current_message = ptrnode_tail->char_ptr;
            if (current_node == NULL) {
                this_user->current_message = NULL;
                create_modify_event(epfd, this_user->fd, EPOLLIN);
            } else {
                if (next_node == NULL) {
                    this_user->current_message = NULL;
                    create_modify_event(epfd, this_user->fd, EPOLLIN);
                } else {
                    this_user->current_message = next_node->char_ptr;
                }
            }
            return head;
        }
    } else {
        current_node = ptrnode_head;
        while (current_node != NULL) {
            if (current_node->char_ptr == this_user->current_message)
                break;
        }
        current_node->cnt -= 1;
        return ptrnode_head;
    }
}
