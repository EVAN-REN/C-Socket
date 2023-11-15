#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>

// 读写锁是一把锁，是互斥锁的升级版，既能锁读(读操作可以提高程序的执行效率)，也能锁写
// 在文件里有大量读操作可以使用来提高效率
// read/write lock : pthread_rwlock_t rwlock;
// initialize : int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);
// release : int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
// read lock : int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
// try read lock : int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
// write lock : int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
// try write lock : int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
// unlock : int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

// the information in rwlock:
// status of lock:lock/unlock
// lock which operation:write/read
// which thread lock it

//特点
//使用读写锁的读锁锁定了临界区，线程对临界区的访问是并行的，读锁是共享的
//使用读写锁的写锁锁定了临界区，线程对临界区的访问是串行的，写锁是独占的
//使用读写锁分别对两个临界区加了读锁和写锁，两个线程要同时访问着两个临界区，访问写锁临界区的线程继续运行，访问读锁临界区的线程阻塞，因为写锁比读锁的优先级高

int number = 0;

#define MAX 50

pthread_rwlock_t rwlock;

void* read_num(void* arg){
    for(int i = 0; i < MAX; i++){
        pthread_rwlock_rdlock(&rwlock);
        printf("Thread Read, id = %lu, number = %d\n", pthread_self(), number);
        pthread_rwlock_unlock(&rwlock);
        usleep(rand()%5);
    }
    return NULL;
}

void* write_num(void* arg){
    for(int i = 0; i < MAX; i++){
        pthread_rwlock_wrlock(&rwlock);
        int cur = number;
        cur++;
        number = cur;
        printf("Thread Write, id = %lu, number = %d\n", pthread_self(), number);
        pthread_rwlock_unlock(&rwlock);
        usleep(5);
    }
}

int main(int argc, const char* argv[]){
    pthread_t p1[5], p2[3];
    pthread_rwlock_init(&rwlock, NULL);

    for(int i = 0; i < 5; i++){
        pthread_create(&p1[i], NULL, read_num, NULL);
    }

    for(int i = 0; i < 3; i++){
        pthread_create(&p2[i], NULL, write_num, NULL);
    }

    for(int i = 0; i < 5; i++){
        pthread_join(p1[i], NULL);
    }

    for(int i = 0; i < 3; i++){
        pthread_join(p2[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);
    
    return 0;
}


