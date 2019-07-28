#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


queue_t *queue_init()
{
    queue_t *qhead = (queue_t *)malloc(sizeof(queue_t));
    qhead->front = NULL;
    qhead->rear = NULL;
    return qhead;
}

void enqueue(queue_t *qhead,char data)
{
    if(NULL == qhead)
        return;
    qnode_t *newnode = (qnode_t *)malloc(sizeof(qnode_t));
    if(NULL == newnode)
    {
        printf("malloc error!\n");
        return;
    }
    newnode->data = data;
    newnode->next = NULL;

    if(qhead->front == NULL && qhead->rear == NULL)
    {
        qhead->front = newnode;
        qhead->rear = newnode;
        return;
    }
    qhead->rear->next = newnode;
    qhead->rear = newnode;
    return;
}

void display(queue_t *qhead)
{
    if(NULL == qhead)
        return;
    if(qhead->front == NULL && qhead->rear == NULL)
        return;
    qnode_t *q = qhead->front;
    while(q != NULL)
    {
        printf("%c\t",q->data);
        q = q->next;
    }
    printf("\n");
}
char dequeue(queue_t *qhead)
{
    if(NULL == qhead)
        return '\0';
    if(qhead->front == NULL || qhead->rear == NULL)
        return '\0';
    qnode_t *q = qhead->front;
    if(qhead -> front == qhead ->rear)
    {
        qhead -> front = NULL;
        qhead -> rear = NULL;
    }
    else
        qhead->front = qhead->front->next;
    char ch = q->data;
    free(q);
    return ch;
}

