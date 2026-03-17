#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

enum SystemState
{
    INIT,
    SCAN,
    MOVE_FORWARD,
    STOP,
    INDEX_TRAY,
    DRILL,
    RETRACT,
    DROP_SEED,
    NEXT_POSITION
};

extern volatile SystemState currentState;

#endif