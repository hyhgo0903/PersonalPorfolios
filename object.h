#pragma once
#include "gameNode.h"
#include <vector>

// 얘는 부모클래스

class object : public gameNode
{
protected:
	RECT _rc;
	int _id;
	float _x; float _y;
	bool _isFire;
	bool _isBossOn;

public:
	object();
	~object();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	RECT getRect() { return _rc; }
	int getId() { return _id; }
	bool getIsFire() { return _isFire; }
	bool getIsBossOn() { return _isBossOn; }
//	void setId(int x) { _id = x; } // 외부에서 x를 집어넣으면 _id의 값이 x로 바뀌게 된다.


};

