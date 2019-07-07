#ifndef __LIST_H__
#define __LIST_H__

typedef struct list
{
    int data;
    struct list *next;
}list_t;

list_t *list_init();
void insert(list_t *head,int value);
void display1(list_t *head);
void display2(list_t *head);
void insert_last(list_t *head,int value);
void insert_order(list_t *head,int value);
int count1(list_t *head);
void count2(list_t *head,int *pcnt);
int knode(list_t *head,int k);
int middle(list_t *head);
void reverse1(list_t *head);
void reverse2(list_t *head);
int list_empty(list_t *head);
void list_delete(list_t *head,int value);

#endif
