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

State CurrentState = unlocked;

void LockStateMachine(Event NewEvent)
{
	State NextState;

	switch(CurrentState)
	{
	    case unlocked :
	        switch(NewEvent)
	        {
	            case PushUnlockButton:
	                NextState = unlocked;
	                printf("Flash lights once\n");
	                printf("Car is unlocked\n");
	            break;
	            case PushLockButton:
	                NextState = locked;
	                printf("Flash lights twice\n");
	                printf("Flash lights twice\n");
	                printf("Car is locked\n");
	            break;
	            default:
	                /* We should never end up here */
	                printf("Error\n");
	            break;
	        }
	    break;
	    case locked :
	        switch(NewEvent)
	        {
	            case PushUnlockButton:
	                NextState = unlocked;
	                printf("Flash lights once\n");
	                printf("Car is unlocked\n");
	            break;
	            case PushLockButton:
	                NextState = locked;
	                printf("Flash lights twice\n");
	                printf("Flash lights twice\n");
	                printf("Car is locked\n");
	            break;
	            case TwoMinuteTimeout:
	                NextState = doublelocked;
	                printf("Car is double locked\n");
	            break;
	            default:
	                /* We should never end up here */
	                printf("Error\n");
	            break;

	        }
	    break;
	    case doublelocked :
	        switch(NewEvent)
	        {
	            case PushUnlockButton:
	                NextState = unlocked;
	                printf("Flash lights once\n");
	                printf("Car is unlocked\n");
	            break;
	            case PushLockButton:
	                NextState = doublelocked;
	                printf("Flash lights twice\n");
	                printf("Flash lights twice\n");
	                printf("Car is double locked\n");
	            break;
	            default:
	                /* We should never end up here */
	                printf("Error\n");
	            break;
	        }
	    break;
	    default:
	        /* We should never end up here */
	    break;
	}

	CurrentState = NextState;
	/* printf("The current state is %d\n", CurrentState); */
	/* printf("The current state is %s\n", getStateName(CurrentState)); */

	return;
}