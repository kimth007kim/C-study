#include<sys/epoll.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/util.h"
#include "../include/protocol.h"
#include "../include/linkedlist.h"
#include "../include/client.h"

void client_epoll(int flag, int server_socket, int epfd, int fd, char * read_buf, char * write_buf) {
    int read_length = 0;
//    char read_buf[BUF_SIZE] = {0,};
//    char write_buf[BUF_SIZE] = {0,};
    if (flag == 0) {
        memset(write_buf, 0, sizeof(write_buf));
        int str_len = read(server_socket, write_buf, sizeof(write_buf));
//                printf("버퍼에서 읽어온 값 : %d  %s", str_len, buf);
        if (str_len == 0) {
            epoll_ctl(epfd, EPOLL_CTL_DEL, server_socket, NULL);
            close(server_socket);
            return;
        }

        write_buf[str_len] = '\n';
        fputs(write_buf, stdout);
        memset(write_buf, 0, sizeof(write_buf));
    } else {
        char temp;
        int str_len = read(STDIN_FILENO, &temp, 1);
        if (str_len == 0) {
            //ctrl+c 를 입력했을때
            epoll_ctl(epfd, EPOLL_CTL_DEL, STDIN_FILENO, NULL);
            close(STDIN_FILENO);
            return;
        } else {
            if (temp != '\n' && read_length < BUF_SIZE - 1) {
                read_buf[read_length] = temp;
                read_length += 1;
                return;
            }
            read_buf[read_length] = '\0';

            char *protocol = encode_protocol(read_buf, 0);

            write(server_socket, protocol, strlen(protocol));
            memset(read_buf, 0, sizeof(read_buf));
            free(protocol);
            read_length = 0;
        }
    }

}
