#ifndef SPIDER_H
#define SPIDER_H
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <getopt.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

#include "confparser.h"


/* macros */
#define MAX_MESG_LEN   1024

#define SPIDER_LEVEL_DEBUG 0
#define SPIDER_LEVEL_INFO  1
#define SPIDER_LEVEL_WARN  2
#define SPIDER_LEVEL_ERROR 3
#define SPIDER_LEVEL_CRIT  4 

static const char * LOG_STR[] = { 
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "CRIT"
};





#define SPIDER_LOG(level, format, ...) do{ \
    if (level >= g_conf->log_level) {\
        time_t now = time(NULL); \
        char msg[MAX_MESG_LEN]; \
        char buf[32]; \
        sprintf(msg, format, ##__VA_ARGS__); \
        strftime(buf, sizeof(buf), "%Y%m%d %H:%M:%S", localtime(&now)); \
        fprintf(stdout, "[%s] [%s] %s\n", buf, LOG_STR[level], msg); \
        fflush(stdout); \
    } \
    if (level == SPIDER_LEVEL_ERROR) {\
		exit(-1); \
    } \
} while(0)

extern Config *g_conf;


#endif
