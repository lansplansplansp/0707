#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;/*初始化互斥锁*/
//法2：pthread_mutex_init(mutex,NULL);//如果参数attr(第二个参数)为空，则使用默认的互斥锁属性，默认属性为快速互斥锁 
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;//初始化条件变量
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
int x=50;
void *routine1(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        x+=random()%10;
        if(x>=50)
            pthread_cond_signal(&cond1);
        else
            pthread_cond_signal(&cond2);
        sleep(1);
        pthread_mutex_unlock(&mutex);
        usleep(100);
    }
    return NULL;
}
void *routine2(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        x-=random()%10;
        if(x>=50)
            pthread_cond_signal(&cond1);
        else
            pthread_cond_signal(&cond2);
        sleep(1);
        pthread_mutex_unlock(&mutex);
        usleep(100);//把进程挂起一段时间， 单位是微秒（百万分之一秒）；
    }
    return NULL;
}
void *routine3(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(x<50)
        {
            pthread_cond_wait(&cond1,&mutex);
        }
        printf("x>50 have :%d\n",x);
        sleep(1);
        pthread_mutex_unlock(&mutex);
        usleep(100);
    }
    return NULL;
}
void *routine4(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(x>=50)
        {
            pthread_cond_wait(&cond2,&mutex);
        }
        printf("x<50 have :%d\n",x);
        sleep(1);
        pthread_mutex_unlock(&mutex);
        usleep(100);
    }
    return NULL;
}
int main()
{
    srand(time(0));
    pthread_t tid1, tid2, tid3, tid4;

    pthread_create(&tid1,NULL,routine1,NULL);
    pthread_create(&tid2,NULL,routine2,NULL);
    pthread_create(&tid3,NULL,routine3,NULL);
    pthread_create(&tid4,NULL,routine4,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    pthread_join(tid4,NULL);

    pthread_mutex_destroy(&mutex);

    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);
    return 0;
}
