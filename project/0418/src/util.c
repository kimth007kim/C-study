#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "../include/util.h"


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
    return result;
}

void switch_buffer(char *buffer, int *offset) {

//    int new_length = strlen(buffer) - *offset;
//    char *new_buffer = malloc(BUF_SIZE);
//    memmove(new_buffer, buffer + *offset, new_length);
//    *buffer = *new_buffer;
////    memmove(buffer, buffer + *offset, new_length);
//    *offset = new_length;

    int new_length = strlen(buffer) - *offset;
    char *new_buf = malloc(BUF_SIZE);
    strncpy(new_buf, buffer + *offset, new_length);
    memset(buffer, 0, BUF_SIZE);
    strncpy(buffer, new_buf, new_length);
    *offset = new_length;
}

void safe_free(void **ptr) {
    if (*ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}