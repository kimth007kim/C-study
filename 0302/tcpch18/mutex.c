#include<stdio.h>
#include<pthread.h>

#define THREAD_SIZE 100


void *thread_inc(void *arg);

void *thread_desc(void *arg);

long long num = 0;
pthread_mutex_t mutex;

int main() {
    int i;
    pthread_t pthreads[THREAD_SIZE];

    pthread_mutex_init(&mutex, NULL);

    printf("%lld\n", num);
    for (i = 0; i < THREAD_SIZE; i++) {
        if (i % 2)
            pthread_create(&(pthreads[i]), NULL, thread_inc, NULL);
        else
            pthread_create(&(pthreads[i]), NULL, thread_desc, NULL);
    }
    for (i = 0; i < THREAD_SIZE; i++) {
        pthread_join(pthreads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("%lld\n", num);

    return 0;
}

void *thread_inc(void *arg) {
    int i;
    pthread_mutex_lock(&mutex);
    for (i = 0; i < 50000000; i++) {
        num += 1;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;

}

void *thread_desc(void *arg) {
    int i;
    pthread_mutex_lock(&mutex);
    for (i = 0; i < 50000000; i++)
        num -= 1;
    pthread_mutex_unlock(&mutex);
    return NULL;
}
