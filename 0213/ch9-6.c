#include<stdio.h>


int main(void){
    int a = 10;
    int *p = &a;
    double *pd;
    pd = p;

    printf("%1f\n",*pd);

//    double b =3.4;
//    double *pb = &b;
//    int *pi ;
//
//    pi = (int *)pb;
//
//    printf("%f\n",(double) *pi);


    return 0;
}
