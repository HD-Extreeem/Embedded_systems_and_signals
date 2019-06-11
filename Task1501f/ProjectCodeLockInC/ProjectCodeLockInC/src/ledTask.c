/*
 * CFile2.c
 *
 * Created: 2016-12-14 08:34:58
 *  Author: Spellabbet
 */ 
#include "ledTask.h"
#include <asf.h>

  

void task_led(void *pvParam){
	portTickType xlastWakeTime;
	const portTickType xTimeIncrement = 500;
	
	xlastWakeTime = xTaskGetTickCount();
	while(1){
		vTaskDelayUntil(&xlastWakeTime,xTimeIncrement);
		gpio_toggle_pin(LED0_GPIO);
	}
}