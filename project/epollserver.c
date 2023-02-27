#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define BUF_SIZE 100
#define EPOLL_SIZE 50
#define MAX_NAME_SIZE 30

void error_handling(char *message);

void send_greetings(int clnt_sock);

int main() {

    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    int i, str_len, optlen;
    socklen_t adr_sz;
    char buf[BUF_SIZE];

    // epoll 설정
    int epfd, event_cnt;
    struct epoll_event *ep_events;
    struct epoll_event event;


    int option;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    //소켓 재할당 설정
    optlen = sizeof(option);
    option = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void *) &option, optlen);


    memset(&serv_adr, 0, sizeof(serv_adr));


    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = 9190;

    if (bind(serv_sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1) {
        error_handling("bind() error");
    }

    if (listen(serv_sock, 5) == -1) {
        error_handling("listen() error");
    }

    epfd = epoll_create(EPOLL_SIZE);
    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
    event.events = EPOLLIN;
    event.data.fd = serv_sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);

    while (1) {

        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        if (event_cnt == -1) {
            puts("epoll_wait() error");
            break;
        }
        for (i = 0; i < event_cnt; ++i) {
            if (ep_events[i].data.fd == serv_sock) {
                adr_sz = sizeof(clnt_adr);
                clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_adr, &adr_sz);
                event.events = EPOLLIN;
                event.data.fd = clnt_sock;
//                send_greetings(clnt_sock);
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
                printf("connected client : %d \n", clnt_sock);
            } else {
                str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
                if (str_len == 0) {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    close(ep_events[i].data.fd);
                    printf("close client : %d \n ", ep_events[i].data.fd);
                } else {
                    for (int i = 5; i < clnt_sock + 1; i++) {
                        write(i, buf, str_len);
                    }
                }
            }

        }

    }


    close(serv_sock);
    return 0;

}

void send_greetings(int clnt_sock) {

    char name[MAX_NAME_SIZE + 1];
    char greetings[] = "님이 입장하셨습니다!\n";
    int name_len = read(clnt_sock, name, sizeof(MAX_NAME_SIZE));
    name[name_len] = '\0';
    printf("%s\n", name);
    strcat(name, greetings);
    printf("%s\n", name);
    for (int i = 5; i < clnt_sock + 1; i++) {
        write(i, name, strlen(greetings) + name_len);
    }

}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);

}
