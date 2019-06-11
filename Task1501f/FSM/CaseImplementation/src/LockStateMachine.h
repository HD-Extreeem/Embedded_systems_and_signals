typedef enum
{
    unlocked,
    locked,
    doublelocked
} State;

typedef enum
{
    PushUnlockButton,
    PushLockButton,
    TwoMinuteTimeout
} Event;

void LockStateMachine(Event);