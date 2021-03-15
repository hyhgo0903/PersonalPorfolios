#pragma once
#include "STATE.h"



class player;

class grab : public STATE
{
private:
    int count;
public:

	void EnterState();
	void updateState();
	void ExitState();

};

