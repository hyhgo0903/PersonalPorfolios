#pragma once
#include "gameNode.h"

enum enemyState { E_IDLE, E_WALK, E_ATK, E_DEAD, E_HIT, E_GRAB, E_FLYING, E_WALK2, E_SHAKE, E_FLYING2 };

class enemy : public gameNode
{
protected:
	RECT _rc;
	RECT _attackRc;
	float _x; float _y; // 중점. RectMakeCenter를 이용하기로 함
	float _currentHP; float _maxHP;

	int _count; int _index; int _index2;
	float _pX; float _pY; // 플레이어 중점
	bool _left; // 왼쪽을 보고 있으면 1, 오른쪽이면 0. 왜 인트냐면 _frameIndexY처럼 쓸것이기 때문)
	int _attackCount;			// 공격쿨타임
	int _hitCount;				// 피격모션 유지시간
	int _grabCount;				// 그랩모션 유지시간
	bool _flying;					 // 날고있으면 1, 지상이면 0
	int _plAtkNum;					//테스트용 플레이어 공격상태
	int _keyManagerNum;				//키매니저 몬스터 선택상태
	bool _atkArea;					//몬스터 1 공격범위 안에서 움직일수 있게 체크해줌
	int _randomNum;					//몬스터 y좌표 랜덤값 지정 (겹치지않게하기위함)
	bool _isDead;					//몬스터가 죽었는지 살았는지 여부 체크
	int _deadCount;					//죽는 모션이 1개인 경우 죽고 난 다음 일정시간을 유지하기위해 만듬
	int _flyingCount;				//체공시간을 체크하려고 만듬
	bool _flyDown;					
	int _alpha;

	RECT _shadow;

	enemyState _state;
	enemyState _bState;
public:
	enemy();
	~enemy();

	virtual HRESULT init(float x, float y)=0;
	// 선언시 좌표를 입력받지만 매개변수를 추가할거면 enemy.h, 다른 상속클래스들과 통일하여 바꿔주면 됨
	virtual void release();
	virtual void update();
	virtual void render();
	void fillColorEllipse(int R, int G, int B, RECT rc);

	// 공통적으로 쓰이는 함수는 다 여기다 하면 돼
	RECT& getRect() { return _rc; }
	RECT& getShadow() { return _shadow; }
	RECT& getAtkRc() { return _attackRc; }
	float& getHp() { return _currentHP; }
	bool& getIsDead() { return _isDead; }
	enemyState& getState() { return _state; }
	void setPlayerPt(float x, float y) { _pX = x; _pY = y; }
	void getDamage(int x) { _currentHP -= x; }
	void setState(enemyState state);
	float getY() { return _y; }
	void setAtkNum() { _plAtkNum = RND->getFromIntTo(1, 3); }
	bool& getLeft() { return _left; }
};
