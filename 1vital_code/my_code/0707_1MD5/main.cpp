 1 #include <iostream>
 2 #include <string.h>
 3 #include <stdlib.h>
 4 #include "MD5.h"
 5 
 6 int main(int argc, char **argv)
 7 {
 8     char tmpstr[256], buf[4][10];
 9     std::cout << "请输入要加密的字符串：";
10     std::cin >> tmpstr;
11     unsigned int* tmpGroup = MD5(tmpstr);
12     sprintf_s(buf[0], "%8X", tmpGroup[0]);
13     sprintf_s(buf[1], "%8X", tmpGroup[3]);
14     sprintf_s(buf[2], "%8X", tmpGroup[2]);
15     sprintf_s(buf[3], "%8X", tmpGroup[1]);
16     std::cout <<"MD5:"<< buf[0] << buf[1] << buf[2] << buf[3] << std::endl;
17     
18     delete[] tmpGroup;
19     return 0; //在此下断点才能看到输出的值
20 }