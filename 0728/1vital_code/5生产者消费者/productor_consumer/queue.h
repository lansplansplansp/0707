#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct qnode
{
    char data;
    struct qnode *next;
}qnode_t;

typedef struct queue
{
    qnode_t *front;
    qnode_t *rear;
}queue_t;

queue_t *queue_init();
void enqueue(queue_t *qhead, char value);
char dequeue(queue_t *qhead);
int  queue_empty(queue_t *head);
char  queue_front(queue_t  *head);

#endif
