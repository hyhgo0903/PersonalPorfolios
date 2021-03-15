#pragma once
#include "gameNode.h"
#include "attack.h"

class attack;

class enemyManager;

class STATE; // 상호참조시 전방선언

enum State {
	IDLE,
	CIDLEANIMATION,
	JUMP,
	WALK,
	RUN,
    SLIDE,
    TACKLE,
    JUMPATTACK,
    HIT,
	COMBO1,
	COMBO11,
	COMBO12,
	COMBO13,
    COMBO21,
    COMBO22,
    COMBO23,
	GRAB,
	GRABSWING,
    WINDMILL,
	DEAD
};

class player :
	public gameNode
{
private:
	image* playerImage; //플레이어 이미지용
	float _flyX; float _flyY;		// 점프하면 유체이탈하듯이 위로
	RECT _flyRc;
	float _groundX; float _groundY; // 땅에 붙는RC
	RECT _groundRc;
	RECT _shadow;					//그림자 rc
	bool _left;						// 왼쪽을 보고 있는지
	State _enumState;
	STATE* _statePattern;
	char _str[128];
	float _currentHP;
	float _maxHP;
	attack* _attack;
	int _count, _index; //프레임 이미지 재생용 카운트, 인덱스.
    float _jumpPower; // 점프 파워
    bool _isGrab;
	int _flyCount; // 적당한 때에 날아가기 위한 카운트


	// ############ 커맨드 입력 관련 변수(대시, 특수기) #############
	int _directionChanged;		// 좌우가 몇번 바뀌었는지 카운트(커맨드)
	int _directionChangeCount;	// 카운트체크해서 내림
	int _dirMemory;				// 방향 기억(대쉬용)
	int _dirMemoryCount;		// 카운트체크해서 내림
	int _shadowWidth;

	enemyManager* _em;

public:
	player() {};
	~player() {};
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void minusDirectionChanged();

	void playerRender();
	void reRender();

	//세터와 게터들입니다
	void setState(State state);
	void stateUpdate();
	void stateRender();
	RECT getGroundRc() { return _groundRc; }
	RECT getFlyRc() { return _flyRc; }
    RECT getShadow() { return _shadow; }
	float& getGroundX() { return _groundX; }float& getGroundY() { return _groundY; }
	float& getFlyX() { return _flyX; }		float& getFlyY() { return _flyY; }
	bool& getLeft() { return _left; }
	State& getEnumState() { return _enumState; }
	void plusDirectionChanged() { ++_directionChanged; }
    int& getDirectionChanged() {return _directionChanged; }
	int& getDirMemory() {return _dirMemory;}
	void setLinkEnemy(enemyManager* em) { _em = em; }
	attack* getAttack() { return _attack; }
	int& getIndex() { return _index; }
    float& getJumpPower() { return _jumpPower; }
    bool& getIsGrab() { return _isGrab; }
    float& getPlHP() { return _currentHP; }
    void getDamage(int x) { _currentHP -= x; }
	int& getFlyCount() { return _flyCount; }

};

