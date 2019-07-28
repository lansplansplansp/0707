	#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
//输入字符，一个字符一个换行，输入0结束
int main()
{
    queue_t *qhead = NULL;
    qhead = queue_init();
    char ch = '1';
    while(ch)
    {
        scanf("%c",&ch);
        if(ch == '0')
            break;
        enqueue(qhead,ch);
		getchar();
    }
    int n = queue_empty(qhead);
    if(n == -1)
        printf("qhead malloc error!\n");
    else if(n == 1)
            printf("queue is empty!\n");
    else
            printf("have queue!\n");
    display(qhead);
    while(!queue_empty(qhead))
    {
        printf("Do you want to delete queue?Y/n\n");
        getchar();
        scanf("%c",&ch);
        if(ch == 'Y' || ch == 'y')
        {
            ch = dequeue(qhead);
            printf("the qnode is: %c\n",ch);
            display(qhead);
        }
        else
            break;
    }
    if(queue_empty(qhead))
        printf("queue is empty!\n");
    return 0;
}

queue_t *queue_init()
{
    queue_t *qhead = (queue_t *)malloc(sizeof(queue_t));
	if(qhead == NULL)
	{
		return NULL;
	}
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

int queue_empty(queue_t *qhead)
{
    if(NULL == qhead)
        return -1;
    else if(qhead->front == NULL && qhead->rear == NULL)
        return 1;
    else
        return 0;
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
    //printf("\n");
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

