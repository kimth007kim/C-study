#define TABLE_SIZE 3500
#include<stdbool.h>

// 해시 테이블의 버킷을 표현하는 구조체
typedef struct bucket {
    int key;
    struct bucket *next;
} Bucket;

// 해시 테이블을 표현하는 구조체
typedef struct hashtable {
    Bucket *table[TABLE_SIZE];
} Hashtable;

int hash(int key);

Bucket *new_bucket(int key);

Bucket *find(Hashtable *ht, int key);

void add(Hashtable *ht, int key);

void remove_key(Hashtable *ht, int key);

// 해시 테이블에 키가 key인 원소가 있는지 검사하는 함수
bool contains(Hashtable *ht, int key);

// 해시 테이블의 모든 원소를 출력하는 함수
void print_set(Hashtable *ht);

int *generate_set(Hashtable *ht);