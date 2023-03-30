#ifndef PROTOCOL_H
#define PROTOCOL_H
/**
 * total : 프로토콜 에서 메세지의 총길이
 * dest : 목적지에 대한 변수 (0 일시 브로드 캐스트)
 * message : 클라이언트가 보낸 메시지
 */

struct protocol{
    int message_length;
    char *destination;
    char *message;
};

struct kd_protocol{
    unsigned int message_length:10; //1024
    unsigned int destination:11; //2048
    char *message;
};



char *encode_protocol(char *read_buf, int target);
void encode_kd_protocol(char *read_buf, int target,char * output_str);
char *decode_protocol(struct protocol *protocol_ptr);
//struct protocol *decode_protocol(int fd, char *protocol);



#endif /* PROTOCOL_H */