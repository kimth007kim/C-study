#include<stdio.h>
#include "my.h"

//
//extern int num1;
//extern int num2;
//
//

int num1 = 20;
int num2 = 100;

void Output() {
    printf("%d와 %d의 합은 %d입니다. \n", num1, num2, Sum(num1, num2));
}

void Output1() {
    printf("%d와 %d의 합은 %d입니다. \n", num1, num2, Sub(num1, num2));
}


int Sum(int a, int b) {
    return a + b;
}

int Sub(int a, int b) {
    return a - b;
}