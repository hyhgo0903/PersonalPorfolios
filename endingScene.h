#pragma once
#include "gameNode.h"
class endingScene :	public gameNode
{
	float _loopX;
	float _characterY;
	bool _yUp;
	int _dialog1[22] = {0,25,51,77,104,122,179,210,256,284,318,358,384,418,461,489,517,563,589,615,642,664};
	int _dialog2[27] = {0,22,48,86,125,150,178,215,253,279,304,330,360,406,438,484,512,536,564,585,611,643,687,713,751,790,818};
	int _dialog3[16] = {0,25,81,102,128,170,207,230,256,282,322,359,388,408,437,459};
	int _dialog1index;
	int _dialog2index;
	int _dialog3index;
	int _dialCount;

public:
	endingScene();
	~endingScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

