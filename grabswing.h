#pragma once
#include "STATE.h"



class player;

class grabswing : public STATE
{
private:
public:

	void EnterState();
	void updateState();
	void ExitState();

};

