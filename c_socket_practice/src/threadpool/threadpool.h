#ifndef _THREADPOOL_H
#define _THREADPOOL_H

typedef struct ThreadPool ThreadPool;
//create threadpool and initialize
ThreadPool *threadPoolCreate(int min, int max, int queueSize);

//destroy threadpool

//assign a task to threadpool

//get the number of working threads in threadpool

//get the number of living threads in threadpool



#endif //_THREADPOOL_H