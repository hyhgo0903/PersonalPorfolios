#pragma once
#include "item.h"
class baseball :	public item
{
private:
	RECT _rcg;
	float _xg, _yg;
	float _gravity;

	RECT _shadow;
	int _distance;
	float _time;
	BOOL _strach;

	float _angle;

public:
	baseball();
	~baseball();

	//기본 함수.

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
	//상속받아 오버라이드하는 함수.

	virtual void setHold(bool holding, float x, float y);
	virtual void attackMove(bool direction);

	//클래스 고유 함수

	void drop();
};

