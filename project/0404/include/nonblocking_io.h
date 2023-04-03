
void nio_read(int host_type,int epfd, int fd, char *read_buf, int *read_offset, int *read_status);

void nio_write(int host_type,int epfd, int fd, char *write_buf, int *write_offset);

void nio_stdin_read(int epfd, int fd, char *client_buf, char *write_buf, int *write_length, int *write_offset);