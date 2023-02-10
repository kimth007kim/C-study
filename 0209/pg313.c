#include <stdio.h>
# include<stdlib.h>

typedef struct island {

    char *name;
    char *opens;
    char *closes;
    struct island *next;

} island;

void display(island *start) {
    island *i = start;
    for (; i != NULL; i = i->next) {
        printf("섬 이름: %s\n 운행 시간: %s-%s\n", i->name, i->opens, i->closes);
    }

}

island *create(char *name) {
    island *i = malloc(sizeof(island));
    i->name =name;
    i->opens ="09:00";
    i->closes ="17:00";
    i->next=NULL;

    return i;
}

int main() {

    island amity = {"Amity", "09:00", "17:00", NULL};
    island craggy = {"Craggy", "09:00", "17:00", NULL};
    island isla_nubla = {"Isla_Nubla", "09:00", "17:00", NULL};
    island shutter = {"Shutter", "09:00", "17:00", NULL};

    amity.next = &craggy;
    craggy.next = &isla_nubla;
    isla_nubla.next = &shutter;


    island skull = {"Skull", "09:00", "17:00", NULL};
    isla_nubla.next = &shutter;
    skull.next = &shutter;
    display(&amity);


    return 0;
}
