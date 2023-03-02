#include <arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<unistd.h>
#include<time.h>

#define BUF_SIZE 1024

void read_message(int sock, char *buf);
void write_message(int sock, char *buf, char *argv);
void error_handling(char *message);
char *generate_time();

int main(int argc, char *argv[]) {

    int sock;
    int pid;
    char buf[BUF_SIZE];
    struct sockaddr_in server_adrress;


    if (argc != 2) {
        error_handling("닉네임을 입력 해주세");
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
        printf("connect error");
        exit(1);
    } else {
        puts("Connected");
        write(sock,argv[1],sizeof(30));
        sleep(1);
// 추후에 채팅한 유저의 정보를 구조체로 저장할 예정
    }
    pid = fork();
    if (pid == 0)
        write_message(sock, buf, argv[1]);
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

void write_message(int sock, char *buf, char *argv) {
    char message[1000];
    char *time_str;
    while (1) {
        fgets(buf, BUF_SIZE, stdin);
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")) {
            shutdown(sock, SHUT_WR);
            return;
        }
        time_str = generate_time();
        sprintf(message, "[%s] [%s] : %s",time_str, argv, buf);
        write(sock, message, strlen(message));
    }
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

char *generate_time() {
    time_t timer = time(NULL);
    struct tm *t = localtime(&timer);
    char *result = malloc(30);
    strftime(result, BUF_SIZE, "%Y/%m/%d %H:%M:%S", t);

    return result;
}
