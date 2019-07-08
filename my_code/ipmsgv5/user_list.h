
#ifndef  __USER_LIST_H__
#define  __USER_LIST_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFLEN   128

typedef struct user
{
	char user_name[BUFFLEN];
	char host_name[BUFFLEN];
	char user_ip[BUFFLEN]; 
	struct user *next;
}user_list_t;


user_list_t *user_list_init(void);
user_list_t *find_user_byid(user_list_t *head, int id);
void add_user(user_list_t *head, char *name, char *host, char *ip);
void del_user(user_list_t *head, char *ip);
void user_list_display(user_list_t *head);
int user_list_empty(user_list_t *head);
void user_list_destroy(user_list_t *head);

#endif   //_USER_MANNAGER_H_

