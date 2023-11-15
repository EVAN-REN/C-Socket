#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <string.h>

// create exclusive lock:pthread_mutex_t mutex
// restrict用来限制只有mutex指针才能访问所指内存
// initialize : int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr)
// destroy : int pthread_mutex_destroy(pthread_mutex_t *mutex)
// lock : int pthread_mutex_lock(pthread_mutex_t *mutex)
// unlock : int pthread_mutex_unlock(pthread_mutex_t *mutex)
// trylock : int pthread_mutex_trylock(pthread_mutex_t *mutex)(和lock都能加锁，lock会堵塞等待，trylock在已经锁上的情况不会堵塞而逝直接返回)
 

#define MAX 50

int number;

pthread_mutex_t mutex;

void* funcA_num(void* arg){
    for(int i = 0; i < MAX; i++){
       pthread_mutex_lock(&mutex);
        int cur = number;
        cur++;
        usleep(10);
        number = cur;
        printf("Thread A, id = %lu, number = %d\n", pthread_self(), number);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* funcB_num(void* arg){
    for(int i = 0; i < MAX; i++){
        pthread_mutex_lock(&mutex);
        int cur = number;
        cur++;
        number = cur;
        printf("Thread B, id = %lu, number = %d\n", pthread_self(), number);
        pthread_mutex_unlock(&mutex);
        usleep(5);
    }
}

int main(int argc, const char* argv[]){
    pthread_t p1, p2;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p1, NULL, funcA_num, NULL);
    pthread_create(&p2, NULL, funcB_num, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}

