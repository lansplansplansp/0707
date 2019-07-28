#ifndef __TCP_SOCK_H__
#define __TCP_SOCK_H__

#include "udp_sock.h"

int  tcp_init(int port);                //初始化tcp网络
void *tcp_send_routine(void* arg);      //发送文件线程函数
void *tcp_recv_routine(void *arg);	//接收文件线程函数


#endif
