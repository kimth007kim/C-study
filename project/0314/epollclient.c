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
                    epoll_ctl(epfd, EPOLL_CTL_DEL, STDIN_FILENO, NULL);
                    close(STDIN_FILENO);
                    return 0;
                } else {
                    if (temp != '\n' && read_length < BUF_SIZE - 1) {
                        read_buf[read_length] = temp;
                        read_length += 1;
                        continue;
                    } else {
                        read_buf[read_length] = '\0';
                        printf(" 가득차버려서 미리끝낸다. 버퍼에 있는 문자열 : %s 문자열의 길이 %ld \n", read_buf, strlen(read_buf));
                    }
                    // TODO 프로토콜 생성해서 붙이기
                    // TODO  추후에 target 을 통해서 목적지를 변경하도록 구현
                    // 이미 정해져 있는 것은 띄어쓰기 문자 두개 밖에 없다.
                    //  target 문자열의 길이가 달라진다. ex) 총길이가 157 일때는 문자열 길이+3을 고려
                    //  총 문자열의 길이가 달라진다. ex) 총길이가 157 일때는 문자열 길이+3을 고려


                    int protocol_length = 2;
                    int target = 0;// 일단은 브로드캐스트로 고정
                    int target_length= int_to_strlength(target);

                    int total_length = strlen(read_buf) +target_length+ protocol_length;
                    int body_length = int_to_strlength(total_length);
                    //총 문자열의 길이를 계산완료
                    total_length += body_length;
                    printf(" %d는 총문자열의 길이 입니다. \n", total_length);

//                    프로토콜의 초기화
                    char protocol[PROTOCOL_SIZE] = {0,};

                    //TODO protocol이 PROTOCOL_SIZE를 초과할때 예외 처리 하도록하자

                    write(sock, read_buf, strlen(read_buf));
                    memset(read_buf, 0, sizeof(read_buf));
                    read_length = 0;


                }
                //TODO 나중에 첫번째 문자열이 '/' 인지 확인하는 것
//              printf("첫번째 문자열은 = {%c} \n",buf[0]);

//                if (buf[0[ == 2) {
//                    if (strcmp("/q", buf)) {
//
//                    }
//                        //TODO 추후 구현할 명령어 관리
//                    else if ("/a", buf) {
//
//                    }
//                }

            }
        }
    }
}


