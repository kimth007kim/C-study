#include "include/linkedlist.h"
#include <stdio.h>

int main() {
    int server_fd = 1;
    Node *user_link = NULL;

    user_link = add_node(user_link, server_fd);
    print_users(user_link);
    user_link = remove_node(user_link, server_fd);
    print_users(user_link);

    user_link = add_node(user_link, 4);
    print_users(user_link);

    user_link = add_node(user_link, 87);
    print_users(user_link);

    user_link = add_node(user_link, 24);
    print_users(user_link);


    free_nodes(user_link);

}