#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

// 条件变量是用来实现多个线程访问多个资源，独自不能处理线程同步，需要配合lock一起使用
// condition variable : pthread_cond_t cond;
// initialize : int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
// destroy : int pthread_cond_destroy(pthread_cond_t *cond);
//这个函数会判断cond是否被释放，若cond处于上锁状态，则将进程进入睡眠，并释放互斥锁，当cond被释放后，会再次上锁然后唤醒进程
//此函数一般在while循环中，防止出现虚假唤醒(操作系统或线程库有时在条件变为真之前被唤醒，所以需要再次睡眠)和满足竞争条件(有时多个消费者卡在cond，当满足时会被唤醒，但只有一个能互斥锁加锁成功，剩余被唤醒的的还需要循环再次判断cond然后继续睡眠)
// wait : int pthread_cond_wait(pthread_cond_t *)restrict cond, pthread_mutex_t *restrict mutex);
// timewait : int pthread_cond_timewait(pthread_cond_t *restrict cond, pthread_mutex *restrict mutex, const struct timespec *restrict abstime);
// wake up some : int pthread_cond_signal(pthread_cond_t *cond);
// wake up all : int pthread_cond_broadcast(pthread_cond_t *cond);

pthread_cond_t cond;
pthread_mutex_t mutex;

struct Node{
    int number;
    struct Node* next;
};

struct Node* head = NULL;

void* producer(void* arg){
    while(1){
        pthread_mutex_lock(&mutex);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->number = rand() % 1000;
        newNode->next = head;
        head = newNode;
        printf("producer, ID: %ld, number: %d\n", pthread_self(), newNode->number);
        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cond);
        sleep(rand() % 3);
    }
    return NULL;
}

void* consumer(void* arg){
    while(1){
        pthread_mutex_lock(&mutex);
        while(head == NULL){
            pthread_cond_wait(&cond, &mutex);
        }
        struct Node* node = head;
        printf("consumer, ID: %ld, number: %d\n", pthread_self(), node->number);
        head = head->next;
        free(node);
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }
    return NULL;
}


int main(){
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t t1[5], t2[5];
    for(int i = 0; i < 5; i++){
        pthread_create(&t1[i], NULL, producer, NULL);
    }
    for(int i = 0; i < 5; i++){
        pthread_create(&t2[i], NULL, consumer, NULL);
    }

    for(int i = 0; i < 5; i++){
        pthread_join(t1[i], NULL);
    }
    for(int i = 0; i < 5; i++){
        pthread_join(t2[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
