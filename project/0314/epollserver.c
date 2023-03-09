#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/epoll.h>
#include<time.h>

#include"include/util.h"
#include"include/linkedlist.h"


//#include"include/hashtable.h"

#define BUF_SIZE 100
#define EPOLL_SIZE 2000
#define MAX_NAME_SIZE 30
#define MAX_USERS 2000
#define TOTAL_MESSAGE_SIZE 1000

char *generate_time();

struct user {
    char *name;
    int fd;
};

void write_greeting(int fd, int flag);

//void exit_user(int fd, struct user *user_list[], int *current_users);
void exit_user(int fd, int *current_users);

void show_users();

void write_message(int fd, char *buf);

// 유저의 fd를 관리하는 링크드리스트, 유저의 구조체를 가지는 배열 를 선언 및 초기화
Node *user_link = NULL;
struct user *user_list[MAX_USERS];

int main() {

    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    int str_len, option_len;


    socklen_t address_size;
    char nickname[MAX_NAME_SIZE];
    int current_users = 0;
    int option;

    // epoll 설정
    int epfd, event_cnt;
    struct epoll_event *ep_events;
    struct epoll_event event;


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
    event.events = EPOLLIN;
    event.data.fd = server_socket;
    epoll_ctl(epfd, EPOLL_CTL_ADD, server_socket, &event);

    while (1) {

        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        if (event_cnt == -1) {
            puts("epoll_wait() error!");
            break;
        }
        for (int i = 0; i < event_cnt; ++i) {
            char buf[BUF_SIZE] = {0,};
            if (ep_events[i].data.fd == server_socket) {
                print_users(user_link);
                address_size = sizeof(client_address);
                client_socket = accept(server_socket, (struct sockaddr *) &client_address, &address_size);
                if (client_socket == -1) {
                    puts("accept() error!");
                    continue;
                }
                event.events = EPOLLIN;
                event.data.fd = client_socket;
                epoll_ctl(epfd, EPOLL_CTL_ADD, client_socket, &event);
                current_users += 1;

                struct user *new_user = malloc(sizeof(struct user));

                new_user->fd = client_socket;
                new_user->name = malloc(MAX_NAME_SIZE);
                str_len = read(client_socket, new_user->name, MAX_NAME_SIZE);
                new_user->name[str_len] = '\0';
                user_list[client_socket] = new_user;

                printf("%d\n", client_socket);
                // 링크드리스트에 클라이언트 소켓을 등록
                user_link = add_node(user_link, client_socket);

                print_users(user_link);
                printf(" %s connected client : %d \n", nickname, client_socket);
                write_greeting(client_socket, 0);


            } else {
                memset(buf, 0, sizeof(buf));
                str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
                printf("문자열의 길이는 %d 입니다.\n", str_len);

                if (str_len == 0 || strcmp(buf,"\n") ) { // TODO 왜 문자열이 1일까?
                    // 종료 요청
                    write_greeting(ep_events[i].data.fd, 1);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    exit_user(ep_events[i].data.fd, &current_users);

                    print_users(user_link);

                } else {
                    printf("메시지 전송 요청");
                    write_message(ep_events[i].data.fd, buf);
                }
            }
        }
    }
    close(server_socket);
    return 0;

}

void write_greeting(int fd, int flag) {

    char message[TOTAL_MESSAGE_SIZE];
    char *time_str;
    char *hey = "입장하셨습니다";
    char *bye = "퇴장하셨습니다";

    time_str = generate_time();
    if (flag == 0) {
        sprintf(message, "[%s] %s 님이 %s.\n", time_str, user_list[fd]->name, hey);
    } else {
        sprintf(message, "[%s] %s 님이 %s.\n", time_str, user_list[fd]->name, bye);
    }

    Node *temp_user_link = user_link;
    while (temp_user_link != NULL) {
        if (user_list[temp_user_link->fd]->fd != fd) {
            write(user_list[temp_user_link->fd]->fd, message, strlen(message));
        }
        temp_user_link = temp_user_link->next;
    }


}

void exit_user(int fd, int *current_users) {
    if (user_link == NULL) {
        return;
    }
    if (user_list[fd]->fd == fd) {
        user_list[fd] = NULL;
        // 링크드리스트에 해당 소켓을 제거
        user_link = remove_node(user_link, fd);
        *current_users -= 1;
        close(fd);
    }

}


void write_message(int fd, char *buf) {
    print_users(user_link);
    if (user_link == NULL) {
        return;
    }
    char message[TOTAL_MESSAGE_SIZE];
    char *time_str;
    time_str = generate_time();
    sprintf(message, "[%s] %s : %s", time_str, user_list[fd]->name, buf);

    Node *temp_user_link = user_link;
    while (temp_user_link != NULL) {
        if (user_list[temp_user_link->fd]->fd != fd) {
            write(user_list[temp_user_link->fd]->fd, message, strlen(message));
        }
        temp_user_link = temp_user_link->next;
    }


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