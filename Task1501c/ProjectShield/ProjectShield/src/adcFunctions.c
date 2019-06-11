/*
 * adcFunctions.c
 *
 * Created: 2015-06-16 09:00:18
 *  Author: Leonard & Hadi
 */ 

#include <inttypes.h>
#include <asf.h>
#include "adcFunctions.h"
#include "DelayFunctions.h"

//V�rdet p� analoga pinnen
uint32_t adcvalue;

int analogInit(int pinNumber)
{
	/* 
	 * The pin number is the analog input pin on the DUe board, see http://www.arduino.cc/en/Hacking/PinMappingSAM3X
	 * Obviously it starts at analog 0 which is equivalent to the analog input on PA16
	 * so you need to figure out which AD channel this corresponds to
	 *
	 * See code example http://asf.atmel.com/docs/latest/sam.drivers.adc.adc_example.arduino_due_x/html/sam_adc_quickstart.html
	 * It is assumed that the AD-converter is using 12 bits
	 */
	
	pmc_enable_periph_clk(ID_ADC);	/* power the clock for the ADC with pmc_enable_periph_clk(ID_ADC) */
	

	// Om pinNumber �r 0, initierar vi adc f�r analog pin 0
	if (pinNumber==0)
	{
		adc_init(ADC,sysclk_get_main_hz(), 1000000, 8);
		adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
		adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
		adc_enable_channel(ADC, ADC_CHANNEL_7);
		adc_configure_trigger(ADC, ADC_TRIG_SW,0);
		
	}
	
	return 0;	/* if everything is ok */
}
//L�ser in v�rdet p� adc och returnerar v�rdet
uint32_t analogRead(int pinNumber)
{
	/* Kollar vilken pinNumber som skall l�sas av */
	if (pinNumber==0)
	{
		adc_start(ADC);
		delayMicroseconds(500);
		adcvalue = adc_get_latest_value(ADC);
		delayMicroseconds(500);
		return adcvalue;	/* Replace with actual value read from A/D input*/
	}
}