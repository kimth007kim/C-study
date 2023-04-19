#include<sys/epoll.h>
#include<stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../include/util.h"
#include "../include/protocol.h"
#include "../include/linkedlist.h"
#include "../include/server.h"
#include "../include/client.h"

void
event_loop(void(*func)(int, int, struct epoll_event), int server_socket,
           int epfd) {

    int event_cnt;
    struct epoll_event *ep_events;

    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
    while (1) {
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
//        printf("event_cnt == %d \n", event_cnt);

        if (event_cnt == -1) {
            return;
        }

        for (int n = 0; n < event_cnt; ++n) {
            if (ep_events[n].data.fd == 5 | ep_events[n].data.fd == 6) {

                if (ep_events[n].events & EPOLLIN) {
                    printf("fd = %d  EPOLLIN \n", ep_events[n].data.fd);
                }
                if (ep_events[n].events & EPOLLOUT) {
                    printf("fd = %d  EPOLLOUT \n", ep_events[n].data.fd);
                }
            }
        }

        for (int i = 0; i < event_cnt; i++) {
            func(server_socket, epfd, ep_events[i]);
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

void create_modify_event(int epfd, int fd, int event) {
    struct epoll_event *new_event = generate_event(fd, event);
    epoll_ctl(epfd, EPOLL_CTL_MOD, fd, new_event);
}

void create_delete_event(int epfd, int fd) {
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
}

int check_event(int epfd, int fd_to_check, int event) {
    struct epoll_event temp_event;
    temp_event.events = 0; // or any events you want to check
    temp_event.data.fd = event;

// Check if the event is registered for the FD
    int result = epoll_ctl(epfd, EPOLL_CTL_MOD, fd_to_check, &temp_event);
    if (result == 0) {
        return 1;
    } else if (errno == ENOENT) {
        return 0;
    } else {
        error_handling("epoll check error");
    }
}
