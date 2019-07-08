#include <stdio.h>

int main()
{
	char serve[24] = "9400";
	short port;
	unsigned long long nTempValue = 0;
	sscanf(serve,"%hi",&port);
	printf("port = %hi\n",port);
	sscanf("0011040019e3","%qx",&nTempValue);//%qx:  为无符号64位整数(unsigned long long),打印使用数字0-9的十六进制,小写a-f;
	printf("%qx\n",nTempValue);//1040019e3,是%x的会溢出全部为ffffffff(32位)
	printf("%d,%d\n",sizeof(long),sizeof(long long));
	return 0;
}
//sscanf(pGateway->valuestring, "%lx", &nTempValue)
//unsigned long nTempValue = 0;