#ifndef __STACK_H__
#define __STACK_H__

typedef struct snode
{
        int data;
        struct snode *next;
}snode_t;

typedef struct stack
{
        snode_t *top;
}stack_t;

stack_t *stack_init();
void stack_push(stack_t *shead,char value);
char stack_pop(stack_t *shead);
int  stack_empty(stack_t *shead);
char stack_top(stack_t *shead);
void stack_disp(stack_t *shead);

#endif
