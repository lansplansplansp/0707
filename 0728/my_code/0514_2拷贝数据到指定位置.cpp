#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
	char filename[128] = {0};
	char path[36] = "0";
	char Libname[64] = "Lib";
	char sname[64] = "FACE_10017623_20190515T093157680_298.jpg";
	memcpy(Libname+3,sname+4,sizeof(sname));
	cout << Libname << endl;
	return 0;
}
//想把服务端传过来的图片名前四个字母FACE改掉