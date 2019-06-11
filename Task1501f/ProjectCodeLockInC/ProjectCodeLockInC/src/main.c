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
#include <asf.h>
#include "lockTask.h"
#include "ledTask.h"
#include "btnLedSetup.h"
#include "consoleFunctions.h"


int main (void)
{
	/* Initialise the Due board */	sysclk_init();	board_init();	btnLedConf();
		/* Initialise console UART */	configureConsole();	/* Print demo information on the terminal*/	printf("-- FreeRTOS Exemple – Tasks --\n\r");	printf("-- %s\n\r", BOARD_NAME);	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);		/* Create the first task for running the code lock */	if (xTaskCreate(task_codeLock, (const signed char * const) "codeLock", TASK_CODELOCK_STACK_SIZE, NULL, TASK_CODELOCK_STACK_PRIORITY, NULL) != pdPASS) {		printf("Failed to create code lock task\r\n");	}		/* Create the second task with blinking LED */	if (xTaskCreate(task_led, (const signed char * const) "Led", TASK_LED_STACK_SIZE, NULL, TASK_LED_STACK_PRIORITY, NULL) != pdPASS) {		printf("Failed to create test led task\r\n");	}	/* Start the FreeRTOS scheduler running all tasks indefinitely*/	vTaskStartScheduler();	/* The program should only end up here if there isn’t enough memory to create the idle task */

}
