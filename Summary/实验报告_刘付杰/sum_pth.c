/*************************************************************************
	>    File Name: pthread.c
	>       Author: fujie
	>         Mail: fujie.me@qq.com
	> Created Time: 2017年08月04日 星期五 18时59分51秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
long m,sum;
int n;
pthread_mutex_t mutex;
void* thread(void* i){
    long ssum = 0;
    printf("ii = %d\n",(int)i);
    for(long j = m/n*(int)i + 1; j <= m/n*((int)i+1) ; j++){
        printf("j = %ld\n",j);
        ssum+=j;
    }
    pthread_mutex_lock(&mutex);
    sum+=ssum;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}
int main(){
    pthread_t threid;
    pthread_mutex_init(&mutex,NULL);
    m = 1000000000;
    scanf("%d",&n);
    for(int i = 0; i < n; i++){
        printf("i = %d\n",i);
        if(pthread_create(&threid , NULL , thread , (void*)i) != 0){
            printf("线程创建失败\n");
        }
    }
    sleep(1);
    printf("sum = %ld\n",sum);
}
