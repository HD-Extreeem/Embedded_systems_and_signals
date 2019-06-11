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
    struct CentralLocking SM;   /* The variable containing the memory area for the state machine */
    CentralLockPtr instance;    /* A pointer to a state machine of this type */

    instance = &SM;             /* Pointing to the state machine used */
    instance->state = unlocked; /* Initial state */

    while(1)
    {
        inp = getchar();
    
        if (inp == 'l')
        {
            PushLockButton(instance); /* run state machine */
        }
        else if (inp == 'u')
        {
            PushUnlockButton(instance); /* run state machine */
        }
        else if (inp == '2')
        {
            TwoMinuteTimeout(instance); /* run state machine */
        }
        else
        {
            /* Do nothing */
        }
    }
}







