/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */
#include <setjmp.h>
// #include <stdio.h>
#include <stdio_serial.h>
#include "conf_board.h"
#include "consoleFunctions.h"
#include "../unity/unity.h"					/* Contains declarations of all functions that Unity provides */
//#include "../test/test_delayFunctions.h"	/* Contains declarations of the tests for the delay used */
#include "../test/test_stateMachine.h"
#include "../src/stateMachine.h"

void setUp(void);
void tearDown(void);
void resetTest(void);

extern codeLockType SM;				/* The memory area for the state machine */
extern codeLockPtrType instance;	/* A pointer to a state machine of this type */

int main (void)
{
	sysclk_init();	/* Insert system clock initialization code here (sysclk_init()). */
	board_init();

	configureConsole();	/* Initialize the console UART used from within Atmel Studio*/
		
	/* From here on the program uses the Unity testing framework */
		
	//UnityBegin("../test/test_delayFunctions.c");	/* Run the tests for the delay from the test-file */
	//RUN_TEST(test_delayTimerIsInitialisedProperly, 5);
	//RUN_TEST(test_delayCountsProperly, 8);
	//UnityEnd();
	
	instance = &SM;				/* Pointing to the state machine used */
	
	UnityBegin("../test/test_stateMachine.c");	/* Run the tests for the delay from the test-file */
	RUN_TEST(test_stateMachineStartsInLockedState, 10);

	RUN_TEST(test_stateGoesToPushOneWhenFirstCorrectButtonIsPressed, 20);
	RUN_TEST(test_stateGoesToLockedWhenFirstIncorrectButtonIsPressed, 22);

	RUN_TEST(test_stateGoesToPushTwoWhenSecondCorrectButtonIsPressed, 30);
	RUN_TEST(test_stateGoesToLockedWhenSecondIncorrectButtonIsPressed, 32);

	RUN_TEST(test_stateGoesToPushThreeWhenThirdCorrectButtonIsPressed, 40);
	RUN_TEST(test_stateGoesToLockedWhenThirdIncorrectButtonIsPressed, 42);

	RUN_TEST(test_stateGoesToOpenWhenFourthCorrectButtonIsPressed, 50);
	RUN_TEST(test_stateGoesToLockedWhenFourthIncorrectButtonIsPressed, 52);
	UnityEnd();
		
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