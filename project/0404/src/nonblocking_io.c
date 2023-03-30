#include<errno.h>
#include "../include/util.h"
#include <stdio.h>
#include <unistd.h>

void nio_read(int fd, char *buf, int *require_cnt) {

    int read_rtn = read(fd, buf, sizeof(buf));

    if (read_rtn < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return;
        } else {
            error_handling("read()시 에러 발생");
        }

    } else if (read_rtn == 0) {
        printf("----- Socket close\n");
        close(fd);
        return;
    } else {
        printf("----- read : %s\n", buf);
    }


}


void nio_write(int fd, char *buf) {
    int read_rtn = write(fd, buf, sizeof(buf));
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
        // 블로킹 걸릴 상황이었다. 송신을 안 했다.
//        epoll_ctl(epfd,EPOLL_CTL_ADD,listen_fd, &event);
        return;
    }

//    if (r == OK)
//    {
//        // 보내기 성공에 대한 처리
//    }
//    else
//    {
//        // 보내기 실패에 대한 처리
//    }

}