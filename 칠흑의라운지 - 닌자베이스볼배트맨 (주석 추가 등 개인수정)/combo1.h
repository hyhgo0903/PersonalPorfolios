#pragma once
#include "STATE.h"

//이후 콤보 1-1 혹은 2-1로 분화하는 아주 매우 많이 기본공격입니다.
class player;

class combo1 : public STATE
{
private:
public:

	void EnterState();
	void updateState();
	void ExitState();

};

