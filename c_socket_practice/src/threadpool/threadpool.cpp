#include <iostream>
#include <threadpool.h>
#include <pthread.h>

//define the task construction
typedef struct Task
{
    void (*function) (void* arg);
    void* arg;
}Task;

//define the threadpool construction
struct ThreadPool
{
    //task queue
    Task* taskQ;
    int queueCapacity; //capacity
    int queueSize;      //the number of tasks
    int queueFont;      //pull the data
    int queueRear;      //push the data

    pthread_t managerID;    //manager thread ID
    pthread_t *threadIDs;   //work thread ID
    int minNum;             //min number of thread
    int maxNum;             //max number of thread
    int busyNum;            //number of busy thread
    int liveNum;            //number of live thread
    int exitNum;            //number of destroy thread
    pthread_mutex_t mutexPool;  //lock the whole threadpool
    pthread_mutex_t mutexBusy;  //lock the busyNum variety
    pthread_cond_t notFull;     //if task list is full
    pthread_cond_t notEmpty;    //if task list is empty 

    int shutdown;           //if destroy the threadpool, yes 1, not 0
};

ThreadPool *threadPoolCreate(int min, int max, int queueSize){
    ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));
    if(pool == NULL){
        printf("malloc threadpool fail...\n");
        return NULL;
    }

    pool->threadIDs = (pthread_t*)malloc(sizeof(pthread_t) * max);
    if(pool->threadIDs == NULL){
        printf("malloc threadIDs fail...\n");
        return NULL;
    }
    memset(pool->threadIDs, 0, sizeof(pthread_t) * max);
    pool->minNum = min;
    pool->maxNum = max;
    pool->busyNum = 0;
    pool->liveNum = min;
    pool->exitNum = 0;

    return NULL;
}
