#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/epoll.h>
#include<time.h>
#include <ctype.h>

#include"include/util.h"
//#include"include/linkedlist.h"
#include"include/protocol.h"
#include "include/epoll.h"
#include "include/server.h"
#include "include/user.h"


char *generate_time();

//struct user {
//    //TODO 각각의 유저별로 read_buf 와 write_buf를 따로 두는 식으로 설계
//
//    char *name;
//    int fd;
//    int total_read_length;
//    int num_end;        // 숫자가 다들어 왔는지 확인하는 변수
//    int current_read_pos;
//    char *read_buf[PROTOCOL_SIZE];
//    char *write_buf[PROTOCOL_SIZE];
//};

void enter_user(int fd);

void exit_user(int fd);


void generate_greeting(int fd, int flag);

void generate_message(int fd, char *buf);

void write_message(int fd, char *buf, int len);


void show_users();


// 유저의 fd를 관리하는 링크드리스트, 유저의 구조체를 가지는 배열 를 선언 및 초기화
//Node *user_link = NULL;
//struct user *user_list[MAX_USERS];
//int current_users = 0;

int main() {

    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    int str_len, option_len;
    socklen_t address_size;
    int option;
    // epoll 설정
    int epfd, event_cnt;
    struct epoll_event *ep_events;
    for (int i = 0; i < MAX_USERS; i++) {
        user_list[i] = NULL;
    }
    server_socket = socket(PF_INET, SOCK_STREAM, 0);
    //소켓 재할당 설정
    option_len = sizeof(option);
    option = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (void *) &option, option_len);


    memset(&server_address, 0, sizeof(server_address));


    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = 9190;

    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        error_handling("bind() error");
    }

    if (listen(server_socket, MAX_USERS) == -1) {
        error_handling("listen() error");
    }

    epfd = epoll_create(EPOLL_SIZE);
    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
    create_add_event(epfd, server_socket, EPOLLIN);


    while (1) {

        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        if (event_cnt == -1) {
            puts("epoll_wait() error!");
            break;
        }
        for (int i = 0; i < event_cnt; i++) {
            char buf[BUF_SIZE] = {0,};
            if (ep_events[i].data.fd == server_socket) {
                //accept
                print_users(user_link);
                address_size = sizeof(client_address);
                client_socket = accept(server_socket, (struct sockaddr *) &client_address, &address_size);
                if (client_socket == -1) {
                    puts("accept() error!");
                    continue;
                }
                create_add_event(epfd, client_socket, EPOLLIN);

                enter_user(client_socket);
                generate_greeting(client_socket, 0);

                //accept!!
//              TODO  accept_listener(client_socket);


            } else {
                //msg
                int targetFd = ep_events[i].data.fd;
                str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
                // network
                //=====================================
//            TODO    message_listener(targetFd,ep_events[i].data.event, buf);


                // parsing

                //1. message 5ro  loop
                // struct msg( int legnth, bytes char* msg ) N ,1

                // broadCast( msg );{
                //msg->length, char*
                //2. meesage 1 -- run  type, length, msg  if( type ==1 ), type==2 () =

                // protocol check

                printf("buf: %s  문자열의 길이는 %d 입니다.\n", buf, str_len);


//             TODO   messageBuffer->get(targetFd)
                if (str_len == 0) {
                    // Ctrl + c 로 인한 종료 요청
                    generate_greeting(ep_events[i].data.fd, 1);

                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    exit_user(ep_events[i].data.fd);

                    print_users(user_link);

                } else {
                    //TODO 프로토콜을 파싱하는 함수를 만들고, 파싱한 정보를 토대로 분기 처리
                    struct protocol *new_protocol = decode_protocol(ep_events[i].data.fd, buf);
//                    generate_message(ep_events[i].data.fd, buf);
                    memset(buf, 0, sizeof(buf));
                }
            }
        }
    }
    close(server_socket);
    return 0;

}

void enter_user(int fd) {
    current_users += 1;
    struct user *new_user = malloc(sizeof(struct user));
    new_user->fd = fd;
    new_user->name = malloc(MAX_NAME_SIZE);
    int str_len = read(fd, new_user->name, MAX_NAME_SIZE);
    new_user->name[str_len] = '\0';
    user_list[fd] = new_user;

    user_link = add_node(user_link, fd);
    show_users();
}

void exit_user(int fd) {
    if (user_link == NULL) {
        return;
    }
    if (user_list[fd]->fd == fd) {
        user_list[fd] = NULL;
        // 링크드리스트에 해당 소켓을 제거
        user_link = remove_node(user_link, fd);
        current_users -= 1;
        close(fd);
    }

}

void generate_message(int fd, char *buf) {
    char *message = malloc(sizeof(char) * PROTOCOL_SIZE);
    char *time_str;
    time_str = generate_time();
    sprintf(message, "[%s] %s : %s", time_str, user_list[fd]->name, buf);
    int message_length = strlen(message);
    write_message(fd, message, message_length);
}

void generate_greeting(int fd, int flag) {
    char *message = malloc(sizeof(char) * PROTOCOL_SIZE);
    char *time_str;
    char *hey = "입장하셨습니다";
    char *bye = "퇴장하셨습니다";

    time_str = generate_time();
    if (flag == 0) {
        sprintf(message, "[%s] %s 님이 %s.\n", time_str, user_list[fd]->name, hey);
    } else {
        sprintf(message, "[%s] %s 님이 %s.\n", time_str, user_list[fd]->name, bye);
    }
    int message_length = strlen(message);
    write_message(fd, message, message_length);
}

void write_message(int fd, char *buf, int len) {
    Node *temp_user_link = user_link;
    while (temp_user_link != NULL) {
        if (user_list[temp_user_link->fd]->fd != fd) {
            printf("%d 번님 %s 메시지입니다. ", user_list[temp_user_link->fd]->fd, buf);
            write(user_list[temp_user_link->fd]->fd, buf, len);
        }
        temp_user_link = temp_user_link->next;
    }
    printf("\n");
}

void show_users() {
    Node *temp_user_link = user_link;
    while (temp_user_link != NULL) {
        printf(" %d번의 %s님", user_list[temp_user_link->fd]->fd, user_list[temp_user_link->fd]->name);
        temp_user_link = temp_user_link->next;
    }
    printf("\n");

}

char *generate_time() {
    time_t timer = time(NULL);
    struct tm *t = localtime(&timer);
    char *result = malloc(30);
    strftime(result, BUF_SIZE, "%Y/%m/%d %H:%M:%S", t);

    return result;
}
