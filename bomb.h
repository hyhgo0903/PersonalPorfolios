#pragma once
#include "item.h"
class bomb :
	public item
{
private:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void attackMove(bool direction);
	virtual void setHold(bool holding, float x, float y);
};

