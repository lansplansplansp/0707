#include "spider.h"
#include "confparser.h"
#include "url.h"
#include "mysocket.h"
#include <errno.h>
#include "threads.h"


Config *g_conf;
extern Surl *surlqueue;
extern Ourl *ourlqueue;
int g_epfd;
extern int errno;
extern int g_cur_thread_num;
static int set_ticker(int second)
{
    struct itimerval itimer;
    itimer.it_interval.tv_sec = (long)second;
    itimer.it_interval.tv_usec = 0;
    itimer.it_value.tv_sec = (long)second;
    itimer.it_value.tv_usec = 0;
    return setitimer(ITIMER_REAL, &itimer, NULL);
}
static void mystat()
{
    SPIDER_LOG(SPIDER_LEVEL_INFO,"cur_thread_num=%d\tsurl_num=%d\tourl_num=%d",g_cur_thread_num,get_surl_queue_size(surlqueue),get_ourl_queue_size(ourlqueue));
    if(g_cur_thread_num <= 0 && get_ourl_queue_size(ourlqueue)!=0)
        next_thread();
}
int attach_epoll_task(int g_epfd)
{
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "#################################%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);
    struct epoll_event ev;
    int sock_rv;
    int sockfd;
	ourlnode_t *ourl = (ourlnode_t *)ourl_dequeue(ourlqueue);
    if (ourl == NULL) {
        SPIDER_LOG(SPIDER_LEVEL_WARN, "Pop ourlqueue fail!");
        return -1;
    }
    SPIDER_LOG(SPIDER_LEVEL_WARN, "build connect (%s,%d)!", ourl->ipaddr, ourl->port);
    if ((sockfd = build_connect(ourl->ipaddr, ourl->port)) < 0) {
        SPIDER_LOG(SPIDER_LEVEL_WARN, "Build socket connect fail: %s", ourl->ipaddr);
        return -1;
    }
    set_nonblocking(sockfd);
    if ((sock_rv = send_request(sockfd, ourl)) < 0) {
        SPIDER_LOG(SPIDER_LEVEL_WARN, "Send socket request fail: %s", ourl->ipaddr);
        return -1;
    } 
    event_arg * arg = (event_arg *)calloc(1, sizeof(event_arg));
    arg->fd = sockfd;
    arg->url = ourl;
    ev.data.ptr = arg;
    ev.events = EPOLLIN | EPOLLET;
    if (epoll_ctl(g_epfd, EPOLL_CTL_ADD, sockfd, &ev) == 0) {
        SPIDER_LOG(SPIDER_LEVEL_DEBUG, "Attach an epoll event success!");
    } else {
        SPIDER_LOG(SPIDER_LEVEL_WARN, "Attach an epoll event fail!");
        return -1;
    }
    g_cur_thread_num++; 
    return 0;
}
static int set_nofile(rlim_t limit)
{
    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        SPIDER_LOG(SPIDER_LEVEL_WARN, "getrlimit fail");
        return -1;
    }
    if (limit > rl.rlim_max) {
        SPIDER_LOG(SPIDER_LEVEL_WARN, "limit should NOT be greater than %lu", rl.rlim_max);
        return -1;
    }
    rl.rlim_cur = limit;
    if (setrlimit(RLIMIT_NOFILE, &rl) < 0) {
        SPIDER_LOG(SPIDER_LEVEL_WARN, "setrlimit fail");
        return -1;
    }
    return 0;
}
void show_errfd(int signo)
{
    SPIDER_LOG(SPIDER_LEVEL_ERROR, "back socket fd, %d,%s\n", errno, strerror(errno));
}
int main()
{
    g_conf = init_config();
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "init config %s:%d\n", __FILE__, __LINE__);
    load_config(g_conf);
    surlqueue = surl_queue_init();
    ourlqueue = ourl_queue_init();
    SPIDER_LOG(SPIDER_LEVEL_DEBUG,  "Seeds Count = %d\n",  g_conf->seedcnt);
    int c = g_conf->seedcnt;
    while(c--)
    {
        surl_enqueue(surlqueue, g_conf->seeds[c], TYPE_HTML, 0);
    }
    SPIDER_LOG(SPIDER_LEVEL_DEBUG,  "Surl Count = %d\n",get_surl_queue_size(surlqueue));
    int cfd;
    event_arg narg;
    while(!surl_queue_empty(surlqueue))
    {
        urlparser(NULL);
        ourlnode_t *tmp;
        tmp = ourl_dequeue(ourlqueue);
        SPIDER_LOG(SPIDER_LEVEL_DEBUG , "get URL : %s,%d,%s,%s\n",tmp->domain, tmp->port, tmp->path, tmp->ipaddr);
        cfd = build_connect(tmp->ipaddr, tmp->port);
        if(cfd==-1){
            tmp = ourlnode_free(tmp);
            continue;
        }
        send_request(cfd, tmp);
        narg.fd = cfd;
        narg.url = tmp;
        recv_response((void *)&narg);
    }
    int err = -1;
    if ((err = create_thread(urlparser, NULL, NULL, NULL)) < 0) {
        SPIDER_LOG(SPIDER_LEVEL_ERROR, "Create urlparser thread fail: %s", strerror(err));
    }
    int try_num = 1;
    while(try_num < 8 && ourl_queue_empty(ourlqueue))
        usleep((10000 << try_num++));
    if (try_num >= 8) {
        SPIDER_LOG(SPIDER_LEVEL_ERROR, "NO ourl! DNS parse error?");
    }
    if (g_conf->stat_interval > 0) {
        signal(SIGALRM, mystat);
        signal(SIGSEGV, show_errfd);
        set_ticker(g_conf->stat_interval);
    }
    int ourl_num = 0;
    struct epoll_event events[10];
    g_epfd = epoll_create(g_conf->max_job_num);
    while(ourl_num++ < g_conf->max_job_num) {
        if (attach_epoll_task(g_epfd) < 0)
            break;
    }
    int n, i;
    while(1) 
    {
        n = epoll_wait(g_epfd, events, 10, 2000);
        fflush(stdout);
        if (n <= 0) {
            SPIDER_LOG(SPIDER_LEVEL_DEBUG, "##########epoll wait up %d, cur threads %d\n", n, g_cur_thread_num);
            if (g_cur_thread_num <= 0 && ourl_queue_empty(ourlqueue) && surl_queue_empty(surlqueue)) {
                sleep(1);
                if (g_cur_thread_num <= 0 && ourl_queue_empty(ourlqueue) && surl_queue_empty(surlqueue))
                    break;
            }
        }
        for (i = 0; i < n; i++) {
            event_arg * arg = (event_arg *)(events[i].data.ptr);
            if ((events[i].events & EPOLLERR) ||(events[i].events & EPOLLHUP) ||(!(events[i].events & EPOLLIN))) {
                SPIDER_LOG(SPIDER_LEVEL_WARN, "epoll fail, close socket %d",arg->fd);
                close(arg->fd);
                continue;
            }
            epoll_ctl(g_epfd, EPOLL_CTL_DEL, arg->fd, &events[i]);
            printf("hello epoll:event=%d\n",events[i].events);
            fflush(stdout);
            create_thread(recv_response, arg, NULL, NULL);
            SPIDER_LOG(SPIDER_LEVEL_DEBUG, "##########thread recv response\n");
        }
    }
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "Task done!");
    close(g_epfd);
    return 0;
}
