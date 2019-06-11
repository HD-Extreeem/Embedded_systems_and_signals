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
    const State currentState = instance->state;
    instance->state = TransitionTable[currentState][PushUnlockEvent];
    printf("Flash lights once\n");
    return;
}

void PushLockButton(CentralLockPtr instance)
{
    const State currentState = instance->state;
    instance->state = TransitionTable[currentState][PushLockEvent];
    printf("Flash lights twice\n");
    printf("Flash lights twice\n");
    return;
}

void TwoMinuteTimeout(CentralLockPtr instance)
{
    const State currentState = instance->state;
    instance->state = TransitionTable[currentState][TwoMinuteEvent];
    return;
return;
}