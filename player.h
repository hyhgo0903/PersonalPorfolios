#pragma once
#include "gameNode.h"
#include "attack.h"


class enemyManager;

class STATE; // 상호참조시 전방선언 같은거

enum State {
	IDLE,
	JUMP,
	WALK,
	RUN,
	COMBO1
};

class player :
	public gameNode
{
private:
	float _flyX; float _flyY;		// 점프하면 유체이탈하듯이 위로
	RECT _flyRc;
	float _groundX; float _groundY; // 땅에 붙는RC
	RECT _groundRc;
	bool _left;						// 왼쪽을 보고 있는지
	State _enumState;
	STATE* _statePattern;
	char _str[128];
	float _currentHP;
	float _maxHP;
	attack* _attack;

	// ############ 커맨드 입력 관련 변수(대시, 특수기) #############
	int _directionChanged;		// 좌우가 몇번 바뀌었는지 카운트(커맨드)
	int _directionChangeCount;	// 카운트체크해서 내림
	int _dirMemory;				// 방향 기억(대쉬용)
	int _dirMemoryCount;		// 카운트체크해서 내림

	enemyManager* _em;

public:
	player();
	~player();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void minusDirectionChanged();

	void playerRender();
	// 플레이어 변수에따라 여러 렌더를 하겠지만
	// 여기엔 z오더 서순에 맞춰야할 플레이어 캐릭터'만' 그려주는 것
	// 그래서 렌더에서 분리한 것임

	// 상태패턴 하면 게터 미친듯이 많아지는듯함. 창훈이것도 봤었는데 엄청 많더라
	// 여기서 직접 연산하는것보다 상태객체에서 연산이 되기 때문에..
	void setState(State state);
	RECT getGroundRc() { return _groundRc; }
	RECT getFlyRc() { return _flyRc; }
	float& getGroundX() { return _groundX; }float& getGroundY() { return _groundY; }
	float& getFlyX() { return _flyX; }		float& getFlyY() { return _flyY; }
	bool& getLeft() { return _left; }
	State& getEnumState() { return _enumState; }
	void plusDirectionChanged() { ++_directionChanged; }
	int& getDirMemory() {return _dirMemory;}
	void setLinkEnemy(enemyManager* em) { _em = em; }
	attack* getAttack() { return _attack; }
};

