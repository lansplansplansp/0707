#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

queue_t *queue_init()
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}
void enqueue(queue_t *qhead, char value)
{
    if(qhead == NULL)
        return ;
    qnode_t * newnode = (qnode_t *)malloc(sizeof(qnode_t));
    if(NULL == newnode)
    {
        printf("malloc error!\n");
        return;
    }
    newnode->data = value;
    newnode->next = NULL;

    if(qhead->front == NULL && qhead->rear == NULL)
    {
        qhead->front = newnode;
        qhead->rear  = newnode;
        return;
    }
    else
    {
        qhead->rear->next = newnode;
        qhead->rear = newnode;
        return ;
    }
}
char dequeue(queue_t *qhead)
{
    if(qhead == NULL)
        return '\0';
    if(qhead->front == NULL && qhead->rear == NULL)
        return '\0';
    qnode_t *q = qhead->front;
    if(qhead->front == qhead->rear)
    {
        qhead->front = NULL;
        qhead->rear = NULL;
    }
    else
    {
        qhead->front = qhead->front->next;
    }
    char ch = q->data;
    free(q);
    return ch;
}
int  queue_empty(queue_t *head)
{
    if(head==NULL)
        return -1;
    else if(head->front ==NULL && head->rear==NULL)
        return 1;
    else
        return 0;
}
