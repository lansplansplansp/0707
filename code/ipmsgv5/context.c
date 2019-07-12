#include "context.h"

context_t *context_init(int port)
{
    context_t *context = (context_t *)malloc(sizeof(context_t));
    if(NULL == context){
        printf("context malloc");
        exit(-1);
    }
    memset(context, 0, sizeof(context));

    context->udp_fd = udp_init(IPMSG_PORT);
    context->tcp_fd = tcp_init(IPMSG_PORT);
    context->listhead = user_list_init();

    return context;
}

void context_destroy(context_t **context)
{
    if(NULL == context || NULL == *context)
        return ;
    else{
        close((*context)->udp_fd);
        close((*context)->tcp_fd);
        user_list_destroy((*context)->listhead);
        free(*context);
        *context = NULL;
    }
}




