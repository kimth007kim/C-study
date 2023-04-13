struct message_node {
    char *char_ptr;
    int length;
    int offset;
    struct message_node *next;
};
typedef struct message_node Message_node;

Message_node *add_message_node(Message_node *head, char *char_ptr, int length);

Message_node *remove_message_node(Message_node *head);

Message_node *remove_zero_cnt_message_nodes(Message_node *head);

void free_message_node(Message_node *head);

void print_message_node(Message_node *head);

Message_node *find_message_node(Message_node *head, char *target);

Message_node *get_next_message_node(Message_node **head_ptr);

//void set_ptr(struct user *this_user, Message_node *head);