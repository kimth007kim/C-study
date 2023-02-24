#include <arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<unistd.h>

#define BUF_SIZE 1024

void read_message(int sock, char *buf);

void write_message(int sock, char *buf);

void error_handling(char *message);

int main() {

    int sock;
    char opmsg[BUF_SIZE];
    char *message;
    int str_len, recv_len, recv_cnt;
    int pid;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_adr;


    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_adr.sin_port = 9190;
    serv_adr.sin_family = AF_INET;

//    printf("설정완료 연결 대기중");

    if (connect(sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1) {
        printf("connect error");
        exit(1);
    } else {
        puts("Connected");
    }

//    while (1) {
//        fputs("Input message(Q to quit): ", stdout);
//        fgets(message, BUF_SIZE, stdin);
//        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
//            break;
//        str_len = write(sock, message, strlen(message));
//
//        recv_len = 0;
//        while (recv_len < str_len) {
//            recv_cnt = read(sock, &message[recv_len], BUF_SIZE - 1);
//            if (recv_cnt == -1)
//                error_handling("read() error!");
//            recv_len += recv_cnt;
//        }
//        message[recv_len] = 0;
//        printf("Message from server: %s ", message);
//    }


    pid = fork();
    if (pid == 0)
        write_message(sock, buf);
    else
        read_message(sock, buf);

    close(sock);

    return 0;

}

void read_message(int sock, char *buf) {
    while (1) {
        int str_len = read(sock, buf, sizeof(buf));
        if (str_len == 0) {
            return;
        }
        buf[str_len] = 0;
        fputs(buf, stdout);
    }

}

void write_message(int sock, char *buf) {
    char message[1000];
    while (1) {
        fgets(buf, BUF_SIZE, stdin);
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")) {
            shutdown(sock, SHUT_WR);
            return;
        }
        sprintf(message, " %s  %s", "안녕", buf);
        write(sock,message,strlen(message));
    }
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
