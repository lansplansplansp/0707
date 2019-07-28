#include <stdio.h>//fileno
#include <string.h>
#include <unistd.h>//STDOUT_FILENO
#include <stdarg.h>

int HttpApi_write_log (const char *format, ...) 
{
	va_list arg;//解决变参问题
	char szMsg[128] = {0};//用数组减少开辟释放空间麻烦
	va_start (arg, format);
	//将可变参数格式化输出到一个字符数组。
	vsnprintf(szMsg, 512, format, arg);//szMsg把生成的格式化的字符串存放在这里
	va_end (arg);	
	write(1,szMsg,strlen(szMsg));
}

int main()
{
    printf("The file descriptor for stdin is %d\n", fileno(stdin));//0
    printf("The file descriptor for stdout is %d\n", fileno(stdout));//1
    printf("The file descriptor for stderr is %d\n", fileno(stderr));//2
	char szMsg[128] = {0};//用数组减少开辟释放空间麻烦
	
	int nCode = 0;
	int clifd = 4;
	while(1)
	{//STDOUT_FILENO是linux系统里面的标准输出文件描述符  一个整数

		sprintf(szMsg,"accpet socket %d. \n", clifd);
		write(STDOUT_FILENO,szMsg,strlen(szMsg));
		write(1,szMsg,strlen(szMsg));
		sleep(2);
		HttpApi_write_log("%d:nCode %d, szMsg %s",__LINE__,nCode++,szMsg);//显示调用的29行
	}

	return 0;
}