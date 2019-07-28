#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"
#include "myhash.h"

shashmap_t *smap = NULL;

int main()
{
	shash_insert("www.baidu.com","192.168.1.101");
	shash_insert("www.taobao.com","192.168.1.102");
	shash_insert("www.jingdong.com","192.168.1.103");
	shash_delete("www.taobao.com");
	shashmap_t *node = shash_find("www.taobao.com");
	printf("domain:%s,ipaddr = %s\n",node->domain,node->ipaddr);
	return 0;
}

void shash_insert(char *domain,char *ipaddr)
{
        shashmap_t *s = (shashmap_t *)malloc(sizeof(shashmap_t));
        strcpy(s->domain,domain);
        strcpy(s->ipaddr,ipaddr);
        HASH_ADD_STR(smap,domain,s);
}

shashmap_t *shash_find(char *domain)
{
        shashmap_t *s = NULL;
        HASH_FIND_STR(smap,domain,s);
        return s;
}

void shash_delete(char *domain)
{
        shashmap_t *s = NULL;
        HASH_FIND_STR(smap,domain,s);
        if(s!=NULL)
        {
                HASH_DEL(smap,s);
                free(s);
        }
}
