#include<stdio.h>
#include<time.h>


int main() {
    time_t timer = time(NULL);
    struct tm *t = localtime(&timer);

    printf("현재 년: %d\n",t->tm_year+1900);
    printf("현재 월: %d\n",t->tm_mon+1);
    printf("현재 일: %d\n",t->tm_mday);
    printf("현재 시: %d\n",t->tm_hour);
    printf("현재 분: %d\n",t->tm_min);
    printf("현재 초: %d\n",t->tm_sec);

    printf(" 안녕하세요");

    

    return 0;

}
