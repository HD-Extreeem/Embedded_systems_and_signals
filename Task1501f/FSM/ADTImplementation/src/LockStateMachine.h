typedef enum {
    unlocked,
    locked,
    doublelocked
} State;
    
struct CentralLocking {
    /* Let a variable hold the state of our object. */
    State state;
    int lights;
};

typedef struct CentralLocking * CentralLockPtr;

void PushUnlockButton(CentralLockPtr instance);
void PushLockButton(CentralLockPtr instance);
void TwoMinutetimeout(CentralLockPtr instance);

