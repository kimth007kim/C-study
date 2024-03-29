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

#define NEED_LENGTH 0
#define NEED_DESTINATION 1
#define NEED_MESSAGE 2


/**
 *
 * @param server_socket server_socket은 서버의 경우 자기 자신을 의미합니다. 이것을 토대로 연결요청인지, 아니면 클라이언트와의 통신인지 구별합니다.
 * @param epfd          epfd는 epollevent를 감지하는 fd입니다.
 * @param fd            fd 는 이벤트가 발생한 fd를 가리킵니다.
 * @param read_buf      epoll_event가 발생할때 read_buf도 받습니다. 서버에서는 read_buf가 사용되지않습니다.
 * @param write_buf     epoll_event가 발생할때 write_buf도 받습니다. 서버에서는 write_buf가 사용되지않습니다.
 * @param read_length   epoll_event가 발생할때 read_length 받습니다. 서버에서는 read_length 가 사용되지않습니다.
 */
void server_epoll(int server_socket, int epfd, int fd, char *read_buf, char *write_buf, int *read_length) {
    socklen_t address_size;
    int str_len;
    int client_socket;
    struct sockaddr_in client_address;
    struct protocol *new_protocol = malloc(sizeof(struct protocol));


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



        str_len = read(fd, user_list[fd]->read_buf + user_list[fd]->end_offset, BUF_SIZE);
        if (str_len == 0) {
            epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
            exit_user(fd);
        }
        struct user *user_ptr = user_list[fd];
        int total_read = str_len + user_ptr->end_offset - user_ptr->start_offset;
        user_ptr->end_offset += total_read;
        while (total_read > 0) {
            if (user_ptr->num_end == 0) {
                if (total_read < 4) {
                    // 4보다 적게 읽어 왔을때 총 길이를 모를때
                    return;
                    //return 으로 빠져 나간다.
                } else {

                    memset(new_protocol, 0, sizeof(struct protocol));
                    char temp[5];
                    strncpy(temp, user_ptr->read_buf + user_ptr->start_offset, 4);
                    temp[4] = '\n';
//                            printf(" 읽어온 프로토콜은 %s\n", temp);
                    int total_length = atoi(temp);
//                            printf(" int 형으로 변환 읽어온 프로토콜은 %d\n", total_length);
                    user_ptr->start_offset += 4;
                    new_protocol->total = total_length;
                    total_read -= 4; //프로토콜의 총 길이를 읽어오는 작업 완료
                    user_ptr->num_end = NEED_DESTINATION;
                    memset(temp, 0, 5);

                }
                // 4보다 많이 읽어 왔을때(총 길이를 알때)
            } else if (user_ptr->num_end == 1) {
                if (total_read < 4) {
                    return;
                } else {
                    char temp[5];
                    strncpy(temp, user_ptr->read_buf + user_ptr->start_offset, 4);
                    temp[4] = '\n';
                    int dest = atoi(temp);
//                            printf(" int 형으로 변환 읽어온 프로토콜은 %d\n", dest);
                    user_ptr->start_offset += 4;
                    new_protocol->dest = dest;
                    total_read -= 4;
                    user_ptr->num_end = NEED_MESSAGE;
                    memset(temp, 0, 5);
                }
            } else {
                if (total_read < new_protocol->total) {
//                    user_ptr->end_offset += str_len + 1;
                    return;
                } else {
                    char tmp[BUF_SIZE];
                    strncpy(tmp, user_ptr->read_buf + user_ptr->start_offset, new_protocol->total);
//                    temp[strlen(temp)] = '\n';

                    user_ptr->start_offset += new_protocol->total;
                    total_read -= new_protocol->total;
                    user_ptr->num_end = NEED_LENGTH;
                    new_protocol->message = tmp;


//                    user_ptr->end_offset += str_len + 1;
                    // 함수를 호출해서 마무리 하는 과정
                    printf("message = %s , total = %d , dest = %d\n", new_protocol->message, new_protocol->total,
                           new_protocol->dest);
                    memset(tmp, 0, BUF_SIZE);

                    // 버퍼를 교체하는 작업을 해야한다.
                    switch_buffer(user_ptr);

                }

            }
        }

    }
    // 4보다 많이 읽어왔을때(총길이를 알때)


    // 앞에서 4부터 짤라서 본다.


}

//        else {
//            printf("읽어온 read_buf %s", read_buf);
//
//            printf("\n");
//            write_message(fd, read_buf, strlen(read_buf));
//
//
//            memset(read_buf, 0, sizeof(read_buf));
//        }
//
//        str_len = read(fd, read_buf, BUF_SIZE);
//        if (str_len == 0) {
//            // Ctrl + c 로 인한 종료 요청
////            greeting = generate_greeting(fd, 1);
//            epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
//            exit_user(fd);
//        } else {
//            printf("읽어온 read_buf %s", read_buf);
//
//            //TODO 프로토콜 read할때 처리
//            // if 문으로 분기처리
//
//            // str_len 이 4 보다 작을때 (프로토콜의 총길이를 모를때 처리)
////            struct protocol *new_protocol = decode_protocol(fd, read_buf);
//            // 프로토콜의 총길이를 처음알았을때 user 구조체에 저장하는 코드
//
//            // 현재 offset을 저장하는 함수
//
//            // 모든 길이를 다 읽었다면 write 하는 함수
//
//            //TODO 프로토콜을 파싱하는 함수를 만들고, 파싱한 정보를 토대로 분기 처리
//
//            printf("\n");
//            write_message(fd, read_buf, strlen(read_buf));
//
//
//            memset(read_buf, 0, sizeof(read_buf));
//        }

//    }


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

void switch_buffer(struct user *user) {
    char *new_buf = malloc(BUF_SIZE);
    memset(new_buf, 0, BUF_SIZE);
    int idx = 0;
    for (int i = user->start_offset; i < user->end_offset; i++) {
        new_buf[idx] = user->read_buf[i];
        idx++;
    }

    user->start_offset = 0;
    user->end_offset = idx;

    strcmp(user->read_buf, new_buf);
}