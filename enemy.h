#pragma once
#include "gameNode.h"

enum enemyState { E_IDLE, E_WALK, E_ATK, E_DEAD, E_HIT, E_GRAB, E_FLYING };
enum bossState { B_IDLE, B_WALK };

class enemy : public gameNode
{
protected:
	RECT _rc;
	float _x; float _y; // 중점. RectMakeCenter를 이용하기로 함
	float _currentHP; float _maxHP;

	int _count; int _index;
	float _pX; float _pY; // 플레이어 중점
	bool _left; // 왼쪽을 보고 있으면 1, 오른쪽이면 0. 왜 인트냐면 _frameIndexY처럼 쓸것이기 때문)
	int _attackCount;		// 공격쿨타임
	int _hitCount;			// 피격모션 유지시간
	int _grabCount;			// 그랩모션 유지시간
	int _flyingCount;		// 플라잉모션 유지시간
	bool _flying; // 날고있으면 1, 지상이면 0

	enemyState _state;
	bossState _bState;
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
