#include <sys/socket.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include "spider.h"
#include "url.h"
#include "mysocket.h"
#include "qstring.h"
#include "savehtml.h"
#include "urlparser.h"

extern int errno;
extern int g_cur_thread_num; 

int build_connect(char *ip, int port)
{
    int cfd;
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (!inet_aton(ip, &(server_addr.sin_addr))) {
        return -1;
    }
    if ((cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    if (connect(cfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) < 0) {
        close(cfd);
        return -1;
    }
    return cfd;
}
int send_request(int cfd, ourlnode_t *ourl)
{
    int need, begin, n;
    char request[1024] = {0};
    sprintf(request, "GET /%s HTTP/1.0\r\n"
            "Host: %s\r\n"
            "Accept: */*\r\n"
            "Connection: Keep-Alive\r\n"
            "User-Agent: Mozilla/5.0 (compatible; Qteqpidspider/1.0;)\r\n"
            "Referer: %s\r\n\r\n", ourl->path, ourl->domain, ourl->domain);
    need = strlen(request);
    begin = 0;
    while(need) {
        n = write(cfd, request+begin, need);
        if (n <= 0) {
            if (errno == EAGAIN)
            {
                usleep(1000);
                continue;
            }
            SPIDER_LOG(SPIDER_LEVEL_WARN, "Thread %lu send ERROR: %d", pthread_self(), n);
            close(cfd);
                ourlnode_free(ourl);
            return -1;
        }
        begin += n;
        need -= n;
    }
    return 0;
}
void set_nonblocking(int fd)
{
    int flag;
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        SPIDER_LOG(SPIDER_LEVEL_ERROR, "fcntl getfl fail");
    }
    flag |= O_NONBLOCK;
    if ((flag = fcntl(fd, F_SETFL, flag)) < 0) {
        SPIDER_LOG(SPIDER_LEVEL_ERROR, "fcntl setfl fail");
    }
}
#define HTML_MAXLEN   1024*1024
static Header * parse_header(char *header)
{
    int c = 0;
    char *p = NULL;
    char **sps = NULL;
    char *start = header;
    Header *h = (Header *)calloc(1, sizeof(Header));
    memset(h, 0, sizeof(Header));
    if ((p = strstr(start, "\r\n")) != NULL) {
        *p = '\0';
        sps = strsplit(start, ' ', &c, 2);
        if (c == 3) {
            h->status_code = atoi(sps[1]);
        } else {
            h->status_code = 600; 
        }
        start = p + 2;
    }
    while ((p = strstr(start, "\r\n")) != NULL) {
        *p = '\0';
        sps = strsplit(start, ':', &c, 1);
        if (c == 2) {
            if (strcasecmp(sps[0], "content-type") == 0) {
                h->content_type = strdup(strim(sps[1]));
            }
        }
        start = p + 2;
    }
    return h;
}
void * recv_response(void * arg)
{
    int n;
    int len=0;
    int trunc_head = 0;
    char *body_ptr = NULL;
    event_arg *narg = (event_arg *)arg;
    Response *resp = (Response *)malloc(sizeof(Response));
    resp->header = NULL;
    resp->body = (char*)malloc(HTML_MAXLEN);
    resp->body_len = 0;
    resp->url = narg->url;
    while(1)
    {
        n = read(narg->fd,  resp->body+len, 1024);
        if(n<0)
        {
            if(errno==EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
            {
                usleep(100000);
                continue;
            }
            SPIDER_LOG(SPIDER_LEVEL_WARN, "Read socket failed:%s", strerror(errno));
            goto leave;
        }
        else if(n==0)
        {
            resp->body_len = len;
            if(resp->body_len>0)
            {
                extract_url(resp->body, narg->url);
                SPIDER_LOG(SPIDER_LEVEL_DEBUG, "extract url ok,%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);
                save_html(resp);
                SPIDER_LOG(SPIDER_LEVEL_DEBUG, "save html ok,%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);
            }
            goto leave;
        }
        else
        {
            len += n;
            resp->body[len] = '\0';
            if(trunc_head == 0)
            {
                body_ptr = strstr(resp->body, "\r\n\r\n");
                if(body_ptr == NULL)
                        continue;
                *(body_ptr+2) = '\0';
                resp->header = parse_header(resp->body);
                if (header_postcheck(resp->header)) {
                    goto leave;
                }
                trunc_head = 1;
                SPIDER_LOG(SPIDER_LEVEL_DEBUG, "stauts code:%d,content-type:%s\n", resp->header->status_code,resp->header->content_type);
                int i;
                body_ptr += 4;
                for (i = 0; *body_ptr; i++) {
                    resp->body[i] = *body_ptr;
                    body_ptr++;
                }
                resp->body[i] = '\0';
                len = i;
            }
        }
    }
leave:
    if(resp->header!=NULL)
    {
        if(resp->header->content_type != NULL)
            free(resp->header->content_type);
        free(resp->header);
    }
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "free,%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);
    free(resp->body);
    free(resp);
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "free,%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);
    ourlnode_free(narg->url);
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "free,%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);
    g_cur_thread_num--;
    next_thread();
    return NULL;
}
