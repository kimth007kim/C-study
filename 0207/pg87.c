#include <stdio.h>


void go_south_east(int *lat, int *lon) {
    *lat = *lat - 1;
    *lon = *lon + 1;
    printf("lat 주소, long 주소 [ %p ,%p ]\n",lat,lon);
//    printf("그만! 현재 위치: [%i ,%i]\n",*lat,*lon);
}


int main() {

    int latitude = 32;
    int longitude = -64;
//    printf("lat 주소, long 주소 [ %i ,%i]\n",&latitude,&longitude);
    go_south_east(&latitude, &longitude);

    printf("그만! 현재 위치: [ %i , %i ]\n", latitude, longitude);


    return 0;
}
