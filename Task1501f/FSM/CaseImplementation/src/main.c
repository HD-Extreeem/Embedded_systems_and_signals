//
//  main.c
//  C examples
//
//  Created by Ulrik on 2014-03-05.
//
//

#define delay_length 400000
#include <stdio.h>
#include "LockStateMachine.h"

int main(void)
{
	char inp;
	Event KeyReturn = PushUnlockButton;

	while(1)
	{
	    inp = getchar();
    
	    if (inp == 'l')
	    {
	        KeyReturn = PushLockButton;
	        LockStateMachine(KeyReturn); /* run state machine */
	    }
	    else if (inp == 'u')
	    {
	        KeyReturn = PushUnlockButton;
	        LockStateMachine(KeyReturn); /* run state machine */
	    }
	    else if (inp == 't')
	    {
	        KeyReturn = TwoMinuteTimeout;
	        LockStateMachine(KeyReturn); /* run state machine */
	    }
	    else
	    {
	        /* Do nothing */
	    }
	}
}







