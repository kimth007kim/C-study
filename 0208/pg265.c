#include <stdio.h>


struct exercise{
    const char *description;
    float duration;

};

struct meal{
    const char * ingredients;
    float weight;
};

struct preferences{
    struct meal food;
    struct exercise exercise;
};

struct fish{ //0x0010
    char *name; ///0x0010 snap
//    char name2[3];
    char *species; //0x0011  0x102        0x0102
    // 구조체의 멤버에 포인터를 선언하면 포인터들은 변수들의 주소를 저장할수있어 변수의 값을 유동적으로 변경 가
    int teeth;  //0x0012
    int age; //0x0016
    struct preferences care;
};

void catalog(struct fish f){
    printf("%s는 %s종 이며, 이빨이 %i개고 %d살 입니다\n",
           f.name,f.species,f.teeth,f.age);
}
void label(struct fish f){
    printf("이름: %s\n",f.name);
    printf("종: %s\n",f.species);
    printf("이빨 수: %d\n",f.teeth);
    printf("나이: %d\n",f.age);
    printf("%2.2f 파운드의 %s를 먹이고 %2.2f 시간 동안 %s하게 하세요.",f.care.food.weight,f.care.food.ingredients,f.care.exercise.duration,f.care.exercise.description);
}

int main() {
    struct fish snappy={"snappy","피라냐",69,4,{{"고기",0.2},{"거품 수족관에서 수영",7.5}}};
    catalog(snappy);
    label(snappy);
//    printf("%s는, %s를 잘 먹 습니다.\n",snappy.name,snappy.care.food);
    return 0;
}
