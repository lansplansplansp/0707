#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
int x = 100;
void *routine1(void *arg)
{
    while(1)
    {
            x++;
            sleep(1);
            //pthread_yield();
    }
    return NULL;
}
int main()
{
    pthread_t tid1 ;
    pthread_create(&tid1,NULL,routine1,NULL);
    while(1)
    {
        printf("%d\n",x);
        sleep(1);
        //pthread_yield();
    }
    return 0;
}
