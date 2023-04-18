//
// Created by kim on 23. 3. 13.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include <netinet/in.h>
#include <time.h>
#include "../include/util.h"
#include "../include/protocol.h"
#include "../include/user.h"
#include "../include/server_io.h"

//HTTP
/* HEADER + BODY */

//WJP2
/* HEADER + BODY */
/* 12byte + ~~ */
/* 4byte = magic number */
/* 10byte = header  flag */

//    4Byte  + 4Byte + Message Length Byte
// Body의 길이 + 타겟   +  문자열 길이

int
decode_and_handle_protocol(int host_type, int epfd, int fd, struct protocol *new_protocol, int *read_status,
                           char *read_buf, int total_length, char *message, int *message_offset, int *read_idx) {

    int current_read_idx = 0;
    int completed = 0;
    while (total_length > 0) {
        if (*read_status == REQUIRE_HEADER) {
            if (total_length < 9) {
                if (completed == 0)
                    return 0;
                return current_read_idx;
            } else {
                memset(new_protocol, 0, sizeof(struct protocol));
                char temp_length[5];

                strncpy(temp_length, read_buf + current_read_idx, 4);
                temp_length[4] = '\n';
                int length = atoi(temp_length);
                new_protocol->message_length = length;
                current_read_idx += 4;

                new_protocol->mode = read_buf + current_read_idx;
                current_read_idx += 1;

                new_protocol->destination = read_buf + current_read_idx;
                current_read_idx += 4;


                memset(temp_length, 0, 5);
                total_length -= 9;
                *read_status = REQUIRE_BODY;
            }
        } else {
            if (total_length < new_protocol->message_length) {
                *read_status = REQUIRE_HEADER;
                if (completed == 0)
                    return 0;

                return current_read_idx - 9;
            } else {
                new_protocol->message = read_buf + current_read_idx;
                current_read_idx += new_protocol->message_length;
                total_length -= new_protocol->message_length;

                destination_handler(fd, epfd, new_protocol, message, message_offset, &current_read_idx);
                *read_idx += new_protocol->message_length + 9;
                *read_status = REQUIRE_HEADER;
                completed += 1;
            }
        }
    }
    return current_read_idx;
}

int
handle_protocol_decoding(int host_type, int epfd, int fd, struct protocol *new_protocol,
                         int *read_status,
                         char *read_buf, int *offset, int total_length, char *message, int *message_offset) {
    int current_read_idx = 0;
    int completed = 0;
    while (total_length > 0) {
        if (*read_status == REQUIRE_HEADER) {
            if (total_length < 9) {
                if (completed == 0)
                    return 0;
                return current_read_idx;
            } else {
                memset(new_protocol, 0, sizeof(struct protocol));
                char temp_length[5];

                strncpy(temp_length, read_buf, 4);
                temp_length[4] = '\n';
                int length = atoi(temp_length);
                new_protocol->message_length = length;

                current_read_idx += 4;
                new_protocol->mode = read_buf + current_read_idx;

                current_read_idx += 1;
                new_protocol->destination = read_buf + current_read_idx;


                memset(temp_length, 0, 5);
                current_read_idx += 4;
                total_length -= 9;
                *read_status = REQUIRE_BODY;
            }
        } else {
            if (total_length < new_protocol->message_length) {
                *read_status = REQUIRE_HEADER;
                if (completed == 0)
                    return 0;
                return current_read_idx - 9;
            } else {
                char *output_message = malloc(BUF_SIZE);
                new_protocol->message = read_buf + current_read_idx;
                current_read_idx += new_protocol->message_length;
                total_length -= new_protocol->message_length;

                sprintf(output_message, "%.*s", new_protocol->message_length, new_protocol->message);
//                fputs(output_message, stdout);
                printf("%s \n", output_message);
                *read_status = REQUIRE_HEADER;
                completed += 1;
            }
        }
    }
    return current_read_idx;
}

char *encode_protocol(char *read_buf, int length, char *mode, int target) {


//    printf("여기서 받은 %s \n", read_buf);
    char *total = malloc(4);
    char *dest = malloc(4);
    char *result = malloc(PROTOCOL_SIZE);
    // TODO 메세지의 총 길이가 9999를 넘어가면 어떻게 해야할지 정하도록 하자
    // 총 문자열의 길이를 char 형으로 변경
    total = int_to_charzero(length);
    // destination을 char형으로 변형
    dest = int_to_charzero(target);
    // 총길이 + destination + message를 하는 sprintf()
    sprintf(result, "%s%s%s%s", total, mode, dest, read_buf);
//    result[strlen(result)] = '0';
//    printf(" 완성된 프로토콜 %s\n", result);
    memset(total, 0, sizeof(total));
    memset(dest, 0, sizeof(dest));
//    memset(result,0,sizeof(result));
    return result;
}

void encode_kd_protocol(char *read_buf, int target, char *output_str) {
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


/*
    struct kd_protocol *new_kd_protocol = malloc(sizeof(struct kd_protocol));
    memset(new_kd_protocol, 0, sizeof(struct kd_protocol));

    // Read the first 2 bytes (10 bits) into message_length
    new_kd_protocol->message_length = (read_buf[0] << 2) | (read_buf[1] >> 6);

    // Read the next 2 bytes (11 bits) into destination
    new_kd_protocol->destination = ((read_buf[1] & 0x3F) << 5) | (read_buf[2] >> 3);

    // Read the remaining bytes into message
    new_kd_protocol->message = malloc(new_kd_protocol->message_length + 1);
    memcpy(new_kd_protocol->message, read_buf + 3, new_kd_protocol->message_length);
    new_kd_protocol->message[new_kd_protocol->message_length] = '\0';
*/

}

char *generate_time() {
    time_t timer = time(NULL);
    struct tm *t = localtime(&timer);
    char *result = malloc(30);
    strftime(result, BUF_SIZE, "%Y/%m/%d %H:%M:%S", t);

    return result;
}

char *generate_message(int fd, char *buf, int message_length) {
    char *message = malloc(sizeof(char) * PROTOCOL_SIZE);
    char *time_str;
    time_str = generate_time();
    sprintf(message, "[%s] %s : %.*s", time_str, user_list[fd]->name, message_length, buf);

    return message;
}

char *generate_greeting_protocol(int fd, int flag) {
    char *message = malloc(sizeof(char) * PROTOCOL_SIZE);
    char *time_str;
    char *hey = "입장하셨습니다";
    char *bye = "퇴장하셨습니다";

    time_str = generate_time();
    if (flag == 0) {
        sprintf(message, "[%s] %s 님이 %s.", time_str, user_list[fd]->name, hey);
    } else {
        sprintf(message, "[%s] %s 님이 %s.", time_str, user_list[fd]->name, bye);
    }
    int message_length = strlen(message);

    char *result = encode_protocol(message, message_length, CHAR_BROADCAST, 9999);


    return result;
}