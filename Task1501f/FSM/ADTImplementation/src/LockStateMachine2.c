#include <stdio.h>
#include "LockStateMachine.h"

const char* getStateName(State foo) 
{
   switch (foo) 
   {
      case unlocked: return "Unlocked";
      case locked: return "Locked";
      case doublelocked: return "Double Locked";
   }
}

void PushUnlockButton(CentralLockPtr instance)
{
	instance->state = unlocked;
	printf("Flash lights once\n");
	return;
}

void PushLockButton(CentralLockPtr instance)
{
	switch(instance->state)
	{
	    case unlocked:
	        instance->state = locked;
	    break;
	    default:
	        /* Stay in the same state */
	    break;
	}
    printf("Flash lights twice\n");
    printf("Flash lights twice\n");
	return;
}

void TwoMinutetimeout(CentralLockPtr instance)
{
	switch(instance->state)
	{
	    case locked:
	        instance->state = doublelocked;
	    break;
	    default:
	        /* Stay in same state */
	    break;
	}
	return;
}