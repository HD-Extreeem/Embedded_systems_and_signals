/*
 * stateMachine.h
 *
 * Created: 2015-06-17 14:58:02
 *  Author: Ulrik
 */ 

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

typedef enum{
	pushButton1Event,
	pushButton2Event,
	pushButton3Event,
	releaseEvent
	}Event;
#define no_Event 4

typedef enum
{
	Locked,
	PushOne, ReleaseOne,
	PushTwo, ReleaseTwo,
	PushThree, ReleaseThree,
	PushFour,
	OPEN
} states;
#define no_State 9

typedef struct codeLock
{
	states state;	/* Let a variable hold the state of our object. */
	int lamps[4];	/* For the lamps */
} codeLockType;


typedef codeLockType *codeLockPtrType;

void startCodeLock(codeLockPtrType foo);	/* Starting the code lock state machine */
void pushButton1(codeLockPtrType foo);		/* Yellow button is pushed */
void pushButton2(codeLockPtrType foo);		/* Red button is pushed */	
void pushButton3(codeLockPtrType foo);		/* Green button is pushed */
void releaseButton(codeLockPtrType foo);	/* No button is pushed */
#endif /* STATEMACHINE_H_ */