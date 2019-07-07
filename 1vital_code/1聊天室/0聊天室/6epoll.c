#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mychat.h"
#include <time.h>

#define ARRSIZE 1024

int main()
{
    int cnt;
    char buff[1024];
    int sfd = server_init_port(9876);
    int epfd = epoll_create(ARRSIZE);
    struct epoll_event ev;
    ev.data.fd = sfd;
    ev.events = EPOLLIN | EPOLLPRI;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&ev);
    struct epoll_event revs[ARRSIZE];
    int evcnt;
    struct sockaddr_in peer;
    socklen_t size;

    clientinfo_t *head = NULL;
    int filefd = open("Ichat.log", O_WRONLY|O_APPEND|O_CREAT);

    while(1)
    {
        printf("waiting for change......\n");
        evcnt = epoll_wait(epfd,revs,ARRSIZE,-1);
        printf("evcnt=%d\n", evcnt);
        int i;
        for(i=0;i<evcnt;i++)
        {
            if(revs[i].data.fd == sfd)
            {
                size = sizeof(peer);
                int newfd = accept(sfd,(struct sockaddr *)&peer,&size);

                ev.data.fd = newfd;
                ev.events = EPOLLIN | EPOLLPRI;
                epoll_ctl(epfd,EPOLL_CTL_ADD,newfd,&ev);

                clientinfo_t newpeople;

                newpeople.newfd = newfd;
                strcpy(newpeople.ipaddr,inet_ntoa(peer.sin_addr));
                newpeople.port = ntohs(peer.sin_port);

                head = list_insert_new(head,&newpeople);
                disp_client_info(head);
            }
            else//接收数据
            {
                cnt = recv(revs[i].data.fd,buff,1024,0);

                clientinfo_t *online_man;
                online_man = list_search(head,revs[i].data.fd);
                if(online_man->online_flag == 0)
                {
                    if(strncmp(buff,"login",5) == 0)//上线
                    {
                        online_man->name_len = cnt-6;
                        memmove(online_man->name,&buff[6],online_man->name_len);
                        online_man->online_flag = 1;

                        printf("login's newfd:%d,name:%s",revs[i].data.fd,online_man->name);

                        send_to_all_clients(online_man,head, "I am coming!\n");
                        char buffer[ARRSIZE] = "";
                        ipmsg_pkg_t *pck = create_package(online_man,"I am coming!\n");
                        sprintf(buffer,"%s:\n%s:%s",pck->mytime,pck->name,pck->msg);
                        write(filefd,buffer,strlen(buffer));
                    }
                }
                else
                {
                    if(strncmp(buff,"logout",6) == 0)//下线
                    {
                        printf("logout's newfd:%d,ip:%s,port:%d\t",revs[i].data.fd,inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
                        ev.data.fd = revs[i].data.fd;
                        epoll_ctl(epfd, EPOLL_CTL_DEL,revs[i].data.fd, &ev);
                        close(ev.data.fd);
                        head = list_delete(head, revs[i].data.fd);
                        send_to_all_clients(online_man,head, "I have to logout!\n");
                        char buffer[ARRSIZE] = "";
                        ipmsg_pkg_t *pck = create_package(online_man,"I have to logout!\n");
                        sprintf(buffer,"%s:\n%s:%s",pck->mytime,pck->name,pck->msg);
                        write(filefd,buffer,strlen(buffer));
                    }
                    else
                    {
                        printf("chat's newfd:%d,ip:%s,port:%d\t",revs[i].data.fd,inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
                        send_to_all_clients(online_man,head, buff);
                        char buffer[ARRSIZE] = "";
                        ipmsg_pkg_t *pck = create_package(online_man,buff);
                        sprintf(buffer,"%s:%s", pck->name,pck->msg);
                        write(filefd,buffer,strlen(buffer));
                    }
                }
            }
        }
    }
    close(sfd);
    close(filefd);
    return 0;
}

int server_init_port(int port)
{
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    printf("sfd = %d\n",sfd);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    int on = 1;
    setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    int ret = bind(sfd,(struct sockaddr *)&serv,sizeof(serv));
    printf("ret = %d\n",ret);

    listen(sfd,5);

    return sfd;
}

clientinfo_t *list_insert_new(clientinfo_t *head,clientinfo_t *newpeople)
{
    clientinfo_t *newnode = (clientinfo_t *)malloc(sizeof(clientinfo_t));
    if(NULL == newnode)
    {
        printf("malloc error\n");
        return head;
    }
    newnode->newfd = newpeople->newfd;
    memmove(newnode->ipaddr,newpeople->ipaddr,sizeof(newpeople->ipaddr));
    newnode->port = newpeople->port;
    newnode->online_flag = 0;
    newnode->next = NULL;

    newnode->next = head;
    head = newnode;

    return head;
}

void disp_client_info(clientinfo_t *head)
{
    if(NULL == head)
        return;
    clientinfo_t *p = head;
    printf("display list:\n");
    int i=1;
    while(p!=NULL)
    {
        printf("%d:newfd:%d,ip:%s,port:%d\n",i++,p->newfd,p->ipaddr,p->port);
        p = p->next;
    }
}

clientinfo_t *list_search(clientinfo_t *head, int serfd)
{
    clientinfo_t *p = head;
    while(p!=NULL)
    {
        if(p->newfd == serfd)
            break;
        p = p->next;
    }

    return p;
}

ipmsg_pkg_t *create_package(clientinfo_t *search,char *msg)
{
    char buf[BUFFLEN];
    time_t now = time(NULL);
    strftime(buf,sizeof(buf),"%Y%m%d %H:%M:%S", localtime(&now));
    ipmsg_pkg_t *pkg = (ipmsg_pkg_t*)malloc(sizeof(ipmsg_pkg_t));
    strncpy(pkg->name,search->name, search->name_len-2);
    strcpy(pkg->msg,msg);
    strcpy(pkg->mytime,buf);
    printf("in pkg\r\npkg->name:%s,pkg->msg:%s,pkg->mytime:%s\n",pkg->name,pkg->msg,pkg->mytime);
    return pkg;
}
/*****   向所有其它在线人员发送信息   ***/
void send_to_all_clients(clientinfo_t *comeFrom,clientinfo_t *head,char buff[])
{
    char buffer[1024] = "";

    printf("all:\n");
    clientinfo_t *p = head;
    ipmsg_pkg_t *pck = create_package(comeFrom,buff);
    sprintf(buffer,"%s:%s", pck->name,pck->msg);
    while(p!=NULL)
    {   //p--在线，且不是消息来源方
        if(p != comeFrom && p->online_flag == 1)
            write(p->newfd,buffer,strlen(buffer));
        p = p->next;
    }
}

clientinfo_t *list_delete(clientinfo_t *head, int delfd)
{
    clientinfo_t *p = head;
    clientinfo_t *pre = head;
    while(p!=NULL)
    {
        if(p->newfd == delfd)
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
