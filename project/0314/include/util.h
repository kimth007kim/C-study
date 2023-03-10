#define BUF_SIZE 1000
#define EPOLL_SIZE 4000
#define MAX_NAME_SIZE 30
#define MAX_USERS 2000
#define PROTOCOL_SIZE BUF_SIZE+10

void error_handling(char *message);
int int_to_strlength(int num); // int형 변수의 길이를 측정해 주는 함수 100일경우 3을 리턴
