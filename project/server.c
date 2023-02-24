#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define BUF_SIZE 100

void error_handling(char * message);
int main() {

    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    fd_set reads,cpy_reads;
    int fd_max,fd_num,i,str_len;
    socklen_t adr_sz;
    struct timeval timeout;
    char buf[BUF_SIZE];

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr,0,sizeof (serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
//    serv_adr.sin_port=htons(atoi("9190"));
    serv_adr.sin_port=9190;

    if(bind(serv_sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr))==-1){
        error_handling("bind() error");
    }

    if(listen(serv_sock,5)==-1){
        error_handling("listen() error");
    }
    FD_ZERO(&reads);
    FD_SET(serv_sock,&reads);
    fd_max= serv_sock;


    while(1){
        cpy_reads = reads;
        timeout.tv_sec=5;
        timeout.tv_usec=5000;

        if((fd_num= select(fd_max+1,&cpy_reads,0,0,&timeout))==-1){
            break;
        }
        if(fd_num==0){
            continue;
        }
        for(i=0; i<fd_max+1;i++){
            if(FD_ISSET(i,&cpy_reads)){
                if(i==serv_sock){   // connection request
                    adr_sz= sizeof(clnt_adr);
                    clnt_sock= accept(serv_sock,(struct sockaddr*)&clnt_adr,&adr_sz);

                    FD_SET(clnt_sock,&reads);
                    if(fd_max<clnt_sock)
                        fd_max=clnt_sock;
                    printf("connected client: %d\n",clnt_sock);
                }else{ //read message
                    str_len=read(i,buf,BUF_SIZE);
                    if(str_len==0){
                        FD_CLR(i,&reads);
                        close(i);
                        printf("closed client :%d \n",i);
                    }else{

                        for(int j=4; j<fd_max +1;j++){    //여러 클라이언트에게 쏴주는것
                            write(j,buf,str_len);
                        }
//                        write(i,buf,str_len);
                    }

                }
            }
        }
    }





    close(serv_sock);
    return 0;

}

void error_handling(char * message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);

}
