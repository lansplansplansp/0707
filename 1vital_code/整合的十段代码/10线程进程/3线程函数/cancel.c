#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
void *thread_fun(void *arg)
{
        int i=1;
        printf("thread start \n");
        while(1)
        {
                printf("i = %d\n",i++);
                sleep(1);
        }
        return (void *)0;
}
int main()
{
        void *ret=NULL;
        pthread_t tid;
        pthread_create(&tid,NULL,thread_fun,NULL);
        sleep(1);

        pthread_cancel(tid);//取消线程
        int n = pthread_join(tid, &ret);//成功返回0；
        printf("thread 3 exit code %d,n = %d\n", (int)ret,n);

        return 0;
}
