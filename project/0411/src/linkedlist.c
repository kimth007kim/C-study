#include "../include/linkedlist.h"
#include<stdio.h>
#include <stdlib.h>


Node *add_node(Node *head, int fd) {
    Node *new_node = malloc(sizeof(Node));
    new_node->fd = fd;
    new_node->next = head;
    return new_node;
}


Node *remove_node(Node *head, int fd) {
    if (head == NULL) {
        return NULL;
    }
    if (head->fd == fd) {
        Node *next_node = head->next;
        free(head);
        return next_node;
    }
    Node *current_node = head;
    while (current_node->next != NULL && current_node->next->fd != fd) {
        current_node = current_node->next;
    }
    if (current_node->next != NULL) {
        Node *node_to_remove = current_node->next;
        current_node->next = node_to_remove->next;
        free(node_to_remove);
    }
    return head;
}


void free_nodes(Node *head) {
    while (head != NULL) {
        Node *next_node = head->next;
        free(head);
        head = next_node;
    }
}

void print_users(Node *head) {
    printf("Node list:\n");
    if (head == NULL) {
        return;
    }
    while (head != NULL) {
//        Node *next_node = head->next;
        printf(" - fd : %d\n", head->fd);
        head = head->next;
    }
}
