/**
 * @file main.c
 *
 * @brief main file initiating all necessary hardware and then blinking LED
 *
 * @author Leonard & Hadi
 *
 * @date 2015-12-17
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include <inttypes.h>
#include "digitalIO.h" /* Functions developed in Task1501a */
#include "WDT.h"
#include "LedTask.h"
#include "da.h"
#include "DelayFunctions.h"
#include "conf_board.h"
#include "consoleFunctions.h"
#include "tcc_conf.h"
static int count = 0; //countern f�r vilket index
uint32_t da[16] = {1769,2125,2427,2629,2700,2629,2427,2125,1769,1412,1110,908,838,908,1110,1412}; //da array med 16 v�rden f�r sinusv�gen
/* Adress f�r port b registret f�r att s�tta bit */
uint32_t *p_PIOB_SODR = (uint32_t *) (PIOB_BASE_ADDRESS+0x0030U);

/* Adress f�r port b registret f�r att t�mma bit */
uint32_t *p_PIOB_CODR = (uint32_t *) (PIOB_BASE_ADDRESS+0x0034U);

#define CONF_BOARD_KEEP_WATCHDOG_AT_INIT 1


/* Timer counter vilket kallas vid interrupt, skriver till da utg�ngen*/
void TC5_Handler(void){
	*p_PIOB_SODR |= (1<<26); //s�tter led 22 p�
	uint32_t brus= da[count]+((trng_read_output_data(TRNG)/14417920)-149); //adderar sinusv�gens v�rde med brus random mellan -0,08 till 0,08v
	dacc_write_conversion_data(DACC, brus); //skriver till da utg�ngen
	count = (count+1)%16; //r�knar upp en counter
	volatile uint32_t dummy; //en dummy variabel 
	dummy = tc_get_status(TC1, 2); //h�mtar status och t�mmer det s� att inte interrupt kallas igen
	UNUSED(dummy); //t�mmer dummy variablen
	*p_PIOB_CODR |= (1<<26); //st�nger av led 22
}

int main (void)
{
	sysclk_init();
	board_init();
	delayInit();
	configureConsole(); //konfigurerar konsolen
	daccInit(); //initierar da omvandlaren
	configure_tc(); //konfigurerar och initierar timer countern f�r interuppt
	pmc_enable_periph_clk(ID_TRNG); //s�tter ig�ng true number generatorn
	trng_enable(TRNG); //initierar true number generatorn och s�tter ig�ng den
	
	pinMode(22,OUTPUT);
	pinMode(13,OUTPUT);
	
	while (1)
	{
		delayMicroseconds(1000000);
		digitalWrite(13,HIGH);
		watchdogReload();
		delayMicroseconds(1000000);
		digitalWrite(13,LOW);
	}
	
	return 0;
}


