#include <stdio.h>


void swap(int x, int y);

int main(void) {
    int a = 10, b = 20;

    swap(a, b);
    printf("a:%d , b:%d",a,b);
    return 0;
}

void swap(int x , int y){
    int tmp;
    tmp =x;
    x= y;
    y= tmp;


}
