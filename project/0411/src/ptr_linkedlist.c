#include "../include/ptr_linkedlist.h"
#include<stdio.h>
#include <stdlib.h>

//
//Ptr_node *add_ptrnode(Ptr_node *head, int cnt, char *char_ptr) {
//    Ptr_node *new_node = malloc(sizeof(Ptr_node));
//    new_node->cnt = cnt;
//    new_node->char_ptr = char_ptr;
//    new_node->next = head;
//    return new_node;
//}

Ptr_node *add_ptrnode(Ptr_node *head, int cnt, char *char_ptr) {
    Ptr_node *new_node = malloc(sizeof(Ptr_node));
    new_node->cnt = cnt;
    new_node->char_ptr = char_ptr;
    new_node->next = NULL;  // set the next pointer to NULL

    if (head == NULL) {
        // if the linked list is empty, make the new node the head
        head = new_node;
    } else {
        // traverse the linked list to find the last node
        Ptr_node *last_node = head;
        while (last_node->next != NULL) {
            last_node = last_node->next;
        }
        // set the next pointer of the last node to the new node
        last_node->next = new_node;
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
