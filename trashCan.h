#pragma once
#include "object.h"

class trashCan :public object
{
private:

	image* _TrashCanImg;

public:
	trashCan();
	~trashCan();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
};

