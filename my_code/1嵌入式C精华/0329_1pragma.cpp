#include <iostream>

using namespace std;

#pragma pack(1) //1、4、没有都是680
typedef struct _XM_SERVER_CONFIG_S  //680
{
	int 		bEnable;
	char 		szServerUrl[64];
	int 		dwServerPort;
	char 		szDeviceID[32];
	char 		username[32];
	char 		password[32];
	char		byRes[512];

}XM_SERVER_CONFIG_S;
#pragma pack()//取消自定义字节对齐方式。

#pragma pack(8) 
 //不写就自然对界,按成员最大size对齐
struct example1 
{ 
	short a; 
	long b; 
}; 
struct example2 
{ 
	char c; 
	example1 struct1; 
	short e; 
}; 
#pragma pack()//取消自定义字节对齐方式。
int main(int argc, char* argv[]) 
{ 
	example2 struct2; 
	cout << sizeof(XM_SERVER_CONFIG_S) << endl; 
	cout << sizeof(example1) << endl; 
	cout << sizeof(example2) << endl; 
	//cout << (unsigned int)(&struct2.struct1) - (unsigned int)(&struct2) << endl; 
	return 0; 
}