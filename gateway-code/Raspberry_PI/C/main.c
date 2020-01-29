#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "rwops.h"
#include "mainops.h"
#include "register.h"
#include "bcm2835.h"

extern unsigned char data_rx[];


int main(void)
{
	int ret;
	wiringPiSetupSys ();
	if (!bcm2835_init())
	{
		printf("error BCM \n");
		return 1;
	}
/*
	pinMode(7, OUTPUT);
	pinMode(29, OUTPUT);
	pinMode(24, OUTPUT);
	pinMode(23, GPIO_CLOCK);
	pinMode(21, INPUT);
	pinMode(19, OUTPUT);
	pinMode(31, INPUT);

	digitalWrite(29,1);
	digitalWrite(7,1);
*/
	printf("Test du SPI \n");
	ret = wiringPiSPISetupMode(0, 500000, 0);
	printf("Initialisation du device SPI %d \n",ret);
	printf("Valeur sur 22 : %d \n",bcm2835_gpio_lev(25));
	initialize();

	write_ZIGBEE_long(RFCON0, 0xFF);
	ret=read_ZIGBEE_long(RFCON0);

	printf("PAN ID : %x%x \n",read_ZIGBEE_short(PANIDH),read_ZIGBEE_short(PANIDL));
	printf("CONTENU RFCON0 : %x \n",ret);

	while(1){
		if(Detect_INT() == 1 ){             // Debounce line INT
      		ret = read_ZIGBEE_short(0x31); // Read and flush register INTSTAT
      		read_RX_FIFO();
		printf("Data reçues low : %c \n",data_rx[0]);
		printf("Data reçues high: %c \n",data_rx[1]);
		}
	}






//	ret = read_ZIGBEE_short(0x18);
//	printf("Valeur à l'adresse 0x18 = %x \n",ret);

//	ret = read_ZIGBEE_long(0x200);
//	printf("Valeur à l'address 0x200 = %x \n",ret);
}