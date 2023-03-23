#include<sys/epoll.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "../include/util.h"
#include "../include/protocol.h"
#include "../include/linkedlist.h"
#include "../include/client.h"


/**
 *
 * @param server_socket server_socket은 서버의 경우 자기 자신을 의미합니다. 이것을 토대로 stdin인지 , 아니면 서버와의 통신인지 구별합니다.
 * @param epfd          epfd는 epollevent를 감지하는 fd입니다.
 * @param fd            fd 는 이벤트가 발생한 fd를 가리킵니다.
 * @param read_buf      epoll_event가 발생할때 read_buf도 받습니다.
 * @param write_buf     epoll_event가 발생할때 write_buf도 받습니다.
 * @param read_length   epoll_event가 발생할때 read_length 받습니다. read_buf에서 어디까지 읽었는지 기록하기위한 변수입니다.
 */
void client_epoll(int server_socket, int epfd, int fd, char *read_buf, char *write_buf, int *read_length) {
    char *protocol = malloc(PROTOCOL_SIZE);
    if (server_socket == fd) {
        memset(write_buf, 0, sizeof(write_buf));
        int str_len = read(server_socket, write_buf, BUF_SIZE);
        if (str_len == 0) {
            epoll_ctl(epfd, EPOLL_CTL_DEL, server_socket, NULL);
            close(server_socket);
//            return;
            exit(1);
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
            exit(1);
        } else {
            if (temp != '\n' && *read_length < BUF_SIZE - 1) {
                read_buf[*read_length] = temp;
                *read_length += 1;
                return;
            }
            read_buf[*read_length] = '\0';

            protocol = encode_protocol(read_buf, 0);
            char *output=malloc(1000);
//            encode_kd_protocol(read_buf, 0,output);
            printf("%s\n",output);
            write(server_socket, protocol, strlen(protocol));
            memset(read_buf, 0, sizeof(read_buf));
            *read_length = 0;
        }
    }

}

void client_network(struct sockaddr_in server_address, int server_socket, char *name) {
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (server_socket == -1) {
        error_handling("socket() error");
    }
    if (connect(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        error_handling("connect error");
    } else {
        puts("Connected");
        write(server_socket, name, strlen(name));
    }
}