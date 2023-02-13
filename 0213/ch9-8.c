// 다른 함수의 변수를 이름으로 사용

#include<stdio.h>

void swap();

int main() {
    int a = 10, b = 20;

    swap();
    printf("a= %d b= %d\n", a, b);

    return 0;

}


void swap() {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;

}