#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

void write_ZIGBEE_short(unsigned char address, unsigned char data_r) {

  address = ((address << 1) & 0b01111111) | 0x01; // calculating addressing mode

  unsigned char buff[2];
  buff[0] = address;
  buff[1] = data_r;

  wiringPiSPIDataRW (0, buff, 2);

}

unsigned char read_ZIGBEE_short(short int address) {

  address = (address << 1) & 0b01111110;      // calculating addressing mode

  unsigned char buff[2];
  buff[0] = address;
  buff[1] = 0xFF;

  wiringPiSPIDataRW (0, buff, 2);

  return buff[1];

}

void write_ZIGBEE_long(int address, unsigned char data_r) {

	unsigned char address_high = (((unsigned char)(address >> 3)) & 0x7F) | 0x80;
	unsigned char address_low  = (((unsigned char)(address << 5)) & 0xE0) | 0x10;
	unsigned char buff[3];
	buff[0] = address_high;
	buff[1] = address_low;
	buff[2] = data_r;

	wiringPiSPIDataRW (0, buff, 3);
}



unsigned char read_ZIGBEE_long(int address)
{
	unsigned char address_high = (((unsigned char)(address >> 3)) & 0x7F) | 0x80;
	unsigned char address_low = (((unsigned char)(address << 5)) & 0xE0);
	unsigned char buff[3];
	buff[0] = address_high;
	buff[1] = address_low;
	buff[2] = 0xFF;

	wiringPiSPIDataRW (0, buff, 3);
	return buff[2];
}
