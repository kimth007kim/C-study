#include <stdio.h>
#include <stdlib.h>

int main() {
    char card_name[3];
    char c;
    puts("카드 이름을 입력 하세요: ");
    scanf("%2s", card_name);
    int val = 0;

    switch (card_name[0]) {
        case 'K':
        case 'Q':
        case 'J':
            val = 10;
            break;
        case 'A':
            val = 11;
            break;
        default:
            val = atoi(card_name);
    }
    printf("입력하신 값은 = %i",val);


//    if (card_name[0] == 'K' || card_name[0] == 'Q' || card_name[0] == 'J') {
//        val = 10;
//    } else if (card_name[0] == "A") {
//        val = 11;
//    } else {
//        val = atoi(card_name);
//    }

    return 0;
}
