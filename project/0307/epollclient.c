#include <arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<unistd.h>
#include <sys/epoll.h>
#include"include/util.h"

#define MAX_NAME_SIZE 30
#define EPOLL_EVENT 10
#define BUF_SIZE 1024

int main(int argc, char *argv[]) {

    int sock;
    int epfd, event_cnt;

    char buf[BUF_SIZE];
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
        event_cnt = epoll_wait(epfd, ep_events, 3, -1);
        if (event_cnt == -1)
            return 0;
        for (int i = 0; i < event_cnt; i++) {
            if (ep_events[i].data.fd == sock) {
                int str_len = read(sock, buf, sizeof(buf));
                if (str_len == 0) {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, sock, NULL);
                    close(sock);
                    return 0;
                }
                buf[str_len] = 0;
                fputs(buf, stdout);
            } else {
                fgets(buf, BUF_SIZE, stdin);
                if (strcmp(buf, "q\n") == 0 || strcmp(buf, "Q\n") == 0) {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, STDIN_FILENO, NULL);
                    close(STDIN_FILENO);
                    return 0;
                } else {
                    write(sock, buf, strlen(buf));
                }
            }
        }
    }

}