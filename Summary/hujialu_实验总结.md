
#三个实验总结

```
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h> 
#include <signal.h>
#include <ctype.h> 
/* 允许建立的子进程个数最大值 */
#define MAX_CHILD_NUMBER 10 
/* 子进程睡眠时间 */
#define SLEEP_INTERVAL 2 
int proc_number=0; 
/* 子进程的自编号，从0开始 */
void do_something(); 

int main(int argc, char* argv[])
{   
    /* 子进程个数 */
    int child_proc_number = MAX_CHILD_NUMBER; 
    int i, ch; 
    pid_t  child_pid; 
    pid_t pid[10]={0}; /* 存放每个子进程的id */ 
    if (argc > 1) /* 命令行参数第一个参数表示子进程个数*/ 
    {
                child_proc_number = atoi(argv[1]); 
                child_proc_number= (child_proc_number > 10) ? 10 :child_proc_number;
            
    }
    pid_t a;
    for (i=0; i<child_proc_number; i++) 
    { 
        a = fork();
        switch(a)
        {
            case 0:
            {
                proc_number = i;
                do_something();
                break;
            }
            case -1:
            {
                printf("errno\n");
                break;
            }
            default:
            {
                pid[i] = a;
                break;
            }
        }
            /* 填写代码，建立child_proc_number个子进程要执行
             *         * proc_number = i; 
             *                 * do_something(); 
             *                         * 父进程把子进程的id保存到pid[i] */ 
    }
    /* 让用户选择杀死进程，数字表示杀死该进程，q退出 */
    while ((ch = getchar()) != 'q')  
    { 
            if (isdigit(ch)) 
            { 
                kill(pid[ch-'0'],SIGTERM);
                        /*  填写代码，向pid[ch-'0']发信号SIGTERM， 
                         *              * 杀死该子进程 */ 
                pid[ch-'0']=0;
                    }
        }

    /*for(int i=0;i<proc_number;i++)
    {
            kill(pid[i],SIGTERM);
    }*/
    kill(0,SIGTERM);//0所属进程里面的所有进程
    //exit(0);
    /* 在这里填写代码，杀死本组的所有进程 */ 
    return 0;
} 
void do_something() 
{ 
    for(;;) 
    {  
            printf("This is process No.%d and its pid is %d\n",proc_number,  getpid());
            sleep(SLEEP_INTERVAL); // 主动阻塞两秒钟
        }
}

```

##坑点
在这个题目中，该题目的用意是创建十个进程，通过kill和进程号来随机输入杀死进程，
输入q的时候杀死所有进程，这里比较坑的就是杀死之后就忘记把杀死的进程所在的数组单位归0，
或者标记。然后杀死所有进程的时候直接用kill会导致后面的僵尸进程，然后还要考虑到忽视子进程的反回，
所以直接调用了kill（0，SIGTERM）杀死所有进程，不采用循环来杀所有进程。


```
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include <ctype.h>
#include <pthread.h>
#include<stdlib.h>
#define MAX_THREAD 3 /* 线程的个数 */
unsigned long long main_counter, counter[MAX_THREAD];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/* unsigned long  long是比long还长的整数 */
void* thread_worker(void*); 
int main(int argc,char* argv[])
{     
    int i, rtn, ch;
    pthread_t thid;
    pthread_t pthread_id[MAX_THREAD] = {0}; /* 存放线程id*/ 
    for (i=0; i<MAX_THREAD; i++)
    { 
        if(pthread_create(&thid,NULL,thread_worker,(void *)i) !=0)
        {
            printf("creat failed!\n");
            exit(1);
        }
        pthread_id[i] = thid;
            /* 在这里填写代码，用pthread_create建一个普通的线程，
             *         线程id存入pthread_id[i]，线程执行函数是thread_worker
             *                 并i作为参数传递给线程 */
        }    
    do {
        pthread_mutex_lock(&mutex);
                /* 用户按一次回车执行下面的循环体一次。按q退出 */          
        unsigned long long sum = 0;    
                                /* 求所有线程的counter的和 */
        for (i=0; i<MAX_THREAD; i++) 
        {
            /* 求所有counter的和 */         
            sum += counter[i];             
            printf("%llu ", counter[i]);        
        }
        printf("%llu/%llu", main_counter, sum);   
        pthread_mutex_unlock(&mutex);
    } while ((ch = getchar()) != 'q'); 
    return 0;
} 
void* thread_worker(void* p)
{ 
    int thread_num;
    thread_num = (int)p;
    /* 在这里填写代码，把main中的i的值传递给thread_num */ 
    for(;;) 
    { /* 无限循环 */
        pthread_mutex_lock(&mutex);
         counter[thread_num]++; /* 本线程的counter加一 */ 
         main_counter++;/* 主counter 加一 */
        pthread_mutex_unlock(&mutex);
    } 
}

```
##坑点

首先是传入i 值的问题，因为当i 值传入子线程的时候，还没有取到它的值，i已经自加了，此时i的地址会往后移动，i值也就不能够准确传入
所以解决i值顺利传入的问题就是要么开辟一个动态数组来存放i值，或者就一个数组来存放，或者直接将它强转为（void *），相当于把i里面
的值当作地址传入，在子线程的函数中再强转为int类型。
该题坑点很多，首先是main_counter在加的时候，三个线程可能都在同时操作这个全局变量，当它们各自分别取地址的时候，可能都一点点时差问题就会造成它们同时取到的都是0，或者是相同的数字，
最后自加的时候只加了一次，显然数值会比预想的小。

首先是传入i 值的问题，因为当i 值传入子线程的时候，还没有取到它的值，i已经自加了，此时i的地址会往后移动，i值也就不能够准确传入
所以解决i值顺利传入的问题就是要么开辟一个动态数组来存放i值，或者就一个数组来存放，或者直接将它强转为（void *），相当于把i里面
的值当作地址传入，在子线程的函数中再强转为int类型。该题坑点很多，首先是main_counter在加的时候，三个线程可能都在同时操作这个全局变量，当它们各自分别取地址的时候，可能都一点点时差问题就会造成它们同时取到的都是0，或者是相同的数字，最后自加的时候只加了一次，显然数值会比预想的小。之后是sum，因为线程都是并发的，所以在sum 每一次得到的都是一个时刻的值，而在sum 进入printf打印的时候，此时可能sum还在累加，但是打印出来的sum是之前的，所以sum的值会比main_counter的小。
所以在这两个变量操作的地方需要加上锁。



```
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>

#define LOOP_TIMES 10000

/*用宏PTHREAD_MUTEX_INITIALIZER来初始化 */
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* thread_worker(void*);
void critical_section(int thread_num, int i);

int main(void)
{
int rtn, i;
pthread_t pthread_id = 0; /* 存放子线程的id */
rtn = pthread_create(&pthread_id,NULL, thread_worker, NULL );
if(rtn != 0)
{
printf("pthread_create ERROR!\n");
return -1;
}
for (i=0; i<LOOP_TIMES; i++)
{
pthread_mutex_lock(&mutex1);
pthread_mutex_lock(&mutex2);
critical_section(1, i);
pthread_mutex_unlock(&mutex2);
pthread_mutex_unlock(&mutex1);
}

pthread_mutex_destroy(&mutex1);
pthread_mutex_destroy(&mutex2);
return 0;
}
void* thread_worker(void* p)
{
int i;
for (i=0; i<LOOP_TIMES; i++)
{
pthread_mutex_lock(&mutex1);
pthread_mutex_lock(&mutex2);
critical_section(2, i);
pthread_mutex_unlock(&mutex2);
pthread_mutex_unlock(&mutex1);
}
}
void critical_section(int thread_num, int i)
{
printf("Thread%d: %d\n", thread_num,i);
}


```
##坑点
这个题目主要写了一个死锁，因为当线程1拿到了锁1的时候，线程2拿到了锁二，此时线程1要用到锁二的时候就要等待锁二的释放，而线程2又要等待锁1的释放，所以就造成了死锁，
此时只需要把两个锁的顺序换一下就能够避免死锁的出现。

