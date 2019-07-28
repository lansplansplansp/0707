#include <iostream>
#include <stdio.h>

typedef struct _XM_SERVER_INFO_S
{
	unsigned char 		byExistServer;
	unsigned char 		byExistServer1;
	//unsigned char 		byExistServer2;
	//unsigned char 		byExistServer3;
	//unsigned char 		byExistServer4;
}XM_SERVER_INFO;

XM_SERVER_INFO g_xm_server;//全局变量和静态变量系统都自动初始化为0，该行放函数里只有一个成员变量时变量是0，一个以上就不是0了

int main()
{
	printf("%d,%d\n",g_xm_server.byExistServer,g_xm_server.byExistServer1);
	while (!g_xm_server.byExistServer) 
	{
		printf("!!\n");
		sleep(1);
	}
	return 0;
}

