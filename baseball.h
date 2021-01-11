#pragma once
#include "item.h"
class baseball :	public item
{
private:
	BOOL _strach;

public:
	baseball();
	~baseball();

	//기본 함수.

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(float x, float y, float bottom);
	virtual void release();
	virtual void update();
	virtual void render();
	//상속받아 오버라이드하는 함수.

	virtual void setHold(float x, float y);
	virtual void setHold(float x, float y, float bottom);
	virtual void attackMove(bool direction);

	//클래스 고유 함수

	void drop();
};

