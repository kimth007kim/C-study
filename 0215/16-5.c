#include<stdio.h>
#include <string.h>


void print_str(char **pps);

int main() {
    char temp[80];
    char *str[21] = {0};
    int i = 0;

    while (i < 20) {
        printf("문자열을 입력하세요: ");
        gets(temp);
        if(strcmp(temp,"end")==0)
        i++;
    }


    return 0;
}

void print_str(char **ps) {
    while (*ps != NULL) {
        printf("%s\n", *ps);
        ps++;
    }
}