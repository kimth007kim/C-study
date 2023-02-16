#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void print_str(char **);

int main(int argc, char **argv) {
    char temp[80];
    char **str;
    int max;
    int i;

    max = atoi(argv[1]);
    str = (char **) malloc(((max + 1) * sizeof(char *)));
    i = 0;
    while (1) {

        printf("문자열을 입력하세요.");
        gets(temp);
        if (temp[0] == '\0')break;

        str[i] = (char *) malloc(strlen(temp) + 1);
        strcpy(str[i], temp);
        i++;
        if (i == max) {
            printf("문자열 입력이 최댓값을 모두 채웠습니다.");
            break;
        }
    }
    str[i] = 0;
    print_str(str);
    i = 0;
    while (str[i] != 0) {
        free(str[i]);
        i++;
    }
    free(str);
    return 0;
}

void print_str(char **ps) {
    while (*ps != 0) {
        printf("%s\n", *ps);
        ps++;
    }
}
