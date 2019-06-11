

#include <inttypes.h>
#include <asf.h>
#include "btnConf.h"
#include "DelayFunctions.h"

//konfigurerar led
int ledconfset(void){
	ioport_init();

	ioport_set_pin_dir(Due_D6,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(Due_D7,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(Due_D8,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(Due_D9,IOPORT_DIR_OUTPUT);

	
}

//Konfigurerar knappar
int btnconfset(void){
	
	ioport_set_pin_dir(Due_D2, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(Due_D3, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(Due_D4, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(Due_D5, IOPORT_DIR_INPUT);
	
		ioport_set_pin_level(Due_D6,LOW);
		delayMicroseconds(10);
		ioport_set_pin_level(Due_D7,LOW);
		delayMicroseconds(10);	
		ioport_set_pin_level(Due_D8,LOW);
		delayMicroseconds(10);	
		ioport_set_pin_level(Due_D9,LOW);
		delayMicroseconds(10);
		
	while (1)
	{
		//Läser av knappar
		uint8_t d4=ioport_get_pin_level(Due_D4);
		delayMicroseconds(50);
		uint8_t d3=ioport_get_pin_level(Due_D3);
		delayMicroseconds(50);
		uint8_t d2=ioport_get_pin_level(Due_D2);
		delayMicroseconds(50);
		uint8_t d5=ioport_get_pin_level(Due_D5);
		delayMicroseconds(50);
		
		//kollar knapp 1 sätter den till hög delay sedan låg igen
		if (!d2)
		{
			ioport_set_pin_level(Due_D6,HIGH);
			delayMicroseconds(1000);
			ioport_set_pin_level(Due_D6,LOW);
		}
		//kollar knapp 2 sätter den till hög delay sedan låg igen
		if (!d3)
		{
			ioport_set_pin_level(Due_D7,HIGH);
			delayMicroseconds(1000);
			ioport_set_pin_level(Due_D7,LOW);
		}
		//kollar knapp 3 sätter den till hög delay sedan låg igen
		if (!d4)
		{
			ioport_set_pin_level(Due_D8,HIGH);
			delayMicroseconds(1000);
			ioport_set_pin_level(Due_D8,LOW);
		}
		//kollar knapp 4 sätter den till hög delay sedan låg igen
		if (!d5)
		{
			ioport_set_pin_level(Due_D9,HIGH);
			delayMicroseconds(1000);
			ioport_set_pin_level(Due_D9,LOW);
		}
	}
	
}