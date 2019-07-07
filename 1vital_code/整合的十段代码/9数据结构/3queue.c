n#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "queue.h"

int main()
{
	queue_t *queue = NULL;
	queue = queue_init();
        enqueue(queue,'5');
        enqueue(queue,'4');
        enqueue(queue,'3');
        enqueue(queue,'2');
        enqueue(queue,'1');
        int ret = queue_empty(queue);
        if(ret!=0)
            printf("The queue_list is empty!\n");
        else
            printf("Have list!\n");
        printf("The queue_list:\n");
        queue_disp(queue);
        char head = queue_front(queue);
        printf("queue_front_char:\n%c\n",head);
        char ch = dequeue(queue);
        printf("delete char:\n%c\n",ch);
        printf("after queue_list:\n");
        queue_disp(queue);
        printf("enqueue a char:\n");
        enqueue(queue,'0');
        printf("enqueue_list:\n");
        queue_disp(queue);
	return 0;
}
queue_t *queue_init()
{
        queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	queue->front = NULL;
	queue->rear =NULL;
	return queue;
}
void enqueue(queue_t *qhead,char value)
{
	if(qhead == NULL)
		return;
	qnode_t *newnode = (qnode_t *)malloc(sizeof(queue_t));
	newnode->data = value;
	newnode->next = NULL;
        if(qhead->front == NULL && qhead->rear == NULL)
	{
		qhead->front = newnode;
		qhead ->rear = newnode;
		return;
	}
	else
	{
		qhead -> rear -> next = newnode;
		qhead -> rear = newnode;
		return;
	}
}
char dequeue(queue_t *qhead)
{
	if(qhead == NULL)
		return '\0';
	if(qhead ->front ==NULL && qhead->rear ==NULL)
		return '\0';
	qnode_t *q = qhead -> front;
	if(qhead -> front == qhead ->rear)
	{
		qhead -> front = NULL;
		qhead ->rear = NULL;
	}
	else
	{	
		qhead ->front = qhead -> front -> next;
	}
        char ch = q ->data;
	free(q);
	return ch;
}
int queue_empty(queue_t *qhead)
{
    if(qhead == NULL)
        return -1;
    else if(qhead->front == NULL && qhead->rear == NULL)
        return 1;
    else
        return 0;
}
char queue_front(queue_t *qhead)
{
    if(qhead == NULL)
        return '\0';
    else if(qhead->front == NULL && qhead->rear == NULL)
        return '\0';
    else
        return qhead->front->data;
}
void queue_disp(queue_t *qhead)
{
    if(qhead == NULL)
        return;
    if(qhead->front == NULL && qhead->rear == NULL)
        return;
    qnode_t *q = qhead -> front;
    while(q!=NULL)
    {
        printf("%c\t",q->data);
        q = q->next;
    }
    printf("\n");
}

