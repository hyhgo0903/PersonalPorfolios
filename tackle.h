#pragma once
#include "STATE.h"
class player;
class tackle : public STATE
{
private:
public:
    void EnterState();
    void updateState();
    void ExitState();
};

