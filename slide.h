#pragma once
#include "STATE.h"
class player;
class slide : public STATE
{
private:
public:
    void EnterState();
    void updateState();
    void ExitState();
};

