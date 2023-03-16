#include<sys/epoll.h>
#include<stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include "../include/util.h"
#include "../include/protocol.h"
//#include "../include/linkedlist.h"
#include "../include/server.h"
#include "../include/epoll.h"
//#include "../include/user.h"


//void server_epoll(int flag,int server_socket,int epfd,int fd, char * read_buf, char * write_buf) {
//    socklen_t address_size;
//    int str_len=0;
//    int client_socket;
//    int client_address;
//    if (flag == 0) {
//        address_size = sizeof(client_address);
//        client_socket = accept(server_socket, (struct sockaddr *) &client_address, &address_size);
//        if (client_socket == -1) {
//            puts("accept() error!");
//            return;
//        }
//        create_add_event(epfd, client_socket, EPOLLIN);
//
//        enter_user(client_socket);
//        generate_greeting(client_socket, 0);
//
//
//    } else {
//        if (str_len == 0) {
//            // Ctrl + c 로 인한 종료 요청
//            generate_greeting(fd, 1);
//
//            epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
//            exit_user(fd);
//
//
//        } else {
//            //TODO 프로토콜을 파싱하는 함수를 만들고, 파싱한 정보를 토대로 분기 처리
//            struct protocol *new_protocol = decode_protocol(fd, buf);
////                    generate_message(ep_events[i].data.fd, buf);
//            memset(buf, 0, sizeof(buf));
//        }
//
//    }
//}