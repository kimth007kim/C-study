#include<sys/epoll.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <errno.h>
#include "../include/util.h"
#include "../include/protocol.h"
#include "../include/linkedlist.h"
#include "../include/client.h"
#include "../include/epoll.h"
#include "../include/nonblocking_io.h"


#define REQUIRE_INIT 0
#define ALREADY_INIT 1


int init_flag = REQUIRE_INIT;
int read_status;

int read_offset = 0;

int write_length = 0;
int write_offset = 0;
char *protocol;

struct protocol *new_protocol;
char *write_buf;

char *read_buf;

//TODO 프로토콜 버퍼를 추가하도록하자.
char *client_buf;

/**
 *
 * @param server_socket server_socket은 서버의 경우 자기 자신을 의미합니다. 이것을 토대로 stdin인지 , 아니면 서버와의 통신인지 구별합니다.
 * @param epfd          epfd는 epollevent를 감지하는 fd입니다.
 * @param fd            fd 는 이벤트가 발생한 fd를 가리킵니다.
 *
 */
void client_epoll(int server_socket, int epfd, struct epoll_event event) {
    if (init_flag == REQUIRE_INIT) {
        init_global_vars();
    }
    if (event.events & EPOLLOUT) {
        nio_write(CLIENT, epfd, server_socket, write_buf, &write_offset);

    } else {
        if (server_socket == event.data.fd) {
            // 서버로 부터 프로토콜을 전송 받았을 경우에 read() 수행
            nio_read(CLIENT, epfd, server_socket, read_buf, &read_offset, &read_status);
        } else {
            // stdin으로 부터 문자열을 입력 받을 경우에 read() 수행
            nio_stdin_read(epfd, server_socket, client_buf, write_buf, &write_length, &write_offset);
        }
    }
}

void init_global_vars() {
    read_buf = malloc(BUF_SIZE);
    write_buf = malloc(BUF_SIZE);
    client_buf = malloc(BUF_SIZE);
    new_protocol = malloc(sizeof(struct protocol));
    read_status = REQUIRE_HEADER;
    errno = 0;
    init_flag = ALREADY_INIT;
}


void client_network(struct sockaddr_in server_address, int server_socket, char *name) {
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (server_socket == -1) {
        error_handling("socket() error");
    }
    if (connect(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        error_handling("connect error");
    } else {
        puts("Connected");
        write(server_socket, name, strlen(name));
    }
}
