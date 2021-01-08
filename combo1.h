#pragma once
#include "STATE.h"

class player;

class combo1 : public STATE
{
public:

	void EnterState();
	void updateState();
	void ExitState();

};

