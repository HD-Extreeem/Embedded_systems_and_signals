/**
 * /file test_LCDShield_runner.c
 * /author Ulrik Eklund
 * /date 2015-06-09
 * /brief Test runner program for test of the LCD shield with buttons for an Arduino Due board.
 *
 * This project provides a basic set of tests for functions controlling the digital outputs on
 * Arduino Due board, using Unity as the test framework (https://github.com/ThrowTheSwitch/Unity).
 * 
 * This file is the main() function tha calls all the relvant tests, which in turn calls the 
 * functions to be developed.
 *
 */

#include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */
#include <setjmp.h>
// #include <stdio.h>
#include <stdio_serial.h>
#include <asf.h>
#include "conf_board.h"
#include "consoleFunctions.h"
#include "../unity/unity.h"					/* Contains declarations of all functions that Unity provides */
#include "../test/test_delayFunctions.h"	/* Contains declarations of the tests for the delay used in the init function for the LCD */
#include "../test/test_buttons.h"			/* Contains declarations of the tests for the buttons */
#include "../test/test_lcdFunctions.h"		/* Contains declarations of the tests for the LCD */

void setUp(void);
void tearDown(void);
void resetTest(void);

int main(void)
{
	sysclk_init();	/* Insert system clock initialization code here (sysclk_init()). */
	board_init();

	configureConsole();	/* Initialize the console UART used from within Atmel Studio*/
	
	/* From here on the program uses the Unity testing framework */
	UnityBegin("../test/test_delay.c");	/* Run the tests for the delay from the test-file */
	RUN_TEST(test_delayTimerIsInitialisedProperly, 10);
	RUN_TEST(test_delayCountsProperly, 15);
	UnityEnd();
	
	UnityBegin("../test/test_LCDFunctions.c");	/* Run the tests for the LCD from the test-file */
	RUN_TEST(test_initialisatinOfTheLCD, 20);
	RUN_TEST(test_writingCharactersToTheLCD, 25);
	RUN_TEST(test_clearingTheLCDDisplay, 26);
	RUN_TEST(test_writing4DigitNumberOnTheLCDDisplay, 28);
	UnityEnd();
	
	UnityBegin("../test/test_buttons.c");	/* Run the tests for the ADC and buttons from the test-file */
	RUN_TEST(test_ADConverterInitialisesProperly, 30);
	RUN_TEST(test_ADConverterReadsValueWithNoButtonPressed, 25);
	RUN_TEST(test_noButtonIsPressed, 28);
	UnityEnd();
	
	//while(1)
	//{
	//	/* Infinite loop to display the current valued from the ADC reading the buttons */
	//	lcdClearDisplay(void);
	//	uint32_t tempValue = analogRead(0);
	//	lcdWrite4DigitNumber(tempValue);
	//	delayMicroseconds(500000);
	//}
	
	return 0;
}

void setUp(void)
{
	/* Do nothing */
}

void tearDown(void)
{
	/* Do nothing */
}

void resetTest(void)
{
	tearDown();
	setUp();
}

