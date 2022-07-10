#include <REGX52.H>
#include "delay.h"
#include "shumaguan.h"
#include "keycode.h"
#include "AT24C02.h"
#include "I2C.h"
#define unchar unsigned char
unchar c1;
unchar c2;
unchar c3;
unchar key;
unchar temp;
unchar min;
unchar s;
unchar minis;
unchar flip;
void sec_loop()        //���ñ߽�
{
	if(minis>=100)
	{
		minis=0;
		s++;
		if(s>=60)
		{
			s=0;
			min++;
			if(min>=60){min=0;}
		}
	}
}
void timing_init()  //��ʱ����ʼ��
{
	TMOD=0x01;
	TL0 = 0xCD;		//���ö�ʱ��ֵ2ms
	TH0 = 0xF8;
	EA=ET0=1;
	TF0=0;
	TR0=1;
}


void timing()interrupt 1   //�жϺ�����ʵ���������� 
{
	TL0 = 0xCD;		//���ö�ʱ��ֵ2ms
	TH0 = 0xF8;
	TF0=0;
	c1++;
	c2++;
	c3++;
	if(c1>=10)     //ÿ��һ�ι̶�ʱ���ж��ĸ���ť����
	{
		c1=0;
		key_judge();
	}
	if(c2>=1)      //ÿ��һ��ʱ��ɨ�������
	{
		c2=0;
		shumaguan_judge();
	}
	if(c3>=5)      //ÿ��ʮmsʹ��minis��1
	{
		c3=0;
		if(flip==1){minis++;} //����flip��ֵ��������ֹͣ��һ���Ǽ�һ����ͣ���ܣ�
		
		sec_loop();
	}
}


void main()
{
	timing_init();
	while(1)
	{
		key=key_num();  //ȡ�ð����ļ���
		if(key==1)
		{
			flip=!flip;
		}
		if(key==2)      //�����㹦��
		{
			min=0;
			s=0;
			minis=0;
		}
		if(key==3)      //����ֵ�浽AT24C02��
		{
			AT24C02_writebyte(0x01,minis);
			delay_ms(5);
			AT24C02_writebyte(0x02,s);
			delay_ms(5);
			AT24C02_writebyte(0x03,min);
			delay_ms(5);
		}
		if(key==4)      //��ȡ24C02��ֵ
		{
			minis=AT24C02_readbyte(0x01);
			s=AT24C02_readbyte(0x02);
			min=AT24C02_readbyte(0x03);
		}
		shumaguan_set(1,min/10);       //��������ã�����һ����ʾmin/10������
		shumaguan_set(2,min%10);
		shumaguan_set(3,11);
		shumaguan_set(4,s/10);
		shumaguan_set(5,s%10);
		shumaguan_set(6,11);
		shumaguan_set(7,minis/10);
		shumaguan_set(8,minis%10);
		shumaguan_set(9,11);
		
//		key=key_num();
//		if(key)
//		{
//			temp=key;
//		}
//		display(1,temp);
	}
}