#include <iostream>
#include <stdio.h>

using namespace std;
#define EX_FONT_WORD(value) (value)
#define EX_FONT_UNICODE_VAL(value) (value)

typedef struct_wide_unicode_font16x16//16*16点阵的汉字
{
	unsigned char word[3];//一个汉字占两个字节，加一个结尾符
	int value;//内码
	unsigned char data[32];//字模点阵
}Unicode;
//汉字数量
#define CHINESE_CHAR_NUM 4

Unicode chinese[CHINESE_CHAR_NUM]=
{
	{
		EX_FONT_WORD("业");
		EX_FONT_UNICODE_VAL(0x4e1a)//业的内容
		{
			
		}
	},
	{
		
	},
	{
		
	},
	{
		
	}
}

int main()
{
	return 0;
}