#include <REGX52.H>
//#include "delay.h"

unsigned char keynum=0;
unsigned char key_state()
{
	unsigned char num=0;
	if(P3_0==0)
	{
			num=2;
	}
	else if(P3_1==0)
	{
			num=1;
	}
	else if(P3_2==0)
	{
			num=3;
	}
	else if(P3_3==0)
	{
			num=4;
	}
	return num;
}

void key_judge()          //通过定时器功能来实现扫描那个开关按下
{
//	unsigned char keynum=0;
	static unsigned char laststate=0,nowstate=0;
	laststate=nowstate;
	nowstate=key_state();
	if(laststate==1 && nowstate==0)
	{
		keynum=1;
	}
	else if(laststate==2 && nowstate==0)
	{
		keynum=2;
	}
	else if(laststate==3 && nowstate==0)
	{
		keynum=3;
	}
	else if(laststate==4 && nowstate==0)
	{
		keynum=4;
	}
}
unsigned char key_num()
{
//	unsigned char n;
//	n=keynum;
//	return n;
	unsigned char temp;
	temp=keynum;
	keynum=0;
	return temp;
	
}