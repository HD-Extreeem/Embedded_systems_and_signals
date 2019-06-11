/*
 * WDT.c
 * Watchdog funktion f�r att g�ra en reload av watchdogen och f�rhindra den fr�n att l�sa systemet
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