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

//각 상태에선 일단 STATE 상속을받는건 당연한데
//플레이어 클래스랑 상호참조였던가 여튼 저위에 전방선언을해줘야함