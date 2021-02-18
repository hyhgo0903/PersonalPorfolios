#pragma once
#include "gameNode.h"
#include "effect.h"


class itemManager;
class bulletManager;

#define TANKWIDTH 46
#define TANKHEIGHT 46
#define ITEMDURATION 600

enum state // 애니메이션 용으로 이용
{
	RIGHTIDLE, LEFTIDLE, RIGHTRUN, LEFTRUN, RIGHTATTACK, LEFTATTACK
};

enum type // 현재 탱크 종류
{
	CANNON,	MISSILE, MULTI, SUPER
};

struct tagTank
{	
	float x, y;			// _x, _y 중점
	float gravity;
	int probeY;			// Y 탐사축
	float angle;		// 쪼는 각도
	float jumpPower;
	bool isJump;
	RECT rc;			// 사각형
	state state;		// 플레이어 상태
	type type;			// 현재 탱크 종류
	
	float currentHP, maxHP, currentDelay, maxDelay, currentPower, maxPower;
	int frameX, aniCount; // count로 하면 ++했을때 count 60될때가 1초임을 명심하고 쓸 것
};

class playerManager : public gameNode
{
private:
	tagTank _tank;
	// _im->getStateSlot(0~2) 이건 탱크 보유시 보너스 스탯을 주기 위한 것으로 이 클래스 멤버변수마냥 자주 활용됨
	// 0이면 캐논(딜2배) 1이면 미사일(속도빠름 점프력빠름) 2이면 멀탱(공격딜감소) 보유중인지
	bool _usingItem[4];		// 4개 아이템에 대해 사용중인지 (더블파이어 딜감소, 파워업 딜2배, 쉴드 무적, 리페어 회복 순)
	int _itemDuration[4];	// 4개 상태에 대한 지속시간
	int _effectFrameX[4];	// 4개 이펙트에 대한 프레임 (지속시간을 이용해서 갱신됨)
	int _specialCount;		// 공격마다 오르고 2일때 특수무기 발사
	float _damageCoefficient; // 공격딜계수
	int _difficulty;		// 처음에 선택함 -> 0쉬움 1보통 2하드(딜계수 2배 1배 1/2배 체력 5배 1배 1/2배)
	int _selectedTank;		// 처음에 선택함 -> 0캐논 1미사일 2멀티

	bool _autoChanged; // 처음으로 슈탱 변신 가능하면 알아서 바꾸게.. 구차하긴 합니다.
	bool _isInvincible; // 무적인지 계속 판단해줌
	bool _isBlink;	// 맞으면 깜빡깜빡
	int _blinkCount; // 깜빡깜빡 지속시간

	bool _isGameOver; // 게임오버 조건에 켜짐

	BYTE _alphaValue;
	effect* _changeEffect;

	// 이하는 참조를 위한 것들
	itemManager* _im;
	bulletManager* _bm;

public:
	playerManager() {};
	~playerManager() {};

	virtual HRESULT init(int data);
	virtual void release();
	virtual void update();
	virtual void render();

	void keyInput();
	void tankMove();
	void stateChange();
	void interfaceRender();
	void delayReduce();

	void animationUpdate();
	void stateRender();
	void fire();

	void test();

	inline void dealDamage(float x) { _tank.currentHP -= x; }
	inline RECT getRect() { return _tank.rc; }
	inline bool getIsInvincible() {	return _isInvincible;}
	inline void setIsBlink() { _isBlink = true; }
	inline bool getIsGameOver() { return _isGameOver; }
	
	void setImMemoryAddressLink(itemManager* im) { _im = im; }
	void setBmMemoryAddressLink(bulletManager* bm) { _bm = bm; }
};

