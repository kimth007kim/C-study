#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    char *advice[] = {
            "조금 만드 세요.\r\n",
            "꽉끼는 청바지 를 입으 세요 뚱뚱해 보이지 는 않을 겁니다.\r\n",
            "한 마디만 하겠 습니다 옳지 않아요.\r\n",
            "오늘 만 이라도 솔직해 지세요. 직장 상사 에게 '진정' 생각 하고 있는걸 말 하세요.\r\n",
            "그 머리 모양은 아니지 싶습 니다.\r\n",
    };

    int listener_d = socket(PF_INET,SOCK_STREAM,0);

    struct sockaddr_in name;
    name.sin_family= PF_INET;
    name.sin_port=(in_port_t)htons(3000);
    name.sin_addr.s_addr= htonl(INADDR_ANY);
    int c = (listner)



    printf("Hello, World!\n");
    return 0;
}
