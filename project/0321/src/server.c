#include<sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "../include/util.h"
#include "../include/protocol.h"
#include "../include/server.h"
#include "../include/epoll.h"
#include "../include/user.h"

/**
 *
 * @param server_socket
 * @param epfd
 * @param fd
 * @param read_buf
 * @param write_buf
 * @param read_length
 */
void server_epoll(int server_socket, int epfd, int fd, char *read_buf, char *write_buf, int *read_length) {
    socklen_t address_size;
    int str_len;
    int client_socket;
    struct sockaddr_in client_address;

    if (server_socket == fd) {
        // 서버 소켓으로 수신된 데이터가 존재한다는것은 연결 요청이 있다는 것이다.
        printf("flag=0\n");
        address_size = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr *) &client_address, &address_size);
        if (client_socket == -1) {
            puts("accept() error!");
            exit(1);
        }
        create_add_event(epfd, client_socket, EPOLLIN);
        enter_user(client_socket);
    } else {
        // 클라이언트 소켓으로 부터 수신된 데이터가 존재한다는것.

//        str_len = read(fd, read_buf, BUF_SIZE);


        str_len = read(fd, user_list[fd]->read_buf, BUF_SIZE);

        //읽어온 길이를 기록해놓는다.
        user_list[fd]->total_read_length+=str_len;
        if (user_list[fd]->num_end==0){

            if(user_list[fd]->total_read_length<4){
                // 4보다 적게 읽어왔을때 총 길이를 모를때
                return;
                //return 으로 빠져나간다.
            }else{
                // 4보다 많이 읽어왔을때(총길이를 알때)


                // 앞에서 4부터 짤라서 본다.
            }

        }



        if (str_len == 0) {
            // Ctrl + c 로 인한 종료 요청
//            greeting = generate_greeting(fd, 1);
            epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
            exit_user(fd);
        } else {
            printf("읽어온 read_buf %s", read_buf);

            //TODO 프로토콜 read할때 처리
            // if 문으로 분기처리

            // str_len 이 4 보다 작을때 (프로토콜의 총길이를 모를때 처리)
//            struct protocol *new_protocol = decode_protocol(fd, read_buf);
            // 프로토콜의 총길이를 처음알았을때 user 구조체에 저장하는 코드

            // 현재 offset을 저장하는 함수

            // 모든 길이를 다 읽었다면 write 하는 함수







            //TODO 프로토콜을 파싱하는 함수를 만들고, 파싱한 정보를 토대로 분기 처리

            printf("\n");
            write_message(fd, read_buf, strlen(read_buf));


            memset(read_buf, 0, sizeof(read_buf));
        }

    }
}

void server_network(struct sockaddr_in server_address, int server_socket, char *name) {
    int option = 1;
    int option_len = sizeof(option);
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (void *) &option, option_len);


    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        error_handling("bind() error");
    }

    if (listen(server_socket, MAX_USERS) == -1) {
        error_handling("listen() error");
    }
}