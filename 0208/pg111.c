#include <stdio.h>

int main() {
//    char *cards = "JQK";
    char cards[] = "JQK";
    printf(cards);
    printf("\n");

    char a_card = cards[2];
//    printf(a_card);
    cards[2]=cards[1];
    cards[1]=cards[0];
    cards[0]=cards[2];
    cards[2]=cards[1];
    cards[1]=a_card;
    puts(cards);
    printf("\n");
    puts(cards);




    //포인터 변수

}
