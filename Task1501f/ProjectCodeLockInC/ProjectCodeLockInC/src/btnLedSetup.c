/*
 * btnSetup.c
 * Initierar alla knappar och led f�r att kunna skriva till eller l�sa
 * Created: 2016-12-14 09:00:57
 *  Author: Leonard & Hadi
 */ 

#include <inttypes.h>
#include <asf.h>
#include "btnLedSetup.h"

int btnLedConf(void){
	//S�tter ig�ng io portarna
	ioport_init();
	
	//btn konfigurering
	ioport_set_pin_dir(Due_D2, IOPORT_DIR_INPUT);//knapp1
	ioport_set_pin_dir(Due_D3, IOPORT_DIR_INPUT);//knapp2
	ioport_set_pin_dir(Due_D4, IOPORT_DIR_INPUT);//knapp3
	
	//Led konfigurering
	ioport_set_pin_dir(Due_D6,IOPORT_DIR_OUTPUT);//led1
	ioport_set_pin_dir(Due_D7,IOPORT_DIR_OUTPUT);//led2
	ioport_set_pin_dir(Due_D8,IOPORT_DIR_OUTPUT);//led3
	ioport_set_pin_dir(Due_D9,IOPORT_DIR_OUTPUT);//main stora led	
}
