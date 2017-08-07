#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <wait.h>
#define MAX_THREAD 3


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

unsigned long long main_counter, counter[MAX_THREAD];
void* thread_worker(void*);

int
main(int argc,char* argv[])
{
    int i, rtn, ch;
    pthread_t pthread_id[MAX_THREAD] = {0};

    for (i=0; i<MAX_THREAD; i++) {
        pthread_create(&pthread_id[i], NULL, thread_worker, (void *)i);
    }


    do {
        pthread_mutex_lock(&mutex);
        unsigned long long sum = 0;
        for (i=0; i<MAX_THREAD; i++) {
            sum += counter[i];
            printf("%llu ", counter[i]);
        }
        printf("%llu/%llu", main_counter, sum);
        pthread_mutex_unlock(&mutex);
    }while ((ch = getchar()) != 'q');


    return 0;
}


void*
thread_worker(void* p)
{
    int thread_num;
    thread_num = (int)p;

    for(;;) {
        pthread_mutex_lock(&mutex);
        counter[thread_num]++;
        main_counter++;
        pthread_mutex_unlock(&mutex);
    }
}
