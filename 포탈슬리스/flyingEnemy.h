#pragma once
#include "enemy.h"
class flyingEnemy : public enemy
{
private:
	int _phase; // 보스나 대형우주선은 페이즈가 존재한다.

	float _destX, _destY; // 도착목적지 (비행은 위에서 오고 지상은 오른쪽에서 옴)
	int _destinationCount;	// 도착지 바꾸는 카운트

public:
	flyingEnemy() {};
	~flyingEnemy() {};

	virtual HRESULT init(int ID, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void frameXUpdate();
	void fireReady();
	void flyingMove();

	inline int& getPhase() { return _phase; }
};

