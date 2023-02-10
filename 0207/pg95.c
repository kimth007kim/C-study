#include <stdio.h>

void fortune_cookie(char msg[]) {
    printf("메시지는 다음과 같습니다: %s\n",msg);
    printf("메시지는 %li바이트 크기입니다.", sizeof(msg));
}

int main() {
    char quote[]= "Cookies make you fat";
    fortune_cookie(quote);
    return 0;
}
