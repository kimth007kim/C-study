#include <stdio.h>
#include <stdlib.h>

int main() {
    char card_name[3];
    printf("카드 이름을 입력 하세요: ");
    scanf("%2s", card_name);
    int val = 0;
    if (card_name[0] == 'K') {
        val = 10;
    } else if (card_name[0] == 'Q') {
        val = 10;
    } else if (card_name[0] == 'J') {
        val = 10;
    } else if (card_name[0] == 'A') {
        val = 11;
    } else {
        val = atoi(card_name);
    }

    if (val >= 3 && val <= 6) {
        puts("카운트를 하나 올립니다.");
    } else if (val == 10) {
        puts("카운트를 하나 내립니다.");
    }
    return 0;
}
