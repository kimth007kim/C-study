#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>

#define  BUF_SIZE 30

int main(int argc, char *argv[]) {

    fd_set reads, temps;
    int result, str_len;
    char buf[BUF_SIZE];

    struct timeval timeout;

    FD_ZERO(&reads);        //fd_set형 변수를 초기화
    FD_SET(0, &reads);      // fd 0의 위치를 1로 설정에

/*  여기서 시간초기화를 하면 안되는 이유는 select 함수 호출이 끝나게 되면 남은시간으로 변하기 때문
    timeout.tv_sec = 5;
    timeout.tv_usec = 5000;
*/

    while (1) {

        temps = reads;      //temps 에 read를 복사한다.
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        result = select(1, &temps, 0, 0, &timeout);
        if (result == -1) {
            puts("select() error!");
            break;
        } else if (result == 0) {
            puts("Time-out!");
        } else {
            if (FD_ISSET(0, &temps)) {
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                printf("message from console: %s", buf);
            }
        }
    }
    return 0;
}
