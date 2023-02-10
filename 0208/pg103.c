#include <stdio.h>

void skip(char *msg){
    puts(msg+6);
}
int main() {
    int drinks[] = {4, 2, 3};

    printf("첫 번째 주문: %i병\n", drinks[0]);
    printf("첫 번째 주문: %i병\n", *drinks);

    printf("세 번째 주문: %i병\n",drinks[2]);
    printf("세 번째 주문: %i병\n",*(drinks+2));

    char *msg_from_amy="Don't call me";
    skip(msg_from_amy);

    return 0;
}
//int main(){
//    char food[5];
//    printf("좋아 하는 음식 이름을 입력하세요.");
//    scanf("%s",food);
//    printf("좋아하는 음식:%s\n",food);
//    return 0;
//}