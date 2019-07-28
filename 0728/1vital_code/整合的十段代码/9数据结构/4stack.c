#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int main()
{
    stack_t *shead = NULL;
    shead = stack_init();
    stack_push(shead,'5');
    stack_push(shead,'4');
    stack_push(shead,'3');
    stack_push(shead,'2');
    stack_push(shead,'1');
    int ret = stack_empty(shead);
    if(ret!=0)
        printf("The stack_list is empty!\n");
    else
        printf("Have list!:\n");
    printf("The stack_list:\n");
    stack_disp(shead);
    char top = stack_top(shead);
    printf("The stack_top_char:\n%c\n",top);
    char ch = stack_pop(shead);
    printf("Delete number:\n%c\n",ch);
    printf("After stack_list:\n");
    stack_disp(shead);

    return 0;
}

stack_t *stack_init()
{
    stack_t *shead = (stack_t *)malloc(sizeof(stack_t));
    if(NULL == shead)
    {
            printf("head malloc error!\n");
            return shead;
    }
    shead -> top = NULL;
    return shead;
}

void stack_push(stack_t *shead, char value)
{
    if(shead == NULL)
        return;
    snode_t *newnode = (snode_t *)malloc(sizeof(snode_t));

    newnode->data = value;
    newnode->next = NULL;

    if(shead->top == NULL)
    {
        shead->top = newnode;
    }
    else
    {
        newnode->next = shead->top;
        shead->top = newnode;
    }
    return;
}

char stack_pop(stack_t *shead)
{
    if(shead == NULL)
            return '\0';
    if(shead -> top == NULL)
            return '\0';
    snode_t *q = shead ->top;
    shead->top = shead->top->next;
    char ch = q->data;
    free(q);
    return ch;
}

int stack_empty(stack_t *shead)
{
    if(shead == NULL)
        return -1;
    else if(shead->top == NULL)
        return 1;
    else
        return 0;
}

char stack_top(stack_t *shead)
{
    if(shead == NULL)
        return '\0';
    else if(shead->top == NULL)
        return '\0';
    else
        return shead->top->data;
}
void stack_disp(stack_t *shead)
{
    if(shead == NULL)
            return;
    if(shead -> top == NULL)
            return;
    snode_t *p = shead->top;
    while(p!=NULL)
    {
        printf("%c\t",p->data);
        p = p->next;
    }
    printf("\n");
}
