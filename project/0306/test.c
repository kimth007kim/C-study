#include "include/hashtable.h"
#include <stdio.h>

int main() {
    Hashtable ht = {{NULL}};

    // 원소 추가
    add(&ht, 1);
    add(&ht, 3);
    add(&ht, 5);

    // 원소 출력
    print_set(&ht); // 출력: { 1 3 5 }

    // 원소 검색
    if (contains(&ht, 3)) {
        printf("Set contains 3.\n"); // 출력: Set contains 3.
    } else {
        printf("Set does not contain 3.\n");
    }
    printf("3은 들어있나요? %d 입니다." , contains(&ht,3));

    // 원소 제거
    remove_key(&ht, 3);

    // 원소 출력
    print_set(&ht); // 출력: { 1 5 }

    // 원소 검색
    if (contains(&ht, 3)) {
        printf("Set contains 3.\n");
    } else {
        printf("Set does not contain 3.\n"); // 출력: Set does not contain 3.
    }

    return 0;
}