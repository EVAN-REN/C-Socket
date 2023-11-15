#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Test{
    int num;
    int age;
};
// struct Test t;用全局变量传递数据也可

//回调函数  
void* callback(void* arg){
    for(int i = 0; i < 5; i++){
        printf("子线程: i = %d\n", i);
    }
    printf("子线程: %ld\n", pthread_self());

    struct Test* t = (struct Test*)arg;
    t->num = 100;
    t->age = 16;
    //exit and pass the data outside
    pthread_exit(&t);

    return NULL;
}

int main(){
    //thread id,传出参数，无符号长整形数
    pthread_t tid;

    //create thread(point of pthread_t, attribute:default is NULL, point of start_routine(return void*), point of start_routine's parameter)
    // pthread_create(&tid, NULL, callback, NULL);

    struct Test t; 
    //将t初始化在主线程，并传入子线程，这样在子线程结束返还时，子线程记录的数据不会因为栈的销毁而丢失
    pthread_create(&tid, NULL, callback, &t);

    for(int i = 0; i < 5; i++){
        printf("主线程: i = %d\n", i);
    }
    printf("主线程: %ld\n", pthread_self);
    // sleep(3);

    //此时主线程结束，不会释放地址空间，子线程还会继续执行，退出时可以向外传递数据
    //pthread_exit(NULL);
  
    //主线程等待回收子线程占用资源,并可以通过子线程退出(pthread_exit)来获取数据,参数(pthread_t, void**)
    // pthread_join(tid, NULL);
    // printf("num: %d, age = %d\n", t.num, t.age);

    void* ptr;
    pthread_join(tid, &ptr);
    struct Test* pt = (struct Test*)ptr;
    printf("num: %d, age = %d\n", pt->num, pt->age);

    //杀死子线程，执行后子线程在下次系统调用打断后就直接结束了
    pthread_cancel(tid);

    //pthread_join会使主线程等待子线程，通过detach分离主线程和子线程，这样主线程可继续执行
    pthread_detach(tid);
    pthread_exit(NULL);

    return 0;
}