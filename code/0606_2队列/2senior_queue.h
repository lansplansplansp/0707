#ifndef __2QUEUE_H__
#define __2QUEUE_H__

#include <pthread.h>//pthread_mutex_t
#define MAX_SEQUEUE_ELEMENT 5

typedef struct
{
	pthread_mutex_t EnQueueLock; //进队列互斥锁
	pthread_mutex_t DeQueueLock; //出队列互斥锁
	char data[MAX_SEQUEUE_ELEMENT];
	int front,rear; 
}sequeue_compare_t;

sequeue_compare_t *CreateEmptySequeue_COMPARE();
int FullSequeue_COMPARE(sequeue_compare_t *queue);
int EmptySequeue_COMPARE(sequeue_compare_t *queue);
int EnQueue_COMPARE(sequeue_compare_t *queue, char x);
int DeQueue_COMPARE(sequeue_compare_t *queue, char *x);

#endif
