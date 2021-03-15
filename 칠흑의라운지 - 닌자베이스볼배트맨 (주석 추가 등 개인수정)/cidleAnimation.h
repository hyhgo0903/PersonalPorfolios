#pragma once
#include "STATE.h"
class player;
class cidleAnimation :
	public STATE
{
private:
public:
	void EnterState();
	void updateState();
	void ExitState();
};
