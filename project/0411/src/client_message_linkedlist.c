#include "../include/user.h"
#include "../include/client_message_linkedlist.h"
#include<stdio.h>
#include <stdlib.h>

Message_node *add_message_node(Message_node *head, char *char_ptr, int length) {
    Message_node *new_node = malloc(sizeof(Message_node));
    new_node->char_ptr = char_ptr;
    new_node->length = length;
    new_node->offset = 0;
    new_node->next = NULL;  // set the next pointer to NULL

    if (head == NULL) {
        // if the linked list is empty, make the new node the head
        head = new_node;
    } else {
        // traverse the linked list to find the last node
        Message_node *last_node = head;
        while (last_node->next != NULL) {
            last_node = last_node->next;
        }
        // set the next pointer of the last node to the new node
        last_node->next = new_node;
    }

    return head;
}

Message_node *remove_message_node(Message_node *head) {
    if (head == NULL) {
        return NULL;
    }
    free(head->char_ptr);
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    Message_node *next_node = head->next;
    free(head);
    return next_node;
}

void free_message_node(Message_node *head) {
    while (head != NULL) {
        Message_node *next_node = head->next;
        free(head);
        head = next_node;
    }
}

void print_message_node(Message_node *head) {
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

Message_node *find_message_node(Message_node *head, char *target) {
    Message_node *current_node = head;
    while (current_node != NULL) {
        if (current_node->char_ptr == target) {
            return current_node;
        }
        current_node = current_node->next;
    }
    return NULL;  // target not found in linked list
}
//
//Message_node *get_next_message_node(Message_node **head_ptr) {
//    Message_node *head = *head_ptr;
//    head->cnt -= 1;
//    Message_node *next_node = head->next;
//
//    if (head->cnt == 0) { // 현재 노드를 삭제하는 경우
//        Message_node *node_to_remove = head;
//        *head_ptr = head->next;
//        free(node_to_remove->char_ptr); // 할당된 메모리를 해제
//        free(node_to_remove); // 노드를 삭제
//        if (next_node != NULL)
//            this_user->current_message = next_node->char_ptr;
//        else
//            this_user->current_message = NULL;
//        return next_node;
//    }
//    if (next_node != NULL)
//        this_user->current_message = next_node->char_ptr;
//    else
//        this_user->current_message = NULL;
//
//    return head;
//}
