#ifndef __STACK_H__
#define __STACK_H__

typedef struct snode
{
    char data;
    struct snode *next;
}snode_t;

typedef struct stack
{
    snode_t *top;
}stack_t;

stack_t *stack_init();
void stack_push(stack_t *shead,char value);
int stack_empty(stack_t *shead);
void stack_display(stack_t *shead);
char stack_pop(stack_t *shead);

#endif
