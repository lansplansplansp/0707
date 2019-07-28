#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex;
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;

void *product(void *arg)
{
    queue_t *queue = (queue_t *)arg;
    char ch='A';
    while(1)
    {
        sleep(random()%5);
        ch='A';
        ch = ch + random()%26;
        pthread_mutex_lock(&mutex);
        enqueue(queue, ch);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        pthread_yield();//œﬂ≥Ã»√≥ˆCPU
    }
    return NULL;
}
void *comsume(void *arg)
{
    queue_t *queue = (queue_t *)arg;
    char ch;
    while(1)
    {
        sleep(random()%5);
        pthread_mutex_lock(&mutex);
        if(queue_empty(queue))
            pthread_cond_wait(&cond, &mutex);
        ch = dequeue(queue);
        pthread_mutex_unlock(&mutex);
        if(ch=='\0')
            continue;
        else
            printf("comsumer:%c\n", ch);
        pthread_yield();
    }
}
int main()
{
    pthread_t tid1, tid2;
    queue_t *queue = NULL;
    srand(time(0));

    queue = queue_init();

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tid1, NULL, product, (void *)queue);
    pthread_create(&tid2, NULL, comsume, (void *)queue);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
