#include <stdio.h>

int main() {
    char food[5];
    printf(food);
    printf("좋아하는 음식 이름을 입력하세요.");
    fgets(food, sizeof(food),stdin);
    printf(food);
//    printf("Hello, World!\n");
    return 0;
}
