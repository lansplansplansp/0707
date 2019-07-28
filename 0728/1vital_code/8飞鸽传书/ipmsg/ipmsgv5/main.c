#include <stdio.h>
#include <pthread.h>
#include "context.h"
#include "udp_sock.h"
#include "tcp_sock.h"

int main()
{
    context_t* context;
    pthread_t udpsend_tid;
    pthread_t udprecv_tid;
    pthread_t tcpsend_tid;
    pthread_t tcprecv_tid;

    context = context_init();

    pthread_create(&udprecv_tid, NULL, udp_recv_routine, (void *)context);
    pthread_create(&udpsend_tid, NULL ,udp_send_routine, (void *)context);
    pthread_create(&tcpsend_tid, NULL, tcp_send_routine, (void *)context);
    pthread_create(&tcprecv_tid, NULL, tcp_recv_routine, (void *)context);

    pthread_join(udprecv_tid, NULL);
    pthread_join(udpsend_tid, NULL);
    pthread_join(tcpsend_tid, NULL);

    context_destroy(&context);

    return 0;
}
