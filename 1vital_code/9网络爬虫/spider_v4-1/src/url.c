#include "url.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "spider.h"
#include "uthash.h"
#include <pthread.h>
#include "threads.h"
Surl  *surlqueue;
Ourl  *ourlqueue;
pthread_mutex_t sq_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  sq_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t oq_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  oq_cond = PTHREAD_COND_INITIALIZER;
Surl *surl_queue_init()
{
	Surl *queue = (Surl*)malloc(sizeof(Surl));
	queue->front = NULL;
	queue->rear = NULL;
	queue->count = 0;
	return queue;
}
void surl_enqueue(Surl *queue, char *url, int type, int level)
{
    if(queue == NULL)
        return;
    surlnode_t *newnode = (surlnode_t *)malloc(sizeof(surlnode_t));
    newnode->url = strdup(url);
    newnode->type = type;
    newnode->level  = level;
    newnode->next = NULL;
    pthread_mutex_lock(&sq_lock);
    if(surl_queue_empty(queue))
    {
        queue->front = newnode;
        queue->rear = newnode;
    }
    else
    {
        queue->rear->next = newnode;
        queue->rear = newnode;
    }
    queue->count++;
    pthread_cond_signal(&sq_cond);
    pthread_mutex_unlock(&sq_lock);
}
surlnode_t* surl_dequeue(Surl *queue)
{
    if(queue==NULL)
        return NULL;
    surlnode_t *q=NULL;
    pthread_mutex_lock(&sq_lock);
    if(surl_queue_empty(queue))
    {
        q=NULL;
        return NULL;
    }
    else
    {
        queue->count--;
        q = queue->front;
        if(queue->front == queue->rear)
        {
            queue->front = NULL;
            queue->rear = NULL;
        }
        else
        {
            queue->front = queue->front->next;
        }
    }
    pthread_mutex_unlock(&sq_lock);
    return q;
}
int  surl_queue_empty(Surl *queue)
{	
    if(queue == NULL)
        return -1;
    else if(queue->front == NULL && queue->rear == NULL)
        return 1;
    else
        return 0;
}
int get_surl_queue_size(Surl *queue)
{
	int size;
	pthread_mutex_lock(&sq_lock);
	if(queue == NULL)
		size = 0;
	else
		size = queue->count;
	pthread_mutex_unlock(&sq_lock);
	return size;
}
Ourl *ourl_queue_init()
{
	Ourl *queue = (Ourl*)malloc(sizeof(Ourl));
	queue->front = NULL;
	queue->rear = NULL;
	queue->count = 0;
	return queue;
}
void ourl_enqueue(Ourl *queue, ourlnode_t *newnode)
{
    if(queue == NULL)
    {
        free(newnode);
        return ;
    }
    pthread_mutex_lock(&oq_lock);
    if(ourl_queue_empty(queue))
    {
        queue->front = newnode;
        queue->rear = newnode;
    }
    else
    {
        queue->rear->next = newnode;
        queue->rear = newnode;
    }
    queue->count++;
    pthread_cond_broadcast(&oq_cond);
    pthread_mutex_unlock(&oq_lock);
}

static void get_timespec(struct timespec * ts, int millisecond)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    ts->tv_sec = now.tv_sec;
    ts->tv_nsec = now.tv_usec * 1000;
    ts->tv_nsec += millisecond * 1000;
}
ourlnode_t* ourl_dequeue(Ourl *queue)
{
    ourlnode_t *q=NULL;
    pthread_mutex_lock(&oq_lock);
    if(ourl_queue_empty(queue))
    {
        q = NULL;
        return NULL;
    }
    else
    {
        queue->count--;
        q = queue->front;
        if(queue->front == queue->rear)
        {
            queue->front = NULL;
            queue->rear = NULL;
        }
        else
        {
            queue->front = queue->front->next;
        }
    }
    pthread_mutex_unlock(&oq_lock);
    return q;
}
int  ourl_queue_empty(Ourl *queue)
{	
    if(queue == NULL)
        return -1;
    else if(queue->front == NULL && queue->rear == NULL)
        return 1;
    else
        return 0;
}
int get_ourl_queue_size(Ourl *queue)
{
    int size;
    pthread_mutex_lock(&oq_lock);
    if(queue == NULL)
            size =  0;
    else
            size =  queue->count;
    pthread_mutex_unlock(&oq_lock);
    return size;
}
ourlnode_t *ourlnode_free(ourlnode_t *ourl)
{
    free(ourl->domain);
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "ourl free %d\n", __LINE__);
    free(ourl->ipaddr);
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "ourl free %d\n", __LINE__);
    free(ourl->path);
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "ourl free %d\n", __LINE__);
    free(ourl);
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "ourl free %d\n", __LINE__);
    return NULL;
}
typedef struct my_struct {  
    char domain[128];
    char ip[32]; 
    UT_hash_handle hh;
}hashmap;    
hashmap *domain_ip_map;
void hash_add(char *domain, char *ip)
{
    hashmap *s = (hashmap*)malloc(sizeof(hashmap));
    strcpy(s->domain, domain);
    strcpy(s->ip, ip);
    HASH_ADD_STR( domain_ip_map, domain, s );
}
char * hash_find(char *domain)
{
    hashmap *s=NULL;
    HASH_FIND_STR( domain_ip_map, domain, s);
    if(s)
        return s->ip;
    else
        return NULL;
}
void hash_destroy()
{
    hashmap *s, *tmp;
    HASH_ITER(hh, domain_ip_map, s, tmp)
    {
        HASH_DEL(domain_ip_map, s);
        free(s);
    }
}
static void dns_callback(int result, char type, int count, int ttl, void *addresses, void *arg) 
{
    ourlnode_t * ourl = (ourlnode_t *)arg;
    struct in_addr *addrs = (struct in_addr *)addresses;
    if (result != DNS_ERR_NONE || count == 0) {
        SPIDER_LOG(SPIDER_LEVEL_WARN, "Dns resolve fail: %s", ourl->domain);
    } else {
        char * ip = inet_ntoa(addrs[0]);
        SPIDER_LOG(SPIDER_LEVEL_DEBUG, "Dns resolve OK: %s -> %s", ourl->domain, ip);
        ourl->ipaddr= strdup(ip);
        hash_add(ourl->domain, ourl->ipaddr);
        ourl_enqueue(ourlqueue, ourl);
    }
    event_loopexit(NULL);
}
static ourlnode_t * surl2ourl(surlnode_t* surl)
{
	
    surl->url = url_normalized(surl->url);
    ourlnode_t *ourl = (ourlnode_t *)calloc(1, sizeof(ourlnode_t));
    char *p = strchr(surl->url, '/');
    if (p == NULL) {
        ourl->domain = strdup(surl->url);
        ourl->path = strdup(" ");
    } else {
        *p = '\0';
        ourl->domain = strdup(surl->url);
        ourl->path = strdup(p+1);
    }
    p = strrchr(ourl->domain, ':');
    if (p != NULL) {
        *p = '\0';
        ourl->port = atoi(p+1);
        if (ourl->port == 0)
            ourl->port = 80;

    } else {
        ourl->port = 80;
    }
    ourl->level = surl->level;
    return ourl;
}
char * url_normalized(char *url) 
{
    if (url == NULL) 
        return NULL;
    int len = strlen(url);
    while (len && isspace(url[len-1]))
        len--;
    url[len] = '\0';
    if (len == 0) {
        free(url);
        return NULL;
    }
    if (len > 7 && strncmp(url, "http", 4) == 0) {
        int vlen = 7;
        if (url[4] == 's')
            vlen++;
        len -= vlen;
        char *tmp = (char *)malloc(len+1);
        strncpy(tmp, url+vlen, len);
        tmp[len] = '\0';
        free(url);
        url = tmp;
    }
    if (url[len-1] == '/') {
        url[--len] = '\0';
    }
    if (len > MAX_LINK_LEN) {
        free(url);
        return NULL;
    }
    return url;
}
void * urlparser(void *arg)
{
    surlnode_t*surl = NULL;
    ourlnode_t*ourl = NULL;
    while(1)
    {
        pthread_mutex_lock(&sq_lock);
        while(surl_queue_empty(surlqueue))
        {
            pthread_cond_wait(&sq_cond, &sq_lock);
        }
        pthread_mutex_unlock(&sq_lock);
        surl = surl_dequeue(surlqueue);
        if(surl==NULL)
            continue;
        ourl = surl2ourl(surl);
        free(surl);
        char *ip = hash_find(ourl->domain);
        if(NULL == ip)
        {
            struct event_base * base = event_init();
            evdns_init();
            evdns_resolve_ipv4(ourl->domain, 0, dns_callback, ourl);
            event_dispatch();
            event_base_free(base);
        }
        else
        {
            SPIDER_LOG(SPIDER_LEVEL_DEBUG,"use old dns\n");
            ourl->ipaddr= strdup(ip);
            ourl_enqueue(ourlqueue, ourl);
        }
    }
    return NULL;
}
