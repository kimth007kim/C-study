#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include "../include/hashtable.h"


//#define TABLE_SIZE 3500

// 해시 테이블의 버킷을 표현하는 구조체
//typedef struct bucket {
//    int key;
//    struct bucket *next;
//} Bucket;
//
//// 해시 테이블을 표현하는 구조체
//typedef struct hashtable {
//    Bucket *table[TABLE_SIZE];
//} Hashtable;

// 해시 함수
int hash(int key) {
    return key % TABLE_SIZE;
}

// 새로운 버킷을 동적으로 생성하여 반환하는 함수
Bucket *new_bucket(int key) {
    Bucket *b = (Bucket *) malloc(sizeof(Bucket));
    b->key = key;
    b->next = NULL;
    return b;
}

// 해시 테이블에서 키가 key인 원소를 찾아서 반환하는 함수
Bucket *find(Hashtable *ht, int key) {
    int idx = hash(key);
    Bucket *b = ht->table[idx];
    while (b != NULL) {
        if (b->key == key) {
            return b;
        }
        b = b->next;
    }
    return NULL;
}

// 해시 테이블에 원소를 추가하는 함수
void add(Hashtable *ht, int key) {
    int idx = hash(key);
    Bucket *b = ht->table[idx];
    if (b == NULL) {
        ht->table[idx] = new_bucket(key);
        return;
    }
    while (b->next != NULL) {
        b = b->next;
    }
    b->next = new_bucket(key);
}

// 해시 테이블에서 원소를 제거하는 함수
void remove_key(Hashtable *ht, int key) {
    int idx = hash(key);
    Bucket *b = ht->table[idx];
    if (b == NULL) {
        return;
    }
    if (b->key == key) {
        ht->table[idx] = b->next;
        free(b);
        return;
    }
    while (b->next != NULL) {
        if (b->next->key == key) {
            Bucket *temp = b->next;
            b->next = temp->next;
            free(temp);
            return;
        }
        b = b->next;
    }
}

// 해시 테이블에 키가 key인 원소가 있는지 검사하는 함수
bool contains(Hashtable *ht, int key) {
    Bucket *b = find(ht, key);
    if (b != NULL) {
        return true;
    }
    return false;
}

// 해시 테이블의 모든 원소를 출력하는 함수
void print_set(Hashtable *ht) {
    printf("{ ");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Bucket *b = ht->table[i];
        while (b != NULL) {
            printf("%d, ", b->key);
            b = b->next;
        }
    }
    printf("}");
}


//int *generate_set(Hashtable *ht) {
//    int *result = malloc(sizeof(int) * TABLE_SIZE);
//    int idx = 0;
//    for(int i=5;i<TABLE_SIZE;i++){
//        result[idx]=
//    }
////    for (int i = 5; i < TABLE_SIZE; i++) {
////        printf("%d\n",i);
////        Bucket *b = ht->table[i];
////        printf("%d, ", b->key);
////        while (b != NULL) {
//////            result[idx++]=b->key;
////            result[idx]=b->key;
////            idx++;
////            printf("%d, ", b->key);
////            b = b->next;
////        }
////    }
//    return result;
//}