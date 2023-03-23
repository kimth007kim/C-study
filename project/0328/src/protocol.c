//
// Created by kim on 23. 3. 13.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include <netinet/in.h>
#include "../include/util.h"
#include "../include/protocol.h"

//HTTP
/* HEADER + BODY */

//WJP2
/* HEADER + BODY */
/* 12byte + ~~ */
/* 4byte = magic number */
/* 10byte = header  flag */

//    4Byte  + 4Byte + Message Length Byte
// Body의 길이 + 타겟   +  문자열 길이
char *encode_protocol(char *read_buf, int target) {


//    printf("여기서 받은 %s \n", read_buf);
    char *total = malloc(sizeof(4));
    char *dest = malloc(sizeof(4));
    char *result = malloc(PROTOCOL_SIZE);
    int message_length = strlen(read_buf);
    // TODO 메세지의 총 길이가 9999를 넘어가면 어떻게 해야할지 정하도록 하자
    // 총 문자열의 길이를 char 형으로 변경
    total = int_to_charzero(message_length);
    // destination을 char형으로 변형
    dest = int_to_charzero(target);
    // 총길이 + destination + message를 하는 sprintf()
    sprintf(result, "%s%s%s", total, dest, read_buf);
    result[strlen(result)] = '\0';
    printf(" 완성된 프로토콜 %s\n", result);
    memset(total, 0, sizeof(total));
    memset(dest, 0, sizeof(dest));
//    memset(result,0,sizeof(result));
    return result;
}

void encode_kd_protocol(char *read_buf, int target,char * output_str) {
    struct kd_protocol protocol;
    protocol.message_length = strlen(read_buf);
    protocol.destination = target;
    protocol.message = malloc(strlen(read_buf) + 1);
    strcpy(protocol.message, read_buf);

    int length_bits = 10;
    int length_bytes = length_bits / 8 + ((length_bits % 8) ? 1 : 0);
    int destination_bits = 11;
    int destination_bytes = destination_bits / 8 + ((destination_bits % 8) ? 1 : 0);

    int total_size = (length_bytes + destination_bytes) + strlen(protocol.message);
    char *combined_str = (char *) malloc(total_size);

    // Copy message_length as binary data into combined_str
    unsigned int message_length = protocol.message_length & 0x3FF;
    message_length = htons(message_length);
    memcpy(combined_str, &message_length, length_bytes);

    // Copy destination as binary data into combined_str
    unsigned int destination = protocol.destination & 0x7FF;
    destination = htons(destination);
    memcpy(combined_str + length_bytes, &destination, destination_bytes);

    // Copy message into combined_str
    memcpy(combined_str + length_bytes + destination_bytes, protocol.message, strlen(protocol.message) + 1);

    // Copy combined_str into output_str as a string
    int i;
    for (i = 0; i < total_size; i++) {
        sprintf(output_str + 2 * i, "%02X", (unsigned char) combined_str[i]);
    }
    output_str[2 * i] = '\0';

    // Free the allocated memory
    free(combined_str);
}

void check_combined_str(char *combined_str, int target, char *read_buf) {
    // Extract message_length from combined_str
    unsigned int message_length;
    memcpy(&message_length, combined_str, sizeof(unsigned int));
    message_length = ntohs(message_length) & 0x3FF; // Mask out upper bits

    // Extract destination from combined_str
    unsigned int destination;
    memcpy(&destination, combined_str + sizeof(unsigned int), sizeof(unsigned int));
    destination = ntohs(destination) & 0x7FF; // Mask out upper bits

    // Extract message from combined_str
    char *message = combined_str + 2 * sizeof(unsigned int);

    // Check values
    if (message_length != strlen(read_buf)) {
        printf("Error: message_length is not properly entered.\n");
    }
    if (destination != target) {
        printf("Error: destination is not properly entered.\n");
    }
    if (strcmp(message, read_buf) != 0) {
        printf("Error: message is not properly entered.\n");
    }
}