#include <arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define BUF_SIZE 50

int main() {

    int sock;
    char opmsg[BUF_SIZE];

    struct sockaddr_in serv_adr;


    memset(&serv_adr, 0, sizeof(serv_adr));
    sock = socket(PF_INET, SOCK_STREAM, 0);
    serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_adr.sin_port = 9190;
    serv_adr.sin_family = AF_INET;

    if (connect(sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1) {
        printf("connect error");
        exit(1);
    } else {
        puts("Connected");
    }


    return 0;

}
