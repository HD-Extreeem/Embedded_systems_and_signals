/*
 * digitalIO.c
 *
 * Created: 2015-06-10 15:11:18
 *  Author: Ulrik
 *  Modified by: Hadi & Leonard
 */ 

#include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */
#include <asf.h>		/* Only needed to get the definitions for HIGH and LOW */
#include "digitalIO.h"

#define PIOB_BASE_ADDRESS 0x400E1000U


void pinMode(int pinNumber, mode_definition mode)
{
	
	if (mode == OUTPUT)	/* You only have to program a function that cares about OUTPUT, and does nothing for the other values */
	{
		/* defines the address for enabling the parallel Input/output B register */
		uint32_t *p_PIOB_PER = (uint32_t *) (PIOB_BASE_ADDRESS+0x0000U);
		
		/* defines the address for enabling the parallel output B register */
		uint32_t *p_PIOB_OER = (uint32_t *) (PIOB_BASE_ADDRESS+0x0010U);
		
		
		if (pinNumber == 13)
		{
			/*PIO enables the register for pin 13*/
			*p_PIOB_PER |= (1<<27);
			/*Output enables the register for pin 13*/
			*p_PIOB_OER |= (1<<27);
			
		}
		else if (pinNumber == 22)
		{
			/*PIO enables the register for pin 22*/
			*p_PIOB_PER |= (1<<26);
			/*Output enables the register for pin 22*/
			*p_PIOB_OER |= (1<<26);
			
		}
		
	}
	else
	{
		/* Do nothing */
	}
}

void digitalWrite(int pinNumber, int value)
{
	/* defines the address for setting the output pins of the B register */
	uint32_t *p_PIOB_SODR = (uint32_t *) (PIOB_BASE_ADDRESS+0x0030U);
	
	/* defines the address for clearing the output pins of the B register  */
	uint32_t *p_PIOB_CODR = (uint32_t *) (PIOB_BASE_ADDRESS+0x0034U);
	
	if (value == HIGH)
	{
		/*Sets pin 13 HIGH*/
		if (pinNumber == 13)
		{
			*p_PIOB_SODR|=(1<<27);
		}
		/*Sets pin 22 HIGH*/
		else if (pinNumber==22)
		{
			*p_PIOB_SODR|=(1<<26);
		}
		
	}
	else if (value == LOW)
	{
		/*Sets pin 13 LOW*/
		if (pinNumber == 13)
		{
			*p_PIOB_CODR|=(1<<27);
		}
		/*Sets pin 22 LOW*/
		else if (pinNumber==22)
		{
			*p_PIOB_CODR|=(1<<26);
		}
				
	}
	else
	{
		/* Something is wrong */
		printf("Error!!! Something went wrong");
	}
}
