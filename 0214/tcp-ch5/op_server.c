#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

#define BUF_SIZE 1024
#define OPSZ 4


void error_handling(char *message);

int calculate(int opnum, int opnds[], char oprator);

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    char opinfo[BUF_SIZE];
    int result, opnd_cnt, i;
    int recv_cnt, recv_len;
    struct sockaddr_in server_addr, client_addr;
    socklen_t clnt_adr_sz;

    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    //소켓 생성
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("소켓 생성 제대로 안됨 ");
    printf("소켓 생성완료");

    //바인딩
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_family = AF_INET;


    if (bind(serv_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
        error_handling("바인딩 오류");
    //listen
    printf("리슨완료");
    if (listen(serv_sock, 5) == -1) {
        error_handling("리슨 오류");
    }
    clnt_adr_sz = sizeof(client_addr);
    printf("%d\n",clnt_adr_sz);

    for (i = 0; i < 5; i++) {
        opnd_cnt = 0;
        clnt_sock = accept(serv_sock, (struct sockaddr *) &client_addr, &clnt_adr_sz);
        read(clnt_sock, &opnd_cnt, 1);
        recv_len = 0;
        while ((opnd_cnt * OPSZ + 1) > recv_len) {
            recv_cnt = read(clnt_sock, &opinfo[recv_len], BUF_SIZE - 1);
            recv_len += recv_cnt;
        }
        result = calculate(opnd_cnt, (int *) opinfo, opinfo[recv_len - 1]);
        write(clnt_sock, (char *) &result, sizeof(result));
        close(clnt_sock);
    }
//    accept(serv_sock, (struct sockaddr *) &client_addr, &clnt_adr_sz);
    close(serv_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);


}

int calculate(int opnum, int opnds[], char op) {

    int result = opnds[0], i;
    switch (op) {
        case '+':
            for (i = 1; i < opnum; i++) result += opnds[i];
        case '-':
            for (i = 1; i < opnum; i++) result -= opnds[i];
        case '*':
            for (i = 1; i < opnum; i++) result *= opnds[i];

    }
    return result;

}
