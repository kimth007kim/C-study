
void client_nio_read_stdin(int epfd, int fd, char *client_buf, char *write_buf, int *write_offset, int *registered);

//void client_write(int epfd, int fd);
void client_nio_write(int epfd, int fd);

void test_client_nio_write(int epfd, int fd, char *write_buf, int *write_offset);

//int client_nio_write(int host_type, int epfd, int fd, char *message, int *write_offset, int *total_length);
int client_write(int host_type, int epfd, int fd, char *message, int *write_offset, int *total_length);

int test_client_write(int host_type, int epfd, int fd, char *message, int *write_offset);
