/*************************************************************************
	> File Name: heapsort.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月29日 星期六 09时15分43秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

void swap(int *a,int *b)
{
    int t=*a;
    *a=*b;
    *b=t;
}
void heap(int a[],int n,int m)
{
    int parent,child;
    int t=a[n];
    for(parent=n;(parent*2)<=m;parent=child)
    {
        child=parent*2;
        if(child>m)
            break;
        if(child!=m&&a[child]>a[child+1])
            child++;
        if(t<=a[child])
            break;
        else
            a[parent]=a[child];
    }
    a[parent]=t;
}
int main ()
{
    int n,k;
    int *a,b;
    while(scanf("%d %d",&n,&k)!=EOF)
    {
        int sum=0;
        a=(int *)malloc(sizeof(int)*(k+1));//动态分配内存防止浪费空间
        for(int i=1;i<=n;i++)//从下标1开始,方便计算
        {
            if(i<=k)
                scanf("%d",&a[i]);
            else
            {
                for(int j=k/2;j>=1;j--)//建立最小堆
                    heap(a,j,k);
                scanf("%d",&b);
                for(int j=1;j<=k;j++)
                {
                    if(a[j]>b)
                    {
                        swap(&a[j],&b);
                        heap(a,j,k);
                    }
                }
            }
        }
        for(int i=1;i<=k;i++)
            sum+=a[i];
        printf("%d\n",sum);
        free(a);
    }
    return 0;
}
