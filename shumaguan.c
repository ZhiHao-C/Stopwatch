#include <REGX52.H>
#include "delay.h"
unsigned char shumaguan_buf[9]={0,10,10,10,10,10,10,10,10};
int a[12]={~0xC0,~0xF9,~0xA4,~0xB0,~0x99,~0x92,~0x82,~0xF8,~0x80,~0x90,0x00,0x40};
void display(unsigned char L,int num)
{
	switch(L)
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=a[num];
//	delay_ms(1);
//	P0=0x00;
	
}
void shumaguan_judge() //扫描数码管
{
	static unsigned i=0;
	i++;
	display(i,shumaguan_buf[i]);
	if(i>7){i=0;}
}

void shumaguan_set(unsigned char Location,int n)  //设置数码管将n显示在第几个数码管
{
	shumaguan_buf[Location]=n;
}