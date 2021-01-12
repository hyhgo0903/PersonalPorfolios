#pragma once
#include "enemy.h"
class boss :public enemy
{
private:
	int _phase; int _phaseCount;
	int _destX; // 목적지
	int _destY; // 목적지. 보스페이즈2일땐 그림자위치로도 씀
	bool _jumping; // 점프
	int _rideCount;
	int _shakeCount; // 한 5번정도만 떨고 일어남
public:
	boss();
	~boss();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
	void bossState();			//보스의 상태값 관리
	void phase1();
	void phase2();
};

