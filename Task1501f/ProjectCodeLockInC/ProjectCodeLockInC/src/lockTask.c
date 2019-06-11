/*
 * taskLock.c
 *
 * Created: 2016-12-14 08:19:32
 *  Author: Leo & Hadi
 */ 

#include <asf.h>
#include "lockTask.h"
#include "stateMachine.h"
#include "delayFunctions.h"
#include "consoleFunctions.h"
#include "btnLedSetup.h"

extern codeLockType SM;				/* The memory area for the state machine */
extern codeLockPtrType instance;	/* A pointer to a state machine of this type */


//Task som skall köras
void task_codeLock(void *pvParam){
	instance = &SM;				/* Pointing to the state machine used */
	startCodeLock(instance);	//startar i locked sätter igång låset
	
	while (1)
	{
		//Läser av knapparna
		uint8_t d4=ioport_get_pin_level(Due_D4);
		
		uint8_t d3=ioport_get_pin_level(Due_D3);
		
		uint8_t d2=ioport_get_pin_level(Due_D2);
			
		//kollar ifall knapp 1 tryckt ska maskinen trycka på 1
		if (!d2)
		{
			pushButton1(instance);
		}
		//kollar ifall knapp 2 tryckt ska maskinen trycka på 2
		else if (!d3)
		{
			pushButton2(instance);
		}
		//kollar ifall knapp 3 tryckt ska maskinen trycka på 2
		else if (!d4)
		{
			pushButton3(instance);
		}
		//kollar ifall inga knappar tryckt ska maskinen släppa
		else if (d4 && d3 && d2)
		{
			releaseButton(instance);
		}
		else {
			//do nothing.....
		}
		
		//sätter leden beroende på vilken state enligt tillståndsdiagrammet
		const states stateStatus = instance->state;
		switch(stateStatus){
			
			case Locked:
			ioport_set_pin_level(Due_D6,LOW);
			ioport_set_pin_level(Due_D7,LOW);
			ioport_set_pin_level(Due_D8,LOW);
			ioport_set_pin_level(Due_D9,HIGH);
			break;
			
			case PushOne:break;
			
			case ReleaseOne:ioport_set_pin_level(Due_D6,HIGH);break;
			
			case PushTwo:break;
			
			case ReleaseTwo:ioport_set_pin_level(Due_D7,HIGH);break;
			
			case PushThree:break;
			
			case ReleaseThree:ioport_set_pin_level(Due_D8,HIGH);break;
			
			case PushFour:break;
			
			case OPEN:ioport_set_pin_level(Due_D9,LOW);break;
			
		}
		
		vTaskDelay(200);
	}
}