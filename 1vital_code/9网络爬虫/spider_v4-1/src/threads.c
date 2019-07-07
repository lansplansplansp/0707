#include "threads.h"
#include "spider.c"
#include "spider.h"
#include "confparser.h"
int g_cur_thread_num = 0;
pthread_mutex_t gctn_lock = PTHREAD_MUTEX_INITIALIZER;
extern int g_epfd;
int create_thread(void *(*start_func)(void *), void * arg, pthread_t *pid, pthread_attr_t * pattr)
{
    pthread_attr_t attr;
    pthread_t pt;
    if (pattr == NULL) {
        pattr = &attr;
        pthread_attr_init(pattr);
        pthread_attr_setstacksize(pattr, 1024*1024);
        pthread_attr_setdetachstate(pattr, PTHREAD_CREATE_DETACHED);
    }
    if (pid == NULL)
        pid = &pt;
    int rv = pthread_create(pid, pattr, start_func, arg);
    pthread_attr_destroy(pattr);
    return rv;
}
void begin_thread()
{
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "Begin Thread %lu", pthread_self());
}
void next_thread()
{
    pthread_mutex_lock(&gctn_lock);	
    int left = g_conf->max_job_num - (g_cur_thread_num);
    if (left == 1) {
        attach_epoll_task(g_epfd);
    } else if (left > 1) {
        attach_epoll_task(g_epfd);
        attach_epoll_task(g_epfd);
    } else {
    }
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "End Thread %lu, cur_thread_num=%d", pthread_self(), g_cur_thread_num);
    pthread_mutex_unlock(&gctn_lock);	
}

