#pragma once
#include "STATE.h"



class player;

class grab : public STATE
{
private:
public:

	void EnterState();
	void updateState();
	void ExitState();

};

