
typedef enum
{
    unlocked,
    locked,
    doublelocked
} State;
#define NO_OF_STATES 3


typedef enum
{
    PushUnlockEvent,
    PushLockEvent,
    TwoMinuteEvent
} Event;
#define NO_OF_EVENTS 3

struct CentralLocking {
    /* Let a variable hold the state of our object. */
    State state;
    int lights;
};

const State TransitionTable[NO_OF_STATES][NO_OF_EVENTS] = {
	/* This is the full logic of the state machine */
    { unlocked, locked,  locked},
    { unlocked, locked,  doublelocked},
    { unlocked, doublelocked,  doublelocked}
};

typedef struct CentralLocking* CentralLockPtr;

void PushUnlockButton(CentralLockPtr instance);
void PushLockButton(CentralLockPtr instance);
void TwoMinuteTimeout(CentralLockPtr instance);

