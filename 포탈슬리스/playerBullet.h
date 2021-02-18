#pragma once
#include "bullets.h"

class playerBullet : public bullets
{
	float _angle;
	int _hits;
	bool _chase; // 쫓아가고 있는지
	RECT _targetRc; // 타겟팅하면 이펙트를 만들어 줘야 하니깐..

public:
	playerBullet() {};
	~playerBullet() {};

	virtual HRESULT init(int ID, float x, float y, float angle
		, float power, float damageCoefficient);
	virtual void release();
	virtual void update();
	virtual void render();
	int& getHits() { return _hits; }
	bool& getChase() { return _chase; }
	void setTargetRc(RECT rc) { _targetRc = rc; }
	void setXSpd(float xSpd) { _xSpd = xSpd; }
	void setYSpd(float ySpd) { _ySpd = ySpd; }

};

