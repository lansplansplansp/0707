#include<stdio.h>
#include<stdlib.h>
#include "2list.h"

int main()
{
	list_t *head = NULL;
        int x;
        while(1)
        {
            scanf("%d",&x);
            if(x == 0)
                break;
            head = list_insert(head,x);
        }
        while(1)
        {
            scanf("%d",&x);
            if(x == 0)
                break;
            head = list_insert_last(head,x);
        }
        while(1)
        {
            scanf("%d",&x);
            if(x == 0)
                break;
            head = list_insert_order(head,x);
        }
        printf("cnt = %d\n",list_count1(head));
        int cnt = 0;
	list_count2(head,&cnt);
	printf("cnt = %d\n",cnt);
	list_display1(head);
	int data = list_rknode(head,2);
	printf("k's data = %d\n",data);
	int middle = list_middle(head);
	printf("middle = %d\n",middle);
	list_display2(head);
	printf("reverse1:\n");
	head = list_reverse1(head);
	list_display1(head);
	printf("reverse2:\n");
	head = list_reverse2(head);
	list_display1(head);
	head = list_delete(head,9);
	list_display1(head);
}

list_t *list_insert(list_t *head,int value)
{
	list_t *newnode = (list_t *)malloc(sizeof(list_t));
	if(NULL == newnode)
	{
		printf("malloc error\n");
		return head;
	}
	newnode->data = value;
	newnode->next = NULL;

	newnode->next = head;
	head = newnode;

	return head;
}
list_t *list_insert_last(list_t *head,int value)
{
	list_t *newnode = (list_t *)malloc(sizeof(list_t));
	if(NULL == newnode)
	{
		printf("malloc error\n");
		return head;
	}
	newnode->data = value;
	newnode->next = NULL;
	if(head == NULL)
	{
		head=newnode;
		return head;
	}
	list_t *p = head;
	list_t *pre = head;
	while(p!=NULL)
	{
		pre = p;
		p = p->next;
	}
	pre->next = newnode;
	return head;
}
int list_count1(list_t *head)
{
	list_t *p = head;
	int cnt = 0;
	while(p!=NULL)
	{
		cnt++;
		p = p->next;
	}
	return cnt;
}
void list_count2(list_t *head,int *pcnt)
{
	if(pcnt == NULL)
		return;
	if(head == NULL)
	{
		*pcnt = 0;
		return;
	}
	list_t *p = head;
	while(p!=NULL)
	{
		(*pcnt)++;
		p = p->next;
	}
	return;
}
void list_display1(list_t *head)
{
	if(NULL == head)
		return;
	list_t *p = head;
	while(p!=NULL)
	{
		printf("%d\t",p->data);
		p = p->next;
	}
	printf("\n");
}
int list_rknode(list_t *head,int k)
{
	if(head == NULL || k <= 0)
		return -999;
	list_t *p = head;
	while(p!=NULL&&k>0)
	{
		k--;
		p=p->next;
	}
	if(k>0)
		return -999;
	list_t *pre = head;
	while(p!=NULL)
	{
		pre = pre->next;
		p = p->next;
	}
	return pre->data;
}
int list_middle(list_t *head)
{
	if(head == NULL)
		return -999;
	list_t *pre=head,*p=head;
	while(1)
	{
		if(p!=NULL)
			p = p->next;
		else
			break;
		if(p!=NULL)
			p = p->next;
		else
			break;
		pre = pre->next;
	}
	return pre->data;
}
void list_display2(list_t *head)
{
	if(head==NULL)
		return;
	list_display2(head->next);
	printf("data = %d\n",head->data);
}
list_t *list_reverse1(list_t *head)
{
	list_t *p = head;
	list_t *q = head;
	list_t *head2 = NULL;
	while(p!=NULL)
	{
		q = p->next;
                p->next = head2;
		head2 = p;
		p = q;
	}
	return head2;
}
list_t *list_reverse2(list_t *head)
{
	if(head==NULL || head->next==NULL)
		return head;
	list_t *p = head;
	list_t *q;
	list_t *r;
	q = p->next;
	while(q!=NULL)
	{
		r = q->next;
		q->next = p;
		p = q;
		q = r;
	}
	head -> next = NULL;
	head = p;
	return head;
}
list_t *list_insert_order(list_t *head,int value)
{
	list_t *newnode = (list_t *)malloc(sizeof(list_t));
	newnode->data = value;
	newnode->next = NULL;
	if(head == NULL)
	{
		head = newnode;
		return head;
	}
	list_t *p = head;
	list_t *pre = head;
	while(p!=NULL)
	{
		if(p->data > value)
			break;
		pre = p;
		p = p->next;
	}
	if(p == head)
	{
		newnode->next = head;
		head = newnode;
		return head;
	}
	if(p == NULL)
	{
		pre->next = newnode;
		return head;
	}
	newnode->next = p;
	pre->next = newnode;
	return head;
}
list_t *list_delete(list_t *head,int value)
{
	list_t *p = head;
	list_t *pre = head;
	while(p!=NULL)
	{
		if(p->data == value)
			break;
		pre = p;
		p = p->next;
	}
	if(head == NULL)
		return head;
	if(p == NULL)
		return head;
	if(head == p)
	{
		head = head->next;
		free(p);
		return head;
	}
	pre->next = p->next;
	free(p);
	return head;
}
