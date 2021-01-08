#pragma once
#include "gameNode.h"

enum enemyState
{
	E_IDLE_L, E_IDLE_R,
	E_WALK_L, E_WALK_R,
	E_ATK_L, E_ATK_R,
	E_DEAD_L, E_DEAD_R
};

class enemy : public gameNode
{
protected:
	RECT _rc;
	float _x; float _y; // 중점. RectMakeCenter를 이용하기로 함
	float _currentHP; float _maxHP;

	int _count; int _index;
	enemyState _state;
	float _pX; float _pY; // 플레이어 중점

public:
	enemy();
	~enemy();

	virtual HRESULT init(float x, float y)=0;
	// 선언시 좌표를 입력받지만 매개변수를 추가할거면 enemy.h, 다른 상속클래스들과 통일하여 바꿔주면 됨
	virtual void release();
	virtual void update();
	virtual void render();

	// 공통적으로 쓰이는 함수는 다 여기다 하면 돼
	RECT& getRect() { return _rc; }
	void setPlayerPt(float x, float y) { _pX = x; _pY = y; }
};
