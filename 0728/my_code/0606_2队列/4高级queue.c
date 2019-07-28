#include <stdio.h>
#include <stdlib.h>
#include "2senior_queue.h"
//队列头是arr[0]，尾是arr[max-1]
int main()
{
	char ch;
	sequeue_compare_t *compare_sequeue = NULL;
	compare_sequeue = CreateEmptySequeue_COMPARE();
	while(1)
	{
		scanf("%c",&ch);
        if(ch == '0')
            break;
		EnQueue_COMPARE(compare_sequeue,ch);
		getchar();
		int n = EmptySequeue_COMPARE(compare_sequeue);
		if(n == -1)
			printf("qhead malloc error!\n");
		else if(n == 1)
			printf("queue is empty!\n");
		else
			printf("have queue!\n");
		if(FullSequeue_COMPARE(compare_sequeue))
		{
			printf("enter FullSequeue_COMPARE:\n");
			char dataEx;//得到新的头的内容
			DeQueue_COMPARE(compare_sequeue,&dataEx);
			printf("dataEx = %c\n",dataEx);
		}
	}
	
	return 0;
}

sequeue_compare_t *CreateEmptySequeue_COMPARE()
{
	sequeue_compare_t *queue;
	queue = (sequeue_compare_t *)malloc(sizeof(sequeue_compare_t));
	if (NULL == queue) return NULL;
	
	queue->front = queue->rear = 0;
	pthread_mutex_init(&queue->EnQueueLock,NULL);
	pthread_mutex_init(&queue->DeQueueLock,NULL);

	return queue;
}

int FullSequeue_COMPARE(sequeue_compare_t *queue)
{
	if (NULL == queue) return -1;
	return ((queue->rear + 1) % MAX_SEQUEUE_ELEMENT == queue->front ? 1 : 0);
}

int EmptySequeue_COMPARE(sequeue_compare_t *queue)
{
	if (NULL == queue) 
		return -1;

	return (queue->front == queue->rear ? 1 : 0);
}

int EnQueue_COMPARE(sequeue_compare_t *queue, char x)
{
	pthread_mutex_lock(&queue->EnQueueLock);
	if (NULL == queue)
	{
		pthread_mutex_unlock(&queue->EnQueueLock);
		return - 1;
	}

	if (1 == FullSequeue_COMPARE(queue))
	{
		pthread_mutex_unlock(&queue->EnQueueLock);
		return -1; /* full */
	}

	queue->rear = (queue->rear + 1) % MAX_SEQUEUE_ELEMENT;//防止队列满，避免溢出
	queue->data[queue->rear] = x;
	printf("queue->rear = %d,ueue->front = %d,queue->data[queue->rear(%d)] = %c\n",queue->rear,queue->front,queue->rear,queue->data[queue->rear]);
	pthread_mutex_unlock(&queue->EnQueueLock);
	return 0;
}

int DeQueue_COMPARE(sequeue_compare_t *queue, char *x)
{
	pthread_mutex_lock(&queue->DeQueueLock);
	if (NULL == queue)
	{
		pthread_mutex_unlock(&queue->DeQueueLock);
		return -1;
	}

	if (1 == EmptySequeue_COMPARE(queue))
	{
		pthread_mutex_unlock(&queue->DeQueueLock);
		return -1; /* empty */
	}

	queue->front = (queue->front + 1) % MAX_SEQUEUE_ELEMENT;//跟着队尾的方响删除

	if (NULL != x) {
		*x = queue->data[queue->front];
	}
	pthread_mutex_unlock(&queue->DeQueueLock);
	return 0;
}

