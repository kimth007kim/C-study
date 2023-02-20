#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void (*old_fun)(int);

void sigint_handler(int signo){
    printf("you pressed Ctrl -C!!\n");
    printf("once again it will shut down.\n");
    signal(SIGINT,old_fun);
}

int main(){
    old_fun= signal(SIGINT,sigint_handler);
    while(1){
        printf("keep running\n");
        sleep(1);
    }
	return 0;
}

