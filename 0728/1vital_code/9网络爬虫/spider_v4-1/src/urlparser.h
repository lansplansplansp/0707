#ifndef URLPARSER_H
#define URLPARSER_H
#include <regex.h>
#include "spider.h"
#include "url.h"




//extern int extract_url(char *str, Url *ourl);

int extract_url(char *str,  ourlnode_t *ourl);
int header_postcheck(void * data) ;
char * url2fn(const ourlnode_t* url);



#endif 
