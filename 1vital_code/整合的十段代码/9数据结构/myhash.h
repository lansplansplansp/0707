#ifndef __MYHASH_H__
#define __MYHASH_H__

typedef struct shashmap
{
        char domain[128];
        char ipaddr[32];
        UT_hash_handle hh;
}shashmap_t;

void shash_insert(char *domain,char *ipaddr);
shashmap_t *shash_find(char *domain);
void shash_delete(char *domain);


#endif
