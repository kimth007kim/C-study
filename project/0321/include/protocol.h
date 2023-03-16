struct protocol{
    char total[4];
    char dest[4];
    char *message[9999];
};
char *encode_protocol(char *read_buf, int target);

struct protocol *decode_protocol(int fd, char *protocol);


