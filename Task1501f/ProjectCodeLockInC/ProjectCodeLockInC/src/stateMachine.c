/*
 * stateMachine.c
 *
 * Created: 2015-08-05 11:10:34
 *  Author: Uek
 *  co Authors Leonard&Hadi
 */ 

#include "stateMachine.h"
#include "lockTask.h"

codeLockType SM;			/* The memory area for the state machine */
codeLockPtrType instance;	/* A pointer to a state machine of this type */


//Tabell med alla h�ndelser vid olika states
const states TransitionTable[no_State][no_Event] = {
	{PushOne, Locked,Locked,Locked},
	{PushOne, PushOne, PushOne,ReleaseOne},
	{Locked, Locked,PushTwo,ReleaseOne},
	{PushTwo,PushTwo,PushTwo,ReleaseTwo},
	{Locked,Locked,PushThree,ReleaseTwo},
	{PushThree,PushThree,PushThree,ReleaseThree},
	{Locked,PushFour,Locked,ReleaseThree},
	{PushFour,PushFour,PushFour,OPEN},
	{Locked,Locked,Locked,OPEN}
};

/* 
 * The assignment of the pointer to the memory area for the state machine,
 * instance = &SM, is done in test_FSM_runner.c
 */
void startCodeLock(codeLockPtrType foo) /* Making sure the FSM starts in the right state */
{
	//Startar i locked state
	foo->state = Locked;
	return;
}

void pushButton1(codeLockPtrType foo)		/* Yellow button is pushed */
{
	//H�mtar nuvarande state
	const states currrentstate = foo->state;
	//kollar i tabell vilka m�jliga h�ndelser som kan ske
	foo->state = TransitionTable[currrentstate][pushButton1Event];
	return;
}

void pushButton2(codeLockPtrType foo)		/* Knapp 2 tryckt vit */
{
	//H�mtar nuvarande state
	const states currrentstate = foo->state;
	//kollar i tabell vilka m�jliga h�ndelser som kan ske
	foo->state = TransitionTable[currrentstate][pushButton2Event];
	return;
}

void pushButton3(codeLockPtrType foo)		/* Knapp 3 tryckt r�d */
{
	//H�mtar nuvarande state
	const states currrentstate = foo->state;
	//kollar i tabell vilka m�jliga h�ndelser som kan ske
	foo->state = TransitionTable[currrentstate][pushButton3Event];
	return;
}

void releaseButton(codeLockPtrType foo)	/* Ingen knapp tryckt */
{
	//H�mtar nuvarande state
	const states currrentstate = foo->state;
	//kollar i tabell vilka m�jliga h�ndelser som kan ske
	foo->state = TransitionTable[currrentstate][releaseEvent];
	return;
}