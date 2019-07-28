#include <stdio.h>

#define KEEPALIVE_PACKAGE_SIZE sizeof(KeepalivePacket)
typedef struct RUIWEI_KEEPALIVE_PACKAGE KeepalivePacket;
struct RUIWEI_KEEPALIVE_PACKAGE//结构体定义时不能初始化
{
	RUIWEI_KEEPALIVE_PACKAGE()
	{
		headFlag = 0x55BB10A0;
		flag1 = 0x10;
		flag2 = 0x00;
		direct = 0x01B0;
	}
	int headFlag;
	char flag1;
	char flag2;
	short direct;
};
int main()
{
	KeepalivePacket ss;
	//ss.headFlag:0x55bb10a0,ss.flag1:0x10,ss.flag2:0x0,ss.direct:0x1b0
	printf("ss.headFlag:0x%x,ss.flag1:0x%x,ss.flag2:0x%x,ss.direct:0x%x\n",ss.headFlag,ss.flag1,ss.flag2,ss.direct);
	printf("sizeof(int):%d\n",sizeof(int));
	return 0;
}
