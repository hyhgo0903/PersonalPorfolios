#pragma once
#include "object.h"

class trashCan :public object
{
private:

	image* _img;
	RECT _trashRect;

public:
	trashCan();
	~trashCan();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	image* getTrashCanImg() { return _img; }
	RECT getTrashCanRect() { return _trashRect; }
};

