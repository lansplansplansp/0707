#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct node
{
        char data;
        struct node *next;
}qnode_t;
typedef struct queue
{
        qnode_t *front;
        qnode_t *rear;
}queue_t;
queue_t *queue_init();
void enqueue(queue_t *qhead, char value);
char dequeue(queue_t *qhead);
int  queue_empty(queue_t *qhead);
char queue_front(queue_t *qhead);
void queue_disp(queue_t *qhead);

#endif
