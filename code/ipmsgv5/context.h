#ifndef __IPMSG_CONTEXT_H__
#define __IPMSG_CONTEXT_H__

#include "user_list.h"
#include "udp_sock.h"
#include "tcp_sock.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct context{
    int tcp_fd;
    int udp_fd;
    user_list_t *listhead;
    pthread_mutex_t muext;
}context_t;

context_t *context_init();
void context_destroy(context_t **context);

#endif

