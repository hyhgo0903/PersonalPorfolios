#pragma once
#include "enemy.h"
class boss :public enemy
{
	
public:
	boss();
	~boss();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
	void move();
};

