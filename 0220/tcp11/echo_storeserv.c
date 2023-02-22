#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#include<wait.h>

#define BUF_SIZE 100

void read_childproc(int sig);

void error_handling(char *message);


int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    int fds[2];

    pid_t pid;
    struct sigaction act;   // 시그널 핸들러의 정보를 담는 구조체
    socklen_t adr_sz;
    int str_len, state;
    char buf[BUF_SIZE];

    if (argc != 2) {
        printf("Usage: %s <port>\n ", argv[0]);
        exit(1);
    }

    // 좀비 프로세스를 막기 위한 코드
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);      //sa_mask의 모든 비트를 0으로 초기화해야되기때문에 사용
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));


    if (bind(serv_sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    pipe(fds);
    pid = fork();
    if (pid == 0) {
        FILE *fp = fopen("echomsg.txt", "wt");
        char msgbuf[BUF_SIZE];
        int i, len;
        for (i = 0; i < 10; i++) {
            len = read(fds[0], msgbuf, BUF_SIZE);
            fwrite((void *) msgbuf, 1, len, fp);
        }
        fclose(fp);
        return 0;
    }

    while (1) {
        adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_adr, &adr_sz);
        if (clnt_sock == -1)
            continue;
        else
            puts("new client connected...");

        pid = fork();
        if (pid == -1) {
            close(clnt_sock);
            continue;
        }
        if (pid == 0) {
            close(serv_sock);
            while ((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0)
                write(clnt_sock, buf, str_len);
            close(clnt_sock);
            puts("client disconnected");
            return 0;
        } else
            close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void read_childproc(int sig) {
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    printf("removed proc id : %d \n ", pid);
}