struct node {
    int fd;
    struct node *next;
};
typedef struct node Node;

Node *add_node(Node *head, int fd);

Node *remove_node(Node *head, int fd);

void free_nodes(Node *head);

void print_users(Node *head);