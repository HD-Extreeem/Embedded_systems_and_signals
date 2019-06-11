/*
 * buttons.c
 * Filen hanterar knapptryckningar på btn/lcd shielden
 * Created: 2015-06-12 16:28:53
 * Author: Leonard & Hadi
 */ 

#include "buttons.h"
#include "lcdApplication.h"
#include "adcFunctions.h"	/* Must use the value from the ADC to figure out which button */
int adcRead;

//Läser av knappval
buttonType readLCDbutton(void)
{
	//läser in analog 
	adcRead=analogRead(0);
	
	if (adcRead>3190 && adcRead<3200)
	{
		return btnNONE;
	}
	
	else if (adcRead>2425 && adcRead<2440)
	{
		return btnSELECT;
	}
	
	else if (adcRead>1785 && adcRead<1800)
	{
		return btnLEFT;
	}
	
	else if (adcRead>1245 && adcRead<1260)
	{
		return btnDOWN;
	}
			
	else if (adcRead>550 && adcRead<570)
	{
		return btnUP;
	}

	else if (adcRead>0000 && adcRead<0015)
	{
		return btnRIGHT;
	}
	
	else{
		lcdWriteAsciiString("ERROR");
	}

}