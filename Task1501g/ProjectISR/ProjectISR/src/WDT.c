/*
 * WDT.c
 * Watchdog funktion för att göra en reload av watchdogen och förhindra den från att låsa systemet
 * Created: 2017-01-11 08:30:11
 *  Author: Hadi & Leonard
 */ 

#include <asf.h>
#include "WDT.h"
#include <inttypes.h>

void watchdogReload(){
	uint32_t *p_wdt = (uint32_t *) (wdt_addr);
	*p_wdt = (0x01 << 0) | (0xA5 << 24);
}