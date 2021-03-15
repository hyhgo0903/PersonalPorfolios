#pragma once
#include "STATE.h"

class player;

class dead : public STATE
{
private:
	int count;
public:

	void EnterState();
	void updateState();
	void ExitState();

};

