#include "urlparser.h"
#include <regex.h>
#include "url.h"
#include "mysocket.h"

static const char *HREF_PATTERN = "href=\"\\s*\\([^ >\"]*\\)\\s*\"";

static char * BIN_SUFFIXES = ".jpg.jpeg.gif.png.ico.bmp.swf";
static int is_bin_url(char *url)
{
    char *p = NULL;
    if ((p = strrchr(url, '.')) != NULL) {
        if (strstr(BIN_SUFFIXES, p) == NULL)
            return 0;
        else
            return 1;
    }
    return 0;
}
char *attach_domain(char *url, const char *domain)
{
    if (url == NULL)
        return NULL;
    if (strncmp(url, "http", 4) == 0) {
        return url;
    } else if (*url == '/') {
        int i;
        int ulen = strlen(url);
        int dlen = strlen(domain);
        char *tmp = (char *)malloc(ulen+dlen+1);
        for (i = 0; i < dlen; i++)
            tmp[i] = domain[i];
        for (i = 0; i < ulen; i++)
            tmp[i+dlen] = url[i];
        tmp[ulen+dlen] = '\0';
        free(url);
        return tmp;
    } else {
        free(url);
        return NULL;
    }
}

char * url2fn(const ourlnode_t* url)
{
    int i = 0;
    int l1 = strlen(url->domain);
    int l2 = strlen(url->path);
    char *fn = (char *)malloc(l1+l2+20);
    for (i = 0; i < l1; i++)
    fn[i] = url->domain[i];
    fn[i] = '\0';
    if(l2==0)
    {
        strcat(fn+l1, ".html");
        l1+=5;
    }
    else
    {
        fn[l1++] = '_';
        for (i = 0; i < l2; i++)
        fn[l1+i] = (url->path[i] == '/' ? '_' : url->path[i]);
        fn[l1+l2] = '\0';
    }
    return fn;
}
extern Surl  *surlqueue;
int extract_url(char *str, ourlnode_t *ourl)
{
    regex_t re;
    const size_t nmatch = 2;
    regmatch_t matchptr[2];
    int len;
    char *p = str;
    if (regcomp(&re, HREF_PATTERN, 0) != 0) {
        SPIDER_LOG(SPIDER_LEVEL_ERROR, "compile regex error");
        return -1;
    }
    while (regexec(&re, p, nmatch, matchptr, 0) != REG_NOMATCH) {
        len = (matchptr[1].rm_eo - matchptr[1].rm_so);
        p = p + matchptr[1].rm_so;
        char *tmp = (char *)calloc(len+1, 1);
        strncpy(tmp, p, len);
        tmp[len] = '\0';
        p = p + len + (matchptr[0].rm_eo - matchptr[1].rm_eo);
        if (is_bin_url(tmp)) {
            free(tmp);
            continue;
        }
        char *tmpurl = attach_domain(tmp, ourl->domain);
        if (tmpurl != NULL) {
            if ((tmpurl = url_normalized(tmpurl)) == NULL) {
                SPIDER_LOG(SPIDER_LEVEL_WARN, "Normalize url fail");
                free(tmpurl);
                continue;
            }
            SPIDER_LOG(SPIDER_LEVEL_DEBUG, "I find a url: %s", tmpurl);
            surl_enqueue(surlqueue, tmpurl, TYPE_HTML, ourl->level+1);
            free(tmpurl);
        }
    }
    return (p-str);
}
int header_postcheck(void * data) {
    Header *h = (Header *)data;
    int i = 0;
    if (h->status_code < 200 || h->status_code >= 300)
        return 1;
    if (h->content_type != NULL) {
        if (strstr(h->content_type, "text/html") != NULL)
            return 0;
        for (i = 0; i < g_conf->typecnt; i++) {
            if (strstr(h->content_type, g_conf->accept_types[i]) != NULL)
                return 0;
        }
        return 1;
    }
    return 0;
}

