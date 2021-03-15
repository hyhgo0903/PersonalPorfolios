#pragma once
#include "STATE.h"


//콤보 2-1(이동방향을 입력한채로 공격하는 콤보)입니다.
class player;

class combo21 : public STATE
{
private:
public:

    void EnterState();
    void updateState();
    void ExitState();

};

