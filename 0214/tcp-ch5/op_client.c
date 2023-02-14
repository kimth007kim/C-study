#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

#define BUF_SIZE 0124
#define RLT_SIZE 4  //피 연산자의 바이트 수
#define OPSZ 4 // 연산결과의 바이트

void error_handling(char * message);
void print_array(char arr[],int size);
int main(int argc, char *argv[]) {
    int sock;
    char opmsg[BUF_SIZE];   //데이터 송수신을 위한 데이터 공간은 배열을 기반으로 생성

    int result, opnd_cnt,i;
    struct sockaddr_in serv_adr;

    if(argc!=3){
        printf("Usage : %s <IP> <port>\n",argv[0]);
        exit(1);
    }

    //소켓 생성
    sock =socket(PF_INET,SOCK_STREAM,0);
    if (sock==-1){
        error_handling("socket() error");
    }

    memset(&serv_adr,0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port=htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr *)&serv_adr,sizeof(serv_adr))==-1)
        error_handling("connect() error!");
    else
        puts("Connected.......");



    fputs("Operand count: ",stdout);
    scanf("%d",&opnd_cnt);      // 피연산자 개수를 입력 받는다.
    fputs("입력받은 피연산자 개수 ",stdout);
    fputc((char)opnd_cnt,stdout);
    fputc('\n',stdout);
    opmsg[0]=(char)opnd_cnt;

    print_array(opmsg,BUF_SIZE);

    for(i=0;i<opnd_cnt;i++){
        printf("Operand %d: ",i+1);
        scanf("%d",(int *)&opmsg[i*OPSZ+1]);
    }

    fgetc(stdin);
    fputs("Operator: ",stdout);
    scanf("%c",&opmsg[opnd_cnt* OPSZ+1]);
    write(sock,opmsg,opnd_cnt*OPSZ+2);

    print_array(opmsg,BUF_SIZE);


    read(sock,&result,RLT_SIZE);

    printf("Operation result : %d \n",result);
    close(sock);
    return 0;



    //바인딩

    //listen

    // accept

    //read,write

    //close

    return 0;
}
void error_handling(char * message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);


}


void print_array(char arr[],int size){
    printf("start array");
    for (int i = 0; i < size; i++)    // 배열의 요소 개수만큼 반복
    {
        fputc(arr[i],stdin);    // 배열의 인덱스에 반복문의 변수 i를 지정
    }
    printf("\n");
}




