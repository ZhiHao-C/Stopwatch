#ifndef __I2C_H__
#define __I2C_H__

void I2C_start();
void I2C_stop();
void I2C_sentdata(unsigned char byte);
unsigned char I2C_receivedata();
void I2C_sentACK(unsigned char ACK);
unsigned char I2C_receiveACK();

#endif