#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
//主线程不等待直接退出，栈空间没了，子线程没了空间无法运行
void  *f1(void *arg)
{
    int i=0;
    while(1)
    {
        printf("%s,%d,%u,i=%d\n", __FUNCTION__, __LINE__, getpid(),i++);
        printf("tid=%lu\n",pthread_self());
        if(i==10)
            //pthread_exit(0);
            return;
        sleep(1);
    }
}

void  *f2(void *arg)
{
    int i=0;
    while(1)
    {
        printf("%s,%d,%u,i=%d\n", __FUNCTION__, __LINE__, getpid(),i++);
        printf("tid=%lu\n",pthread_self());
        sleep(1);
    }
}

int main()
{

    pthread_t thid1, thid2;

    pthread_create(&thid1, NULL, f1, NULL);
    pthread_create(&thid2, NULL, f2, NULL);

    pthread_join(thid1, NULL);
    pthread_join(thid2, NULL);

    return 0;
}
