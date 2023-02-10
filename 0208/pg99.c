#include <stdio.h>

int main() {
    // 배열 변수는 포인터와 비슷하다.
    // 배열변수는 첫번째 요소의 주소를 나타낸다.
    int contestants[] = {1, 2, 3};
    int t = *contestants;
    printf("contestants의 배열의 길이 = %d\n", sizeof(contestants));
    printf("*contestants의 sizeof() 결과 = %d\n", sizeof(t));



    int *choice = contestants;  // 포인터 변수(포인터 선언)후 배열의 첫번째 주소를 변수에 대입
    contestants[0] = 2; // contestants = [2,2,3]
    contestants[1] = contestants[2]; // contestants = [2,3,3]
    contestants[2] = *choice; // 배열의 2번째 값에 chice 가 참조하고있는 실제값 contestants[0]을 대입한다.
    printf("나는 참가자 %i번을 선택할 꺼야 \n", contestants[2]);


    return 0;
}
