#include <stdio.h>

typedef struct {
    float tank_capacity;
    int tank_psi;
    const char *suit_material;
} equipment;

typedef struct scuba {
    const char *name;
    equipment kit;
} diver;

void badge(diver d) {
    printf("이름: %s 수족관: %2.2f (%i) 잠수복 재질: %s\n",
           d.name, d.kit.tank_capacity, d.kit.tank_psi, d.kit.suit_material);
}

int main() {
    diver randy={"랜디", {5.5,3500,"네오프렌"}};
    badge(randy);
    return 0;
}
