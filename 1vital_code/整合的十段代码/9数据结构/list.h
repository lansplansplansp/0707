#ifndef __LIST_H__
#define __LIST_H__

typedef struct list
{
        int data;
        struct list *next;
}list_t;

list_t *list_insert(list_t *head,int value);
list_t *list_insert_last(list_t *head,int value);
int list_count1(list_t *head);
void list_count2(list_t *head,int *pcnt);
void list_display1(list_t *head);
int list_rknode(list_t *head,int k);
int list_middle(list_t *head);
void list_display2(list_t *head);
list_t *list_reverse1(list_t *head);
list_t *list_reverse2(list_t *head);
list_t *list_insert_order(list_t *head,int value);
list_t *list_delete(list_t *head,int value);

#endif


