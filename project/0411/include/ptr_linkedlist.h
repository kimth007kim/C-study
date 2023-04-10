struct ptr_node {
    char *char_ptr;
    int cnt;
    struct ptr_node *next;
};
typedef struct ptr_node Ptr_node;

Ptr_node *add_ptrnode(Ptr_node *head, int cnt, char *char_ptr);

Ptr_node *remove_ptrnode(Ptr_node *head, char *char_ptr);

Ptr_node *remove_zero_cnt_nodes(Ptr_node *head);

void free_ptrnode(Ptr_node *head);

void print_ptrnode(Ptr_node *head);