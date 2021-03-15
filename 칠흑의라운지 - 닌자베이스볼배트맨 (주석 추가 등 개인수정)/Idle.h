#pragma once
#include "STATE.h"
class player;
class Idle :
    public STATE
{
private:
	int count;
public:
    void EnterState();
    void updateState();
    void ExitState();
};

//각 상태에서 STATE 클래스를 상속받고 player 클래스와 상호참조 하기 위해 전방선언 했습니다