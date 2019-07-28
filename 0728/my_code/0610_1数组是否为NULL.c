#include <stdio.h>
#include <string.h>

int main()
{	
	char *pS = NULL;
	char pSendBuff[1024] = {0};
	printf("pSendBuff :%s\n",pSendBuff);//pSendBuff :
	printf("pSendBuff :%p\n",pSendBuff);	
	printf("pS :%p\n",pS);

	if (pS == 0)
	{
		printf("*pSendBuff = %c\n",*pSendBuff);//空
		printf("*pSendBuff = %d\n",*pSendBuff);//0
		printf("pSendBuff == NULL\n");
	}
	strcpy(pSendBuff,"hello");
	printf("*pSendBuff = %c\n",*pSendBuff);//h
	printf("*pSendBuff = %d\n",*pSendBuff);//104
	pSendBuff[0] = 0;
	printf("*pSendBuff = %c\n",*pSendBuff);//空
	printf("*pSendBuff = %d\n",*pSendBuff);//0
	return 0;
}
//数组没有NULL的情况，char pSendBuff[1024];时有乱码输出，char pSendBuff[1024] = {0};无输出。

