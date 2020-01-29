#include <stdio.h>
#include <stdlib.h>
#include "rwops.h"
#include <unistd.h>
#include <wiringPi.h>
#include "register.h"
#include <bcm2835.h>

unsigned char lost_data, lqi, rssi2;
unsigned char data_rx[]={0};

void channelSelector(int channel){

	write_ZIGBEE_long(RFCON0,(((channel-11) << 4) | 0x3));
	write_ZIGBEE_short(RFCTL,0x04);
	write_ZIGBEE_short(RFCTL,0x00);
	sleep(1);
}


void setAddress16_write(unsigned short address16 )
{
	write_ZIGBEE_short(SADRH, address16 >> 8);
	write_ZIGBEE_short(SADRL, address16 % 0xFF);
}

void setPan(unsigned short panid)
{
	write_ZIGBEE_short(PANIDH, panid >> 8);
	write_ZIGBEE_short(PANIDL, panid & 0xff);
}

void initialize(void){

	int temp;

	write_ZIGBEE_short(0x2A,0x07);
	while(read_ZIGBEE_short(0x2A) % 0x7 != 0){
		printf("WAIT BEFORE RESET PIN \n");
	}


	write_ZIGBEE_short(PACON2,0x98);
	//printf("PACON2 : %x \n", read_ZIGBEE_short(PACON2));
	write_ZIGBEE_short(TXSTBL,0x95);
	write_ZIGBEE_long(RFCON0,0x03);
	write_ZIGBEE_long(RFCON1,0x01);
	write_ZIGBEE_long(RFCON2,0x80);
	write_ZIGBEE_long(RFCON6,0x90);
	write_ZIGBEE_long(RFCON7,0x80);
	write_ZIGBEE_long(RFCON8,0x10);
	write_ZIGBEE_long(SLPCON1,0x21);

	write_ZIGBEE_short(BBREG2,0x80);
	write_ZIGBEE_short(CCAEDTH,0x60); // Set CCA ED threshold to -69 dm
	write_ZIGBEE_short(BBREG6,0x40);
	write_ZIGBEE_short(INTCON_M,0xF6);

	setPan(0xCAFE);
	setAddress16_write(0x4202);

	//pinMode(31,INPUT);
	//pinMode(37,OUTPUT);

	channelSelector(12);


}



void flush_RX_FIFO_pointer(){

	unsigned char temp;
	temp = read_ZIGBEE_short(0x0D);
	temp = temp | 0x01;
	write_ZIGBEE_short(0x0D, temp);
}




/*
char Detect_INT() {
  char i = 0, j = 0, intn_d = 0;
  for(i = 0; i < 5; i++) {
    intn_d = bcm2835_gpio_lev(25);
    //printf("%d\n",digitalRead(21));
    //printf("%d\n",intn_d);
    write_ZIGBEE_short(INTSTAT,0b00001001);
    printf("Valeur du registre INTSTAT : %x \n",read_ZIGBEE_short(INTSTAT));
    sleep(1);
    if (intn_d == 1)
      j++;
  }
  if (j > 2)
    return 1;
  else
    return 0;
}
*/


int Detect_INT(){
  unsigned int last_INT = read_ZIGBEE_short(INTSTAT);
  if(last_INT & INT_RXIF){
	return 0;
  }
  else
  {
	return 1;
  }

}




void read_RX_FIFO(){

  unsigned char data_len = 2;
  unsigned char header_len = 9;
  unsigned char data_RX_FIFO[17];

//unsigned char data_rx[]={0};

  unsigned char temp = 0;
  int i = 0;

  temp = read_ZIGBEE_short(BBREG1);      // disable receiving packets off air.
  temp = temp | 0x04;                    // mask for disable receiving packets
  write_ZIGBEE_short(BBREG1, temp);

  for(i=0; i<128; i++) {
    //printf("Addresse %i contenu %c \n",i,read_ZIGBEE_long(0x300 + i));
    if(i <  (1 + data_len + header_len + 2 + 1 + 1))
      data_RX_FIFO[i] = read_ZIGBEE_long(0x300 + i);  // reading valid data from RX FIFO
    if(i >= (1 + data_len + header_len + 2 + 1 + 1))
      lost_data = read_ZIGBEE_long(0x300 + i);
  }

  data_rx[0] = data_RX_FIFO[header_len + 1];               // coping valid data
  lqi   = data_RX_FIFO[1 + header_len + data_len + 2];  // coping valid data
  rssi2 = data_RX_FIFO[1 + header_len+ data_len + 3];  // coping valid data



  temp = read_ZIGBEE_short(BBREG1);      // enable receiving packets off air.
  temp = temp & (!0x04);                 // mask for enable receiving
  write_ZIGBEE_short(BBREG1, temp);

}