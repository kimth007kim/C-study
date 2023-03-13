#include <arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<unistd.h>
#include <sys/epoll.h>
#include"include/util.h"


struct user {
    char *name[MAX_NAME_SIZE];
    int fd;
};

int mode = 0;

char *generate_protocol(char *read_buf, int target);
// 프로토콜 생성( 버퍼, target 0(브로드 캐스트), else (특정 번호로 타겟)


int main(int argc, char *argv[]) {

    int sock;
    int epfd, event_cnt;

    char buf[BUF_SIZE];

    char read_buf[BUF_SIZE] = {0,};
    char write_buf[BUF_SIZE] = {0,};
    int read_length = 0;
    int write_cnt = 0;
    struct sockaddr_in server_adrress;

    struct epoll_event *ep_events;
    struct epoll_event event;

    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
    if (argc != 2) {
        error_handling("닉네임을 입력 해주세요");
    }

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
    sock = socket(PF_INET, SOCK_STREAM, 0);
    epfd = epoll_create(EPOLL_SIZE);

    event.events = EPOLLIN;
    event.data.fd = sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sock, &event);

    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);

    //TODO EPOLL에다가 EPOLLOUT이벤트를 붙여서 처리하는 방법
    // EPOLLOUT의 경우에는 네트워크 버퍼가 비어있을경우 이벤트를 발생 시킨다.

    while (1) {
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        if (event_cnt == -1)
            return 0;
        for (int i = 0; i < event_cnt; i++) {
            if (ep_events[i].data.fd == sock) {
                memset(buf, 0, sizeof(buf));
                int str_len = read(sock, buf, sizeof(buf));
//                printf("버퍼에서 읽어온 값 : %d  %s", str_len, buf);
                if (str_len == 0) {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, sock, NULL);
                    close(sock);
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

                    char *protocol = generate_protocol(read_buf, 0);

                    write(sock, protocol, strlen(protocol));
                    memset(read_buf, 0, sizeof(read_buf));
                    free(protocol);
                    read_length = 0;
                }
            }
        }
    }
}


char *generate_protocol(char *read_buf, int target) {
    // TODO 프로토콜 생성해서 붙이기
    // TODO  추후에 target 을 통해서 목적지를 변경하도록 구현
    char *result = malloc(sizeof(char) * PROTOCOL_SIZE);
    int protocol_length = 2;
    int target_length = int_to_strlength(target);

    int total_length = strlen(read_buf) + target_length + protocol_length;
    int body_length = int_to_strlength(total_length);
    //총 문자열의 길이를 계산완료
    total_length += body_length;
    printf(" %d는 총문자열의 길이 입니다. \n", total_length);

//                    프로토콜의 초기화
    sprintf(result, "%d %d %s", total_length, target, read_buf);

    printf("만들어진 프로토콜 [%s]\n", result);
    return result;
}
