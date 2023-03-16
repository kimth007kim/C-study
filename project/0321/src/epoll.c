#include<sys/epoll.h>
#include<stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/util.h"
#include "../include/protocol.h"
#include "../include/linkedlist.h"
#include "../include/server.h"
#include "../include/client.h"

void event_loop(void(*func)(int, int, int, int,char*,char*), int server_socket, int epfd) {

    int event_cnt;
    struct epoll_event *ep_events;

    printf(" fd는 = %d",server_socket);

    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
    char *read_buf=malloc(sizeof(BUF_SIZE));
    char *write_buf=malloc(sizeof(BUF_SIZE));
    while (1) {
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        if (event_cnt == -1)
            return;
        memset(read_buf,0,sizeof(BUF_SIZE));
        memset(write_buf,0,sizeof(BUF_SIZE));
        for (int i = 0; i < event_cnt; i++) {
            if (ep_events[i].data.fd == server_socket) {
                func(0, server_socket, epfd, ep_events[i].data.fd,read_buf,write_buf);
            } else {
                func(1, server_socket, epfd, ep_events[i].data.fd,read_buf,write_buf);

            }
        }
    }
}


struct epoll_event *generate_event(int fd, int event) {
    struct epoll_event *new_event = malloc(sizeof(struct epoll_event));
    new_event->events = event;
    new_event->data.fd = fd;

    return new_event;

}

void create_add_event(int epfd, int fd, int event) {
    struct epoll_event *new_event = generate_event(fd, event);
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, new_event);

}


