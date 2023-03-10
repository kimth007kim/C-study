#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<signal.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define BUF_SIZE 30


void urg_handler(int signo);

void error_handling(char *message);

int acpt_sock;
int recv_sock;

int main(int argc, char *argv[]) {
    struct sockaddr_in recv_adr, serv_adr;
    int str_len, state;

    socklen_t serv_adr_sz;
    struct sigaction act;
    char buf[BUF_SIZE];

    if (argc != 2) {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }
    act.sa_handler = urg_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    acpt_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&recv_adr, 0, sizeof(recv_adr));
    recv_adr.sin_family = AF_INET;
    recv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    recv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(acpt_sock, (struct sockaddr *) &serv_adr, sizeof(recv_adr)) == -1)
        error_handling("bind() error");
    listen(acpt_sock, 5);
    serv_adr_sz = sizeof(serv_adr);
    recv_sock = accept(acpt_sock, (struct sockaddr *) &serv_adr, &serv_adr_sz);

    fcntl(recv_sock, F_SETOWN, getpid());           // 현재 프로세스에게 이 소켓의 소유자가 되게한다.
    state = sigaction(SIGURG, &act, 0);
    while ((str_len = (recv_sock, buf, sizeof(buf), 0)) != 0) {
        if (str_len == -1)
            continue;
        buf[str_len] = 0;
        puts(buf);

    }
    close(recv_sock);
    close(acpt_sock);
    return 0;
}


void urg_handler(int signo) {
    int str_len;
    char buf[BUF_SIZE];
    str_len = recv(recv_sock, buf, sizeof(buf - 1), MSG_OOB);
    buf[str_len] = 0;
    printf("Urgent message: %s \n", buf);
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}