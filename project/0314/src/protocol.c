//
// Created by kim on 23. 3. 13.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include "../include/util.h"

char *generate_protocol(char *read_buf, int target);
struct protocol *parse_protocol(int fd, char *protocol);
struct protocol {
    int total;
    int target;
    char *message;

};

char *generate_protocol(char *read_buf, int target) {
    // TODO 프로토콜 생성해서 붙이기
    // TODO  추후에 target 을 통해서 목적지를 변경하도록 구현
    char *result = malloc(sizeof(char) * PROTOCOL_SIZE);
    int protocol_length = 2;
    int target_length = int_to_strlength(target);

    int total_length = strlen(read_buf) + target_length + protocol_length;
    int body_length = int_to_strlength(total_length);
    //총 문자열의 길이를 계산완료
    total_length += body_length;
    printf(" %d는 총문자열의 길이 입니다. \n", total_length);

//                    프로토콜의 초기화
    sprintf(result, "%d %d %s", total_length, target, read_buf);

    printf("만들어진 프로토콜 [%s]\n", result);
    return result;
}

struct protocol *parse_protocol(int fd, char *buf) {
    //TODO 덜들어오면 덜들어온것을 처리하는 구문을 작성하도록하자

    struct protocol *new_protocol = malloc(sizeof(struct protocol));
    int protocol_size = strlen(buf);
    memset(new_protocol,0,sizeof(new_protocol));
    char *num = malloc(sizeof(char) * 4);
    char *target = malloc(sizeof(char) * 4);
    char *message = malloc(sizeof(char) * PROTOCOL_SIZE);
    memset(num, 0, sizeof(char)*5);
    memset(target, 0, sizeof(char)*5);
    memset(message, 0, sizeof(char) * (PROTOCOL_SIZE+1));
    int space = 0;
    int idx = 0;
    printf("읽어온 프로토콜의 크기 : %d\n", protocol_size);
    for (int i = 0; i < strlen(buf); i++) {
        if (space < 2) {
            if (isspace(buf[i])) {
                idx = 0;
                space += 1;
            } else if (isdigit(buf[i])) {
                if (space == 0) {
                    num[idx] = buf[i];
                } else if (space == 1) {
                    target[idx] = buf[i];
                }
                idx += 1;
            } else {
                new_protocol->total=-1;
                return new_protocol;
            }
        } else {
            message[idx] = buf[i];
            idx += 1;
        }
    }
    new_protocol->total = atoi(num);
    new_protocol->target = atoi(target);
    new_protocol->message=message;
    // 여기에 덜받았을 경우에 분기 처리

    printf("%s %s %s 프로토콜 해독 완료\n", message, num, target);
    free(num);
    free(target);
    free(message);
    return new_protocol;
}