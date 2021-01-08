#pragma once
#include "item.h"
class bat :	public item
{
private:

public:
	bat();
	~bat();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
};

