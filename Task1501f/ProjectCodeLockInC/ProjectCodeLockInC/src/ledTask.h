/*
 * IncFile1.h
 *
 * Created: 2016-12-14 08:40:14
 *  Author: Spellabbet
 */ 


#ifndef ledTask_H_
#define ledTask_H_

#define TASK_LED_STACK_SIZE (1024/sizeof(portSTACK_TYPE))
#define TASK_LED_STACK_PRIORITY (tskIDLE_PRIORITY)
#define LED0_GPIO PIO_PB27_IDX

void task_led(void *pvParam);
#endif /* ledTask_H_ */