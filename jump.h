#pragma once
#include "STATE.h"
class player;
class Jump :
    public STATE
{
private:
	float _jumpPower;
public:
	void EnterState(); // 들어갔을떄 이닛의역할
	void updateState(); // 계속 업데이트
	void ExitState(); // 상태해제
};

