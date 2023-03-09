#include <arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<unistd.h>
#include <sys/epoll.h>
#include"include/util.h"

#define MAX_NAME_SIZE 30
#define EPOLL_EVENT 3
#define BUF_SIZE 1024

int main(int argc, char *argv[]) {

    int sock;
    int epfd, event_cnt;

    char buf[BUF_SIZE];

    char read_buf[BUF_SIZE] = {0,};
    char write_buf[BUF_SIZE] = {0,};
    int read_cnt = 0;
    int write_cnt = 0;

    struct sockaddr_in server_adrress;

    struct epoll_event *ep_events;
    struct epoll_event event;

    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_EVENT);
    if (argc != 2) {
        error_handling("닉네임을 입력 해주세요");
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }

    memset(&server_adrress, 0, sizeof(server_adrress));
    server_adrress.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_adrress.sin_port = 9190;
    server_adrress.sin_family = AF_INET;


    if (connect(sock, (struct sockaddr *) &server_adrress, sizeof(server_adrress)) == -1) {
        error_handling("connect error");
    } else {
        puts("Connected");
        write(sock, argv[1], strlen(argv[1]));
    }
    epfd = epoll_create(EPOLL_EVENT);

    event.events = EPOLLIN;
    event.data.fd = sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sock, &event);


    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);


    while (1) {
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_EVENT, -1);
        if (event_cnt == -1)
            return 0;
        for (int i = 0; i < event_cnt; i++) {
            if (ep_events[i].data.fd == sock) {
                memset(buf, 0, sizeof(buf));
                int str_len = read(sock, buf, sizeof(buf));
                if (str_len == 0) {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, sock, NULL);
                    close(sock);
                    return 0;
                }
                buf[str_len] = 0;
                fputs(buf, stdout);
            } else {
                char temp;
                int str_len = read(STDIN_FILENO, &temp, 1);
                if (str_len == 0) {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, STDIN_FILENO, NULL);
                    close(STDIN_FILENO);
                    return 0;
                }
                if (temp == '\n') {
                    read_buf[read_cnt] = '\0';
//                    write(sock, buf, strlen(buf));
                    printf("%s\n", read_buf);
                    memset(read_buf, 0, sizeof(read_buf));
                    read_cnt = 0;
                } else {
                    read_buf[read_cnt] = temp;
                    read_cnt += 1;
                }

            }
        }
    }
}