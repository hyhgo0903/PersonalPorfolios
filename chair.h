#pragma once
#include "object.h"
class chair :public object
{
private:

	image* _img;
	RECT _chairRect;

public:
	chair();
	~chair();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();


	image* getChairImg() { return _img; }
	RECT getChairRect() { return _chairRect; }

};

