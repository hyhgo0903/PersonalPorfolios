#pragma once
#include "object.h"

class chair :public object
{
private:

	image* _img;
	

public:
	chair();
	~chair();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void shadowRender(RECT rc);

	image* getChairImg() { return _img; }


};

