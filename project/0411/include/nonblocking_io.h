
//void nio_stdin_read(int epfd, int fd, char *client_buf, char *write_buf, int *write_offset, int *registered);

int nio_read(int host_type, int epfd, int fd, char *buf, int *offset);

void nio_write(int host_type, int epfd, int fd, char *write_buf, int *write_offset);

void nio_read_parse(int host_type, int epfd, int fd, char *read_buf, int *read_offset, int *read_status);

void nio_read_stdin(int epfd, int fd, char *client_buf, char *write_buf, int *write_offset, int *registered);
