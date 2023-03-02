#include<stdio.h>
#include<time.h>
#define BUF_SIZE 1024

int main() {
    time_t timer = time(NULL);
    struct tm *t = localtime(&timer);
    char result[1024];

    printf("현재 년: %d\n",t->tm_year+1900);
    printf("현재 월: %d\n",t->tm_mon+1);
    printf("현재 일: %d\n",t->tm_mday);
    printf("현재 시: %d\n",t->tm_hour);
    printf("현재 분: %d\n",t->tm_min);
    printf("현재 초: %d\n",t->tm_sec);

    printf(" 안녕하세요");
    strftime(result,BUF_SIZE,"[%Y/%m/%d %l:%M:%S]",t);

    puts(result);

    return 0;

}
