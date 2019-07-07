#include "mysocket.h"
#include "spider.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "urlparser.h"
#include "savehtml.h"

void  save_html(Response *r) {
    if (strstr(r->header->content_type, "text/html") == NULL)
        return ;
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "save file,%s,%s,%d,%s\n", r->url->domain,r->url->ipaddr,r->url->port,r->url->path);
    char *fn = url2fn(r->url);
    if(fn == NULL)
        return ;
    int fd = -1;
    char path[128];
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "save file,%s,%d,%s\n", __FUNCTION__, __LINE__,fn);
    sprintf(path, "download/%s", fn);
    if ((fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0) {
        return ;
    }
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "save file:%s,fd=%d\n", path, fd);
    int left = r->body_len;
    int n = -1;
    char *p = r->body;
    while (left) {
        if ((n = write(fd, p, left)) < 0) {
            close(fd);
            unlink(fn);
            free(fn);
            return ;
        }
        else {
            p+=n;
            left -= n;
        }
    }
    close(fd);
    free(fn);
}
