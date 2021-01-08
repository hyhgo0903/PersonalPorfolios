#pragma once
#include "gameNode.h"
class endingScene :	public gameNode
{


public:
	endingScene();
	~endingScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

