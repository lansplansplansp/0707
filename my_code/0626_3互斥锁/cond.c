#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

pthread_mutex_t mutex;
pthread_cond_t cond1,cond2,cond3;

void  *f1(void *arg)
{
    int *px1 = (int *)arg;
    printf("px1 =%p\n", px1);
    while(1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond1, &mutex);
        (*px1)++;
        sleep(random()%5+1);
        printf("%s, x=%d\n", __FUNCTION__, *px1);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond2);
    }
}
void  *f2(void *arg)
{
    int *px2 = (int *)arg;
    printf("px2 =%p\n", px2);
    while(1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond2, &mutex);
        (*px2)++;
        sleep(random()%5+1);
        printf("%s, x=%d\n", __FUNCTION__, *px2);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond3);
    }
}
void  *f3(void *arg)
{
    int *px3 = (int *)arg;
    printf("px3 =%p\n", px3);
    while(1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond3, &mutex);
        (*px3)++;
        sleep(random()%5+1);
        printf("%s, x=%d\n", __FUNCTION__, *px3);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond1);
    }
}

int main()
{
    int x=10;
    srand(time(NULL));
    printf("x addr=%p\n", &x);
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond1, NULL);
    pthread_cond_init(&cond2, NULL);
    pthread_cond_init(&cond3, NULL);
    pthread_t thid1, thid2, thid3;
    pthread_create(&thid1, NULL, f1, (void *)&x); // &x  (int *)
    pthread_create(&thid2, NULL, f2, (void *)&x);
    pthread_create(&thid3, NULL, f3, (void *)&x);

    sleep(1);
    pthread_cond_signal(&cond1);

    pthread_join(thid1, NULL);
    pthread_join(thid2, NULL);
    pthread_join(thid3, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);
    pthread_cond_destroy(&cond3);
    printf("main x = %d\n", x);
    return 0;
}
