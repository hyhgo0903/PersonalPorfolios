#pragma once
#include "item.h"
class pizza:public item
{
private:
	
public:

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(float x, float y, float bottom);
	virtual void release();
	virtual void update();
	virtual void render();

	void drop();

	virtual void setHold();
};

