#include <arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<unistd.h>
#include <sys/epoll.h>
#include"include/util.h"
#include "include/epoll.h"


struct user {
    char *name[MAX_NAME_SIZE];
    int fd;
};

int mode = 0;

char *encode_protocol(char *read_buf, int target);
// 프로토콜 생성( 버퍼, target 0(브로드 캐스트), else (특정 번호로 타겟)


int main(int argc, char *argv[]) {

    int server_socket;
    int epfd, event_cnt;

    char buf[BUF_SIZE];

    char read_buf[BUF_SIZE] = {0,};
    char write_buf[BUF_SIZE] = {0,};
    int read_length = 0;
    int write_cnt = 0;
    struct sockaddr_in server_adrress;

    struct epoll_event *ep_events;
    struct epoll_event event;

    if (argc != 2) {
        error_handling("닉네임을 입력 해주세요");
    }


    memset(&server_adrress, 0, sizeof(server_adrress));
    server_adrress.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_adrress.sin_port = 9190;
    server_adrress.sin_family = AF_INET;


    server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        error_handling("socket() error");
    }
    if (connect(server_socket, (struct sockaddr *) &server_adrress, sizeof(server_adrress)) == -1) {
        error_handling("connect error");
    } else {
        puts("Connected");
        write(server_socket, argv[1], strlen(argv[1]));
    }
    epfd = epoll_create(EPOLL_SIZE);
    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);


    create_add_event(epfd, server_socket, EPOLLIN);
    create_add_event(epfd, STDIN_FILENO, EPOLLIN);
    //TODO EPOLL에다가 EPOLLOUT이벤트를 붙여서 처리하는 방법
    // EPOLLOUT의 경우에는 네트워크 버퍼가 비어있을경우 이벤트를 발생 시킨다.

//    event_loop(client_epoll,server_socket,epfd);
    while (1) {
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        if (event_cnt == -1)
            return 0;
        for (int i = 0; i < event_cnt; i++) {
            if (ep_events[i].data.fd == server_socket) {
                memset(buf, 0, sizeof(buf));
                int str_len = read(server_socket, buf, sizeof(buf));
//                printf("버퍼에서 읽어온 값 : %d  %s", str_len, buf);
                if (str_len == 0) {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, server_socket, NULL);
                    close(server_socket);
                    return 0;
                }

                buf[str_len] = '\n';
                fputs(buf, stdout);
//                printf(buf);
                memset(read_buf, 0, sizeof(read_buf));
            } else {
                char temp;

                int str_len = read(STDIN_FILENO, &temp, 1);
                if (str_len == 0) {
                    //ctrl+c 를 입력했을때
                    epoll_ctl(epfd, EPOLL_CTL_DEL, STDIN_FILENO, NULL);
                    close(STDIN_FILENO);
                    return 0;
                } else {
                    if (temp != '\n' && read_length < BUF_SIZE - 1) {
                        read_buf[read_length] = temp;
                        read_length += 1;
                        continue;
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
    }
}
