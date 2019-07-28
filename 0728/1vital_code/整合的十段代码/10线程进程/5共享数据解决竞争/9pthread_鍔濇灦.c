#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define N 1000000

int s1=0;
int s2=0;
int s3=0;
pthread_mutex_t mutex;

void *routine1(void *arg)
{
    int i=0;
    while(i++<N)
    {
        pthread_mutex_lock(&mutex);
        s1++;
        s3++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void *routine2(void *arg)
{
    int j=0;
    while(j++<N)
    {
        pthread_mutex_lock(&mutex);
        s2++;
        s3++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main()
{
    pthread_t tid1, tid2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&tid1, NULL, routine1, NULL);
    pthread_create(&tid2, NULL, routine2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("s1=%d,s2=%d,s3=%d\n", s1,s2,s3);
    pthread_mutex_destroy(&mutex);
    return 0;
}
