#include <REGX52.H>
#include "delay.h"
sbit SCL=P2^1;                     //定义两个管脚
sbit SDA=P2^0;                     


void I2C_start()                   //I2C开始标志为SCL高电平时SDA有一个下降沿
{
	SCL=1;
	SDA=1;
	SDA=0;
	delay_ms(2);
	SCL=0;
}

void I2C_stop()                   //I2C结束标志为SCL高电平时SDA出现一个下降沿
{
	SDA=0;
////	SCL=0;
	SCL=1;
	delay_ms(2);
	SDA=1;
}

void I2C_sentdata(unsigned char byte)//通过I2C发送数据
{
	unsigned char i;
	for(i=0;i<8;i++)                 //将要发送的byte字节从高位开始发送
	{
		SDA=byte&(0x80>>i);
		SCL=1;                       //SCL为1的时候将读取SDA
		SCL=0;                       //置零为下次做准备
	}
//	for(i=0;i<8;i++)
//	{
//		SDA=(byte<<i);
//		SCL=1;
//		SCL=0;
//	}
}

unsigned char I2C_receivedata()//通过I2C接收数据
{
	unsigned char Data=0X00;
	unsigned char i;
	SDA=1;                     //释放SDA（将SDA控制权给从机）
	delay_ms(5);
	for(i=0;i<8;i++)           //设立一个Date接收SDA传过来的数据先接收最高位
	{
		SCL=1;                 //SCL低电平期间从机将数据给到SDA，当SCL为高电平时读取一位
		if(SDA==1){Data=Data|(0x80>>i);}
		SCL=0;
	}
	return Data;
}

void I2C_sentACK(unsigned char ACK)//发送应答（主机在收到从机给的数据后要发送应答，ACK为0时表示应答）
{
	SDA=ACK;                       //SDA
	SCL=1;                         //高电平读取
	delay_ms(1);
	SCL=0;
}

unsigned char I2C_receiveACK()//接收应答
{
	unsigned char ACKbit;
	SDA=1;
	delay_ms(1);
	ACKbit=SDA;
	SCL=1;
	delay_ms(1);
	SCL=0;
	return ACKbit;
}