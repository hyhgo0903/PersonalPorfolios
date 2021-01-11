#pragma once
#include "item.h"
class bomb :public item
{
private:
	animation* _ani;
	int _index;
	float _indexTime;

public:
	virtual HRESULT init(float x, float y);
	virtual HRESULT init(float x, float y, float bottom);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void attackMove(bool direction);
	virtual void setHold(float x, float y);
	virtual void setHold(float x, float y, float bottom);

	void drop();
	void drop(float g);
	void framing();
	void framing(int start, int end);
	void reverseFraming();
	void reverseFraming(int start, int end);
};

