#pragma once
#include "STATE.h"

class player;
class windmill : public STATE
{
private:
public:
    void EnterState();
    void updateState();
    void ExitState();
};
