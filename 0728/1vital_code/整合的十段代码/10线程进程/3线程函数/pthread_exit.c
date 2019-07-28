#include <stdio.h>
#include <stdlib.h>//exit();
#include <pthread.h>

void thread_1(void)
{
    int i=0;
    for(i=0;i<=6;i++)
    {
        printf("This is a pthread_1.\n");
        if(i==2)
            //用pthread_exit()来调用线程的返回值，用来退出线程，但是退出线程所占用的资源不会随着线程的终止而得到释放
            pthread_exit(0);
        sleep(1);
    }
}

void thread_2(void)
{
    int i;
    for(i=0;i<3;i++)
        printf("This is a pthread_2.\n");
    //用pthread_exit()来调用线程的返回值，用来退出线程，但是退出线程所占用的资源不会随着线程的终止而得到释放
    //pthread_exit(0);
    exit(0);
}

int main(void)
{
    pthread_t id_1,id_2;
    int ret;

    ret=pthread_create(&id_1,NULL,(void  *) thread_1,NULL);
    if(ret!=0)
    {
        printf("Create pthread error!\n");
        return -1;
    }

     ret=pthread_create(&id_2,NULL,(void  *) thread_2,NULL);
    if(ret!=0)
    {
        printf("Create pthread error!\n");
        return -1;
    }

    pthread_join(id_1,NULL);
    pthread_join(id_2,NULL);
    return 0;
}
