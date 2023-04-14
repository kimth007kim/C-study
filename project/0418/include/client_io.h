
void nio_read_stdin(int epfd, int fd, char *client_buf, char *write_buf, int *write_offset, int *registered);

void client_write(int epfd, int fd);

int n_write(int host_type, int epfd, int fd, char *message, int *write_offset, int *total_length);
