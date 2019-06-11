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
	switch(instance->state)
	{
	    case unlocked:
	        /* Already in state -> stay */
	        printf("Flash lights once\n");
	    break;
	    case locked:
	        instance->state = unlocked;
	        printf("Flash lights once\n");
	    break;
	    case doublelocked:
	        instance->state = unlocked;
	        printf("Flash lights once\n");
	    break;
	    default:
	        /* error("Illegal state"); */
	        printf("Illegal event in this state");
	    break;
	}
	return;
}

void PushLockButton(CentralLockPtr instance)
{
	switch(instance->state)
	{
	    case unlocked:
	        instance->state = locked;
	        printf("Flash lights twice\n");
	        printf("Flash lights twice\n");
	    break;
	    case locked:
	        /* Already in state -> stay in the same state */
	        printf("Flash lights twice\n");
	        printf("Flash lights twice\n");
	    break;
	    case doublelocked:
			/* Already in state -> stay in the same state */
	        printf("Flash lights twice\n");
	        printf("Flash lights twice\n");
	    break;
	    default:
	        /* error("Illegal state"); */
	    break;
	}
	return;
}

void TwoMinutetimeout(CentralLockPtr instance)
{
	switch(instance->state)
	{
	    case unlocked:
	        /* error("Illegal state"); */
	    break;
	    case locked:
	        instance->state = doublelocked;
	    break;
	    case doublelocked:
	        /* Already in state -> do nothing. */
	    break;
	    default:
	        /* error("Illegal state"); */
	    break;
	}
	return;
}