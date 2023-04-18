//#include "user.h"
struct user;
struct ptr_node {
    char *char_ptr;
    int cnt;
    int length;
    struct ptr_node *next;
};
typedef struct ptr_node Ptr_node;

Ptr_node *add_ptrnode(Ptr_node *head, int cnt, char *char_ptr, int length);

Ptr_node *remove_ptrnode(Ptr_node *head, char *char_ptr);

Ptr_node *remove_zero_cnt_nodes(Ptr_node *head);

void free_ptrnode(Ptr_node *head);

void print_ptrnode(Ptr_node *head);

Ptr_node *find_ptrnode(Ptr_node *head, char *target);

Ptr_node *get_next(Ptr_node **head_ptr,struct user * this_user,int epfd);

//void set_ptr(struct user *this_user, Ptr_node *head);