#pragma once
#include "gameNode.h"

enum enemyState { E_IDLE, E_WALK, E_ATK, E_DEAD, E_HIT, E_GRAB, E_FLYING, E_WALK2, E_SHAKE, E_FLYING2 };

class enemy : public gameNode
{
protected:
	RECT _rc;							//enemy의 몸통을 담당하는 렉트
	RECT _attackRc;						//enemy의 공격을 담당하는 렉트
	RECT _shadow;						//enemy의 그림자를 담당하는 렉트

	float _x; float _y;					//enemy의 중점
	float _currentHP; float _maxHP;		//enemy의 현재 체력과 최대 체력

	int _count; int _index; int _index2;
	float _pX; float _pY;				//player의 중점 좌표를 받아오기위해 필요한 변수
	bool _left;							//enemy의 좌우를 판단하는 것 false == right, true == left
	bool _flying;						//enemy가 E_FLYING 상태에 돌입했을때 벽에 충돌하기전까지 날고있는 상태를 체크해줌
	bool _atkArea;						//enemy가 공격범위 안에 진입했는지 체크해줌
	bool _isDead;						//enemy가 특정조건을 달성하여 죽어도되는 상태가 되었는지 체크해줌
	bool _flyDown;						//enemy가 E_FLYING2 상태에서 공중에 일정거리이상 상승한뒤 떨어지고있는지 체크해줌

	int _attackCount;					//enemy의 공격이 이루어지기 전까지의 시간
	int _hitCount;						//enemy가 E_HIT으로 변경된 후 상태 유지시간 
	int _grabCount;						//enemy가 E_GRAB으로 변경된 후 상태 유지시간
	int _plAtkNum;						//enemy1가 피격시 랜덤모션을 렌더할 수 있게 랜덤값을 담아주는 변수
	int _randomNum;						//enemy가 player를 추적할때 y축 좌표에 변동을 주어 enemy가 겹치지않게끔 해주는 변수
	int _deadCount;						//enemy2, 3는 죽는 모션이 한개이기때문에 죽는모션에서 일정시간 유지시킬 필요가있으므로 유지시키는 시간을 입력받는 변수
	int _alpha;							//enemy의 이미지 렌더시 알파 렌더로 출력하기 위해 필요한 변수
	int _phase;							//boss의 페이즈를 구현하기 위해 필요한 변수

	enemyState _state;					//enemy의 특정상태를 주기위해 필요한 상태가 되어주는 변수
public:
	enemy();
	~enemy();

	virtual HRESULT init(float x, float y) = 0;
	virtual void release();
	virtual void update();
	virtual void render();
	void fillColorEllipse(int R, int G, int B, RECT rc);
	void setPlayerPt(float x, float y) { _pX = x; _pY = y; }
	void getDamage(int x) { _currentHP -= x; }
	void setState(enemyState state);
	void setAtkNum() { _plAtkNum = RND->getFromIntTo(1, 3); }
	void setAlpha() { _alpha = 255; }

	RECT& getRect() { return _rc; }
	RECT& getShadow() { return _shadow; }
	RECT& getAtkRc() { return _attackRc; }

	enemyState& getState() { return _state; }

	int getPhase() { return _phase; }
	float& getHp() { return _currentHP; }
	float getY() { return _y; }
	bool& getLeft() { return _left; }
	bool& getIsDead() { return _isDead; }

};
