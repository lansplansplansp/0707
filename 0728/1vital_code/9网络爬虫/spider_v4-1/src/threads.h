#ifndef __MYTHREADS_H__
#define __MYTHREADS_H__
#include <pthread.h>

// typedef void *(*start_routine) (void *);

extern int create_thread(void *(*start_routine) (void *), void *arg, pthread_t * thread, pthread_attr_t * pAttr);

extern void begin_thread();
extern void next_thread();

#endif
