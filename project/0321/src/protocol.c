//
// Created by kim on 23. 3. 13.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include "../include/util.h"
#include "../include/protocol.h"

//HTTP
/* HEADER + BODY */

//WJP2
/* HEADER + BODY */
/* 12byte + ~~ */
/* 4byte = magic number */
/* 10byte = header  flag */


char *encode_protocol(char *read_buf, int target) {
    //4Byte+4Byte+Message Length Byte
    // c띄어쓰기(2byte) +타겟(4byte)+ 문자열길이

    // TODO 프로토콜 생성해서 붙이기
    // TODO  추후에 target 을 통해서 목적지를 변경하도록 구현
    char *total = malloc(sizeof(4));
    char *dest = malloc(sizeof(4));
    char *result = malloc(sizeof(char) * PROTOCOL_SIZE);


    int message_length = strlen(read_buf);
    // 메세지의 총 길이가 9999를 넘어가면 어떻게 해야할지 정하도록 하자
    printf("message_length = %d", message_length);
    //총 문자열의 길이를 char 형으로 변경
    total = int_to_charzero(message_length);
    printf("total = %s", total);
    // destination을 char형으로 변형
    dest = int_to_charzero(target);
    printf("dest = %s", dest);

    // 총길이 + destination + message를 하는 sprintf()
    sprintf(result, "%s%s%s", total, dest, read_buf);

    printf(result);
    return result;
}

struct protocol *decode_protocol(int fd, char *buf) {
    int protocol_size = strlen(buf);
    //TODO 덜들어오면 덜들어온것을 처리하는 구문을 작성하도록하자
    struct protocol *new_protocol = malloc(sizeof(struct protocol));
    if (new_protocol == NULL) {
        return NULL;
    }
    memset(new_protocol, 0, sizeof(struct protocol));
    char *num = malloc(sizeof(char) * 4);
    char *target = malloc(sizeof(char) * 4);
    char *message = malloc(sizeof(char) * PROTOCOL_SIZE);
    memset(num, 0, sizeof(char) * 5);
    memset(target, 0, sizeof(char) * 5);
    memset(message, 0, sizeof(char) * (PROTOCOL_SIZE + 1));
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
                free(num);
                free(target);
                free(message);
                free(new_protocol);
                return NULL;
            }
        } else {
            message[idx] = buf[i];
            idx += 1;
        }
    }
//    new_protocol->total = atoi(num);
//    new_protocol->target = atoi(target);
//    new_protocol->message = message;
    // 여기에 덜받았을 경우에 분기 처리

    printf("%s %s %s 프로토콜 해독 완료\n", message, num, target);
    free(num);
    free(target);
    free(message);
    return new_protocol;
}