#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
    list_t *head = NULL;
    head = list_init();
    int x = 1;
    char ch;
    printf("insert head:\n");
    while(1)
    {
        scanf("%d",&x);
        if(x == 0)
            break;
        insert(head,x);
    }
    printf("cnt = %d\n",count1(head));
    display1(head);
    printf("\n");
    printf("insert last:\n");
    while(1)
    {
        scanf("%d",&x);
        if(x == 0)
            break;
        insert_last(head,x);

    }
    int cnt = 0;
    count2(head,&cnt);
    printf("cnt = %d\n",cnt);
    display1(head);
    printf("\n");
    printf("insert roder:\n");
    while(1)
    {
        scanf("%d",&x);
        if(x == 0)
            break;
        insert_order(head,x);
    }
    display1(head);
    printf("\n");
    printf("knode data = %d\n",knode(head,3));
    printf("middle = %d\n",middle(head));
    reverse1(head);
    display1(head);
    printf("\n");
    reverse2(head);
    display2(head);
    printf("\n");
    while(1)
    {
        printf("Do you want to delete data?Y/n\n");
        scanf("%c",&ch);
        scanf("%c",&ch);
        if(ch=='Y'||ch=='y')
        {
            printf("please input a data:\n");
            scanf("%d",&x);
            list_delete(head,x);
        }
        else
            break;
        if(list_empty(head))
        {
            printf("The list empty!\n");
            break;
        }
        else
        {
            display1(head);
            printf("\n");
        }
    }
    return 0;
}

list_t *list_init()
{
    list_t *head = (list_t *)malloc(sizeof(list_t));
    if(NULL == head)
    {
        perror("list head malloc\n");
        exit(-1);
    }
    head->next = NULL;
    return head;
}

void insert(list_t *head,int value)
{
    list_t *newnode = (list_t *)malloc(sizeof(list_t));
    if(NULL == newnode)
    {
        printf("malloc error!\n");
        return;
    }
    newnode->data = value;
    newnode->next = NULL;

    newnode->next = head->next;
    head->next = newnode;

    return;
}
void display1(list_t *head)
{
    if(NULL == head)
        return;
    list_t *p = head->next;
    while(p != NULL)
    {
        printf("%d\t",p->data);
        p = p->next;
    }
    return;
}
int flag = 0;

void display2(list_t *head)
{
    if(NULL == head)
        return;
    if(flag==0)
        flag = 1;
    else
    {
        printf("%d\t",head->data);
    }
    display2(head->next);
    flag = 0;
    return;
}
void insert_last(list_t *head,int value)
{
    list_t *newnode = (list_t *)malloc(sizeof(list_t));
    if(NULL == newnode)
    {
        printf("malloc error");
        return;
    }
    newnode->next = NULL;
    newnode->data = value;

    if(NULL == head->next)
    {
        head->next = newnode;
        return;
    }

    list_t *p = head->next;
    list_t *pre = head->next;
    while(p != NULL)
    {
        pre = p;
        p = p->next;
    }
    pre->next = newnode;
    return;
}
void insert_order(list_t *head,int value)
{
    list_t *newnode = (list_t *)malloc(sizeof(list_t));
    if(NULL == newnode)
    {
        printf("malloc error");
        return;
    }

    newnode->next = NULL;
    newnode->data = value;

    list_t *p = head->next;
    list_t *pre = head->next;
    while(p != NULL)
    {
        if(p->data > value)
            break;
        pre = p;
        p = p->next;
    }
    if(p == head->next)
    {
        newnode->next = head->next;
        head->next = newnode;
        return;
    }
    if(p!=NULL)
    {
        newnode->next = p;
        pre->next = newnode;
        return;
    }
    pre->next = newnode;
    return;
}
int count1(list_t* head)
{
    if(NULL == head->next)
        return 0;
    list_t *p = head->next;
    int cnt = 0;
    while(p != NULL)
    {
        cnt++;
        p = p->next;
    }
    return cnt;
}
void count2(list_t *head,int *pcnt)
{
    if(NULL == head->next)
    {
        *pcnt = 0;
        return;
    }
    list_t *p = head->next;
    while(p!=NULL)
    {
        (*pcnt)++;
        p = p->next;
    }
    return;
}
int knode(list_t *head,int k)
{
    if(NULL == head->next)
    {
        printf("black list\n");
        return -1;
    }
    list_t *p = head->next;
    list_t *pre = head->next;
    while(k--)
    {
        if(p==NULL)
            break;
        pre = p;
        p = p->next;
    }
    if(k>0)
    {
        printf("knode is too big\n");
        return -1;
    }
    return pre->data;
}
int middle(list_t *head)
{
    if(NULL == head->next)
        return -1;
    list_t *p = head->next;
    list_t *pre = head->next;
    while(1)
    {
        p = p->next;
        if(p == NULL)
            break;
        p = p->next;
        if(p == NULL)
            break;
        pre = pre->next;
    }
    return pre->data;
}
void reverse1(list_t *head)
{
    list_t *p = head->next;
    list_t *q = NULL;
    list_t *head2 = NULL;
    while(p != NULL)
    {
        q = p->next;
        p->next = head2;
        head2 = p;
        p = q;
    }
    head->next = head2;
    return;
}
void reverse2(list_t *head)
{
    if(NULL == head || NULL == head->next)
        return;
    list_t *p = head->next;
    list_t *q = head->next;
    list_t *r = head->next;
    q = p->next;
    p->next = NULL;
    while(q != NULL)
    {
        r = q->next;
        q->next = p;
        p = q;
        q = r;
    }
    head->next = p;
    return;
}

int list_empty(list_t *head)
{
    if(NULL == head->next)
        return 1;
    else
        return 0;
}

void list_delete(list_t *head,int value)
{
    if(NULL == head->next)
        return;
    list_t *p = head->next;
    list_t *pre = head->next;
    while(p!=NULL)
    {
        if(value == p->data)
            break;
        pre = p;
        p = p->next;
    }
    if(p == NULL)
    {
        printf("data not exist!\n");
        return;
    }
    if(p == head->next)
    {
        head ->next= head->next->next;
        free(p);
        return;
    }
    pre->next = p->next;
    free(p);
    return;
}

