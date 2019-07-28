#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main()
{
    stack_t *shead = NULL;
    shead = stack_init();
    char ch = '1';
    while(1)
    {
        scanf("%c",&ch);
        if(ch == '0' || ch == '\n' || ch == ' ')
            break;
        stack_push(shead,ch);
    }
    int n = stack_empty(shead);
    if(n == -1)
        printf("shead empty!\n");
    if(n == 1)
        printf("stack is empty!\n");
    else
        printf("have stack:\n");
    stack_display(shead);
    while(!stack_empty(shead))
    {
        printf("Do you want to delete data?Y/n\n");
        getchar();
        scanf("%c",&ch);
        if(ch == 'Y' || ch == 'y')
        {
            ch = stack_pop(shead);
            printf("pop data: %c\n",ch);
            stack_display(shead);
        }
        else
            break;
    }
    if(stack_empty(shead))
        printf("stack is empty!\n");
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
    shead->top = NULL;
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
int stack_empty(stack_t *shead)
{
    if(NULL == shead)
        return -1;
    if(NULL == shead->top)
        return 1;
    else
        return 0;
}
void stack_display(stack_t *shead)
{
    if(NULL == shead)
        return;
    if(NULL == shead->top)
        return;
    snode_t *q = shead->top;
    while(q!=NULL)
    {
        printf("%c\t",q->data);
        q = q->next;
    }
    printf("\n");
    return;
}

char stack_pop(stack_t *shead)
{
    if(NULL == shead)
        return '\0';
    if(NULL == shead->top)
        return '\0';
    snode_t *q = shead->top;
    shead->top = shead->top->next;
    char ch = q->data;
    free(q);
    return ch;
}

