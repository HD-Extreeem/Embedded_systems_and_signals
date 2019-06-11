/*
 * lcdApplication.c
 *
 * Created: 2015-09-10 08:44:50
 *  Author: Leonard & Hadi
 */ 

#include "lcdApplication.h"
#include "LCDFunctions.h"
#include "DelayFunctions.h"
#include "buttons.h"	/* to get the buttontype definiton */
int adcRead;
int lcdWrite4DigitNumber(int number)
{
	lcdWrite((number/1000)+48, HIGH);
	lcdWrite(((number%1000)/100)+48, HIGH);
	lcdWrite(((number%100)/10)+48, HIGH);
	lcdWrite((number%10)+48, HIGH);
	return 0;	/* Assuming everything went ok */
}

int lcdWriteAsciiString(const char *string)
/* writes an ascii string up to 40 characters on the LCD display */
{
	/* Skriver ut hela strängen på lcd sålänge den inte kommer till slutet \0*/
	
	while (*string !='\0')
	{
		lcdWrite(*string,HIGH);
		string++;
	}
	
	return 0;	/* Assuming everything went ok */
}

int lcdWriteButtonValue(buttonType inputButton)
/* Writes the text corresponding to one of the buttosn on the LCD dispaly using lcdWriteAsciiString() 
 * Output should be one of SELECT, LEFT, UP, DOWN, RIGHT on the LCD display
 * if no buttons is pushed you can chose on displaying nothing or NONE  */
{
	/* Kollar vilken knapp som valts och skriver ut på lcd'n */
	if (inputButton==btnSELECT)
	{
		lcdWriteAsciiString("SELECT");
	}
	
	else if (inputButton==btnNONE)
	{
		lcdWriteAsciiString("NONE");
	}
	
	else if (inputButton==btnRIGHT)
	{
		lcdWriteAsciiString("RIGHT");
	}
	
	else if (inputButton==btnLEFT)
	{
		lcdWriteAsciiString("LEFT");
	}
	
	else if (inputButton==btnUP)
	{
		lcdWriteAsciiString("UP");
	}
	
	else if (inputButton==btnDOWN)
	{
		lcdWriteAsciiString("DOWN");
	}	
	
	return 0;	/* Assuming everything went ok */
}