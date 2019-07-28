#ifndef __MYCHAT_H__
#define __MYCHAT_H__

#define BUFFLEN   128//2^7

typedef struct clientinfo
{
    int   newfd;
    char  ipaddr[32];
    unsigned short port;
    char name[20];
    int name_len;
    int online_flag;
    struct clientinfo *next;
}clientinfo_t ;

typedef struct ipmsg_msg {
    char name[BUFFLEN];
    char msg[BUFFLEN];
    char mytime[BUFFLEN];
}ipmsg_pkg_t;

int server_init_port(int port);

clientinfo_t *list_insert_new(clientinfo_t *head,clientinfo_t *newpeople);
void disp_client_info(clientinfo_t *head);
clientinfo_t *list_search(clientinfo_t *head, int serfd);
void send_to_all_clients(clientinfo_t *comeFrom,clientinfo_t *head, char buff[]);
clientinfo_t *list_delete(clientinfo_t *head, int delfd);
ipmsg_pkg_t *create_package(clientinfo_t *search,char *msg);

#endif
