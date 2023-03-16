#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct protocol{
    char total[4];
    char dest[4];
    char *message[9999];
};
int main() {
    struct protocol *tmp = malloc(sizeof(struct protocol));

    memset(tmp->total, '0', sizeof(tmp->total));
    memset(tmp->dest, '0', sizeof(tmp->dest));

    printf("tmp->total = %s\n ",tmp->total);
    printf("tmp->dest = %s\n ",tmp->dest);
    char total[4];
    char dest[4];

    scanf("%s",dest);
    int temp =atoi(dest);
    if (dest>=0 && temp<=9999){
        printf("%d\n",temp);
    }else{
        return 0;
    }


    return 0;
}