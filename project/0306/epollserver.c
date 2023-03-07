#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/epoll.h>

#include<time.h>

#include"include/util.h"
#include"include/hashtable.h"

#define BUF_SIZE 100
#define EPOLL_SIZE 50
#define MAX_NAME_SIZE 30
#define MAX_USERS 2000

char *generate_time();

struct user {
    char *name;
    int fd;
};

void send_greetings(int client_socket);

void exit_user(int fd, struct user *user_list[], Hashtable *user_num,int *current_users);

void show_users(struct user *user_list[]);

int main() {

    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    int i, str_len, optlen;
    socklen_t adr_sz;
    char nickname[MAX_NAME_SIZE];
    int current_users;

    // epoll 설정
    int epfd, event_cnt;
    struct epoll_event *ep_events;
    struct epoll_event event;

    struct user *user_list[MAX_USERS];

    Hashtable user_num = {{NULL}};


    int option;

    server_socket = socket(PF_INET, SOCK_STREAM, 0);

    //소켓 재할당 설정
    optlen = sizeof(option);
    option = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (void *) &option, optlen);


    memset(&server_address, 0, sizeof(server_address));


    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = 9190;

    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        error_handling("bind() error");
    }

    if (listen(server_socket, 5) == -1) {
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
        for (i = 0; i < event_cnt; ++i) {
            char buf[BUF_SIZE] = {0,};
            if (ep_events[i].data.fd == server_socket) {
                adr_sz = sizeof(client_address);
                client_socket = accept(server_socket, (struct sockaddr *) &client_address, &adr_sz);
                if (client_socket == -1) {
                    puts("bind() error!");
                    continue;
                }
                event.events = EPOLLIN;
                event.data.fd = client_socket;
                epoll_ctl(epfd, EPOLL_CTL_ADD, client_socket, &event);

                add(&user_num, client_socket);

                current_users += 1;

                struct user *new_user = malloc(sizeof(struct user));
                new_user->fd = client_socket;
                new_user->name = malloc(MAX_NAME_SIZE);
                str_len = read(client_socket, new_user->name, MAX_NAME_SIZE);
                new_user->name[str_len] = '\0';
                user_list[client_socket] = new_user;


                show_users(user_list);
                printf(" %s connected client : %d \n", nickname, client_socket);
            } else {

                str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
                if (str_len == 0) {
                    // 종료 요청


                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    exit_user(ep_events[i].data.fd, user_list, &user_num,&current_users);
//                    remove_key(&user_num, ep_events[i].data.fd);
//                    current_users -= 1;
//                    close(ep_events[i].data.fd);


                    printf("close client : %d \n ", ep_events[i].data.fd);
                    show_users(user_list);
                    printf("현재 유저 수 %d ", current_users);


                } else {
                    int *current = malloc(sizeof(int) * TABLE_SIZE);
                    current = generate_set(&user_num);
                    print_set(&user_num);
                    for (int i = 0; i < sizeof(current); i++) {
                        printf("%ld,", current[i]);
                    }
                    printf("%ld\n", sizeof(current));
//                    buf={0,};
                }
            }

        }

    }


    close(server_socket);
    return 0;

}

//void send_greetings(int client_socket) {
//
//    char name[MAX_NAME_SIZE + 1];
//    char greetings[] = "님이 입장하셨습니다!\n";
//    int name_len = read(client_socket, name, sizeof(MAX_NAME_SIZE));
//    name[name_len] = '\0';
//    printf("%s\n", name);
//    strcat(name, greetings);
//    printf("%s\n", name);
//    for (int i = 5; i < client_socket + 1; i++) {
//        write(i, name, strlen(greetings) + name_len);
//    }
//
//}
void exit_user(int fd, struct user *user_list[], Hashtable *user_num,int *current_users) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (user_list[i]->fd == fd) {
            user_list[i]->fd = 0;
            user_list[i]->name = NULL;
            remove_key(&user_num, fd);
            current_users -= 1;
            close(fd);
            break;
        }
    }

}


void show_users(struct user *user_list[]) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (user_list[i] != NULL) {
            printf(" %d번의 %s님", user_list[i]->fd, user_list[i]->name);
        }
    }


}

char *generate_time() {
    time_t timer = time(NULL);
    struct tm *t = localtime(&timer);
    char *result = malloc(30);
    strftime(result, BUF_SIZE, "%Y/%m/%d %H:%M:%S", t);

    return result;
}