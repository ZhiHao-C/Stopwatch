#include <REGX52.H>
#include "I2C.h"
#define AT24C02_address 0xa0             //写地址，读地址加1


void AT24C02_writebyte(unsigned char address,Data)//往24c02地址为address 的地方写入数据Data
{
	
	I2C_start();
	I2C_sentdata(AT24C02_address);// 通过I2C写从机地址（AT24C02默认地址看第三条）
	I2C_receiveACK();
	I2C_sentdata(address);        //再写需要写入数据的地址（告诉24c02要写入数据的地址）
	I2C_receiveACK();
	I2C_sentdata(Data);           //写入数据
	I2C_receiveACK();
	I2C_stop();
	
}

unsigned char AT24C02_readbyte(unsigned char address)
{
	unsigned char Data;
	I2C_start();
	I2C_sentdata(AT24C02_address);//通过I2C写从机地址
	I2C_receiveACK();
	I2C_sentdata(address);        //再写需要读取数据的地址（告诉24c02要写入数据的地址）
	I2C_receiveACK();
	I2C_start();
	I2C_sentdata(AT24C02_address+1);//通过I2C写从机地址（读）
	I2C_receiveACK();
	Data=I2C_receivedata();
	I2C_sentACK(1);
	I2C_stop();
	return Data;
}