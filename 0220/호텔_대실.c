#include <stdio.h>
// #define _CRT_SECURE_NO_WARNINGS 
#include <stdbool.h>
#include <stdlib.h>
#include<string.h>
#define MAX(i, j) (((i) > (j)) ? (i) : (j))




void make(char *** book_time, size_t n, size_t m);
int tok(char * word);
void print(int *pa);

int room [3611]= {0};

void make(char *** book_time, size_t n, size_t m){
    int s,e;
    
    for( int i=0; i<n; i++){
        int j;
        s=tok(book_time[i][0]);
        e=tok(book_time[i][1]);
        e+=9;
        // printf("%d ~ %d\n",s,e);
        
        for (j=s; j<e+1; j++)
            room[j]+=1;
    }
    
}

int tok(char * word){
    int result =0;
    int tmp;
    char * ptr  = strtok(word, ":");
    // printf("%s\n",ptr);
    tmp=atoi(ptr);
    result+= tmp*60;
    ptr  = strtok(NULL, ":");
    // printf("%s\n",ptr);
    result+= atoi(ptr);
    
    return result;
}

void print(int *pa){
    int i;
    for(i =0; i<3611;i++){
        printf("%d ",pa[i]);   
    }
}


// book_time_rows는 2차원 배열 book_time의 행 길이, book_time_cols는 2차원 배열 book_time의 열 길이입니다.
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char*** book_time, size_t book_time_rows, size_t book_time_cols) {
    int answer = 0;
    // printf(*book_time);
    make(book_time, book_time_rows, book_time_cols);
    for (int i=0; i<3612; i++){
        answer=  MAX(answer,room[i]);
    }
    // print(room);

    return answer;
}
