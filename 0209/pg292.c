#include <stdio.h>

typedef union {
    float lemon;
    int lime_pieces;
} lemon_lime;

typedef struct {
    float tequila;
    float cointreau;
    lemon_lime citrus;
} margarita;

int main() {


    margarita m= {2.0,1.0, {2}};
    printf("데킬라 %2.1f잔\n 코엥트로 %2.1f잔\n  주스 %2.1f잔\n",m.tequila,m.cointreau,m.citrus.lemon);

    return 0;
}
