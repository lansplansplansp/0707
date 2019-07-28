#include <stdio.h>
#include <string.h>

typedef enum  _SS_ALARMIN_TYPE_E
{
	SS_ALARMIN_TYPE_NONE    = 0x00,
	SS_ALARMIN_TYPE_SENSOR  = 0x01,
	SS_ALARMIN_TYPE_MOTION  = 0x02,
	SS_ALARMIN_TYPE_VILOST  = 0x04,

}SS_ALARMIN_TYPE_E;

int SS_LOG_WriteLog(SS_ALARMIN_TYPE_E eAlarmType, unsigned char nChn);
int main()
{
	SS_ALARMIN_TYPE_E eAlarmType = SS_ALARMIN_TYPE_VILOST;
	SS_LOG_WriteLog(eAlarmType, 0);错误写法	
	//SS_LOG_WriteLog(0x04, 0);只有这一行，是错误写法	
	int year, month, day, hour, minute, second;
	//unsigned char intime[16];
	//unsigned char outtime[16];
	
	char intime[16];
	char outtime[16];
	
	memset(intime, 0, 16);
	memset(outtime, 0, 16);
	sprintf(intime, "%04d%02d%02d%02d%02d%02d", year,//intime要char型
												month,
												day,
												hour,
												minute,
												second);
	sscanf(outtime, "%4d%2d%2d%2d%2d%2d", &year,
										  &month,
										  &day,
										  &hour,
										  &minute,
										  &second);
										  
										  
	return 0;
}