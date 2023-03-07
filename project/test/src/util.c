#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/epoll.h>

//#include <sys/socket.h>
//#include<time.h>
//
//#include<stdio.h>
//#include <arpa/inet.h>
//#include<string.h>
//#include <stdlib.h>
//#include<unistd.h>
//#include <sys/epoll.h>

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);

}