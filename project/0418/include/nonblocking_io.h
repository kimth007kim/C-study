
//void nio_stdin_read(int epfd, int fd, char *client_buf, char *write_buf, int *write_offset, int *registered);

//void server_write(int host_type, int epfd, int fd, char *write_buf, int *write_offset, char *broadcast_buf,
//                  int *broadcast_offset);

//int nio_server_write(int host_type, int epfd, int fd, char *write_buf, int length);
int server_write(int host_type, int epfd, int fd, char *write_buf, int length);

int server_write_test(int host_type, int epfd, int fd, char *write_buf, int total_length,int current_user_offset,int num);

int stdin_nio_read(int host_type, int epfd, int fd, char *buf);

int nio_read(int host_type, int epfd, int fd, char *buf, int *offset, int total_length);
//int nio_read(int host_type, int epfd, int fd, char *buf, int *offset, int total_length);


int nio_write(int host_type, int epfd, int fd, char *write_buf, int *write_offset);

//int n_write(int host_type, int epfd, int fd, char *message, int *write_offset, int *total_length) ;

void
client_nio_read_parse(int host_type, int epfd, int fd, char *read_buf, int *read_offset,
                      int *read_status);

void
server_nio_read_parse(int host_type, int epfd, int fd, char *read_buf, int *read_offset, int *read_current_idx,
                      int *read_status);

//void client_nio_read_stdin(int epfd, int fd, char *client_buf, char *write_buf, int *write_offset, int *registered);
