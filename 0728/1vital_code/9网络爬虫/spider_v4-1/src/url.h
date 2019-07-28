//  src/url.h  src/url.c   
#ifndef __ULR_H__
#define __ULR_H__

#include <event.h>
#include <evdns.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <regex.h>
#include <sys/types.h>
#include "spider.h"


//下载、保存的类型 网页html、图片image、视频flv
#define TYPE_HTML  0
#define TYPE_IMAGE 1

#define MAX_LINK_LEN 128


//数据结点
typedef struct surlnode
{
	
        char *url;  //www.baidu.com
	int type;  // TYPE_HTML/TYPE_IMAGE
	int level;  //深度 种子->网页1->网页2->网页3
	struct surlnode *next;
}surlnode_t;

//队列头尾指针
typedef struct surl
{
	surlnode_t *front;
	surlnode_t *rear;
	int  count;  //计数器，记录队列中url个数
}Surl;


Surl *surl_queue_init();
void surl_enqueue(Surl *queue, char *url, int type, int level);
surlnode_t* surl_dequeue(Surl *queue);

int  surl_queue_empty(Surl *queue);
int get_surl_queue_size(Surl *queue);





//第二个队列数据结点
typedef struct ourlnode
{
	
	char *domain;  
	short port;
	char *path;
	char *ipaddr;
	int type;  // TYPE_HTML/TYPE_IMAGE
	int level;  //深度 种子->网页1->网页2->网页3
	struct ourlnode *next;
}ourlnode_t;

//第二个队列-队列头尾指针
typedef struct ourl
{
	ourlnode_t *front;
	ourlnode_t *rear;
	int  count;  //计数器，记录队列中url个数
}Ourl;


Ourl *ourl_queue_init();
void ourl_enqueue(Ourl *queue, ourlnode_t *newnode);
ourlnode_t* ourl_dequeue(Ourl *queue);

int  ourl_queue_empty(Ourl *queue);
int get_ourl_queue_size(Ourl *queue);

ourlnode_t *ourlnode_free(ourlnode_t *ourl);

void * urlparser(void *arg);
char * url_normalized(char *url);



#endif
