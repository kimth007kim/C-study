#ifndef PROTOCOL_H
#define PROTOCOL_H
/**
 * total : 프로토콜 에서 메세지의 총길이
 * dest : 목적지에 대한 변수 (0 일시 브로드 캐스트)
 * message : 클라이언트가 보낸 메시지
 */

/**  destination 의 정의 */
#define DESTINATION_ENTER "9001"
#define DESTINATION_BROADCAST "9999"
#define DESTINATION_EXIT "9002"

#define IDX_REGISTER 0
#define IDX_BROADCAST 1
#define IDX_EXIT "2"

#define CHAR_REGISTER "0"
#define CHAR_BROADCAST "1"
#define CHAR_EXIT "2"

struct protocol {
    int message_length;
    char *mode;
    char *destination;
    char *message;
};

struct kd_protocol {
    unsigned int message_length: 10; //1024
    unsigned int destination: 11; //2048
    char *message;
};


char *encode_protocol(char *read_buf, int length, char *mode, int target);

void encode_kd_protocol(char *read_buf, int target, char *output_str);

int client_protocol_handler(int host_type, int epfd, int fd, struct protocol *new_protocol,
                             int *read_status,
                             char *read_buf, int total_length);

int server_protocol_handler(int epfd, int fd, struct protocol *new_protocol,
                               int *read_status,
                               char *read_buf, int total_length, char *message, int *message_offset, int *read_idx);

char *generate_time();

char *generate_message(int fd, char *buf, int message_length);

char *generate_greeting_protocol(int fd, int flag);

#endif /* PROTOCOL_H */