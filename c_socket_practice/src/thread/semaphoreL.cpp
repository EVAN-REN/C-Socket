#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

// 条件变量用于线程之间的协调和通信,通常在等待某个条件变为真时进行等待;信号量用于控制对共享资源的访问,通常用于资源计数和线程同步
// semaphore : sem_t sem;
// 记录生产者和消费者的可用资源
// initialize : int sem_init(sem_t *sem, i nt pshared, unsigned int value);
// pshared: 0线程同步;非0进程同步 / value: 当前信号量的资源数
// destroy : int sem_destroy(sem_t *sem);
// wait : int sem_wait(sem_t *sem);
// trywait : int sem_trywait(sem_t *sem);
// release : int sem_post(sem_t *sem);
// get semaphore value : int sem_getvalue(sem_t *sem, int *sval);

sem_t semp;
sem_t semc;

pthread_mutex_t mutex;

struct Node{
    int number;
    struct Node* next;
};

struct Node* head = NULL;

void* producer(void* arg){
    while(1){
        sem_wait(&semp);
        pthread_mutex_lock(&mutex);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

        newNode->number = rand() % 1000;
        newNode->next = head;
        head = newNode;
        printf("producer, ID: %ld, number: %d\n", pthread_self(), newNode->number);
        pthread_mutex_unlock(&mutex);
        sem_post(&semc);
        sleep(rand() % 3);
    }
    return NULL;
}

void* consumer(void* arg){
    while(1){
        sem_wait(&semc);
        pthread_mutex_lock(&mutex);
        struct Node* node = head;
        printf("consumer, ID: %ld, number: %d\n", pthread_self(), node->number);
        head = head->next;
        free(node);
        pthread_mutex_unlock(&mutex);
        sem_post(&semp);
        sleep(rand() % 3);
    }
    return NULL;
}


int main(){
    sem_init(&semp, 0, 5);
    sem_init(&semc, 0, 0);

    pthread_mutex_init(&mutex, NULL);

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

    sem_destroy(&semp);
    sem_destroy(&semc);

    pthread_mutex_destroy(&mutex);

    return 0;
}


