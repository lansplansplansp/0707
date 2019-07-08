#include "user_list.h"

user_list_t *user_list_init(void)
{
    user_list_t *listhead = (user_list_t *)malloc(sizeof(user_list_t));

    if(NULL == listhead){
        perror("list head malloc\n");
        exit(-1);
    }

    listhead->next = NULL;
    return listhead;
}

static int find_user(user_list_t *head, char *ip)
{
    user_list_t *pf = head->next;

    while(pf != NULL)
    {
        if((strcmp(pf->user_ip, ip)) == 0)
            return 1;
        pf=pf->next;
    }
    printf("not find this user,should add\n");
    return 0;
}

user_list_t *find_user_byid(user_list_t *head, int id)
{
    user_list_t *pf = head->next;
    while(id != 0)
    {
        if(pf->next != NULL)
            pf = pf->next;
        else
            return NULL;
        id--;
    }
    return pf;
}

void add_user(user_list_t *head, char *user,char *host,char *ip)
{
    user_list_t *pf;

    if(find_user(head, ip))
        return;

    pf = (user_list_t*)malloc(sizeof(user_list_t));
    if(NULL == pf){
    perror("new user malloc\n");
        exit(-1);
    }

    strcpy(pf->user_name,user);
    strcpy(pf->host_name,host);
    strcpy(pf->user_ip,ip);

    pf->next = head->next;
    head->next = pf;
}

void del_user(user_list_t *head, char *ip)
{
    user_list_t *pf,*pb;
    pb = head->next;
    pf = head;

    while(pb != NULL){
        if(strcmp(pb->user_ip, ip) != 0){
            pf = pb;
            pb = pb->next;
        }
    }
    if(pb == NULL)
        return;
    pf->next = pb->next;
    free(pb);
}

void user_list_display(user_list_t *head)
{
    user_list_t *pf = head->next;
    int id=0;
    while(pf!=NULL)
    {
        printf("%2d %20s %20s %20s\n", id++, pf->user_name, pf->host_name, pf->user_ip);
        pf=pf->next;
    }
}

int user_list_empty(user_list_t *head)
{
    if(NULL == head || NULL == head->next)
        return 1;
    else
        return 0;
}

void user_list_destroy(user_list_t *head)
{
    free(head);
    return;
}
