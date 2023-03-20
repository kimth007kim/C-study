#include<stdio.h>
#include<stdlib.h>
#include <string.h>


void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);

}

int int_to_strlength(int num) {

    char str[20];
    sprintf(str, "%d", num);
    int result = strlen(str);

    return result;
}

char *int_to_charzero(int num) {
    char *result = malloc(5);
    sprintf(result, "%04d", num);
//    result[4]='\n';
    return result;
}