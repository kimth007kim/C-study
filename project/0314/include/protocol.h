struct protocol {
    int total;
    int target;
    char *message;

};
char *encode_protocol(char *read_buf, int target);

struct protocol *decode_protocol(int fd, char *protocol);


