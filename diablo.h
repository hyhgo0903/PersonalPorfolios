#pragma once
#include "unit.h"

enum ATTACK_PHASE
{
	SUMMON,
	EARTHQUAKE,
	FIREBALL
};

class diablo :
	public unit
{

private:

	ATTACK_PHASE _attackPhase;
	RECT _summonRc; // 소환범위 렉트
	//bool _isAttack; // 소환 했는지 안했는지 
	//int _isAttackCount; // 공격실행 카운트 입니다.

public:
	diablo();
	~diablo();

	virtual HRESULT init(BELONG belong, float x, float y);	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
	virtual void reRender();

	virtual void setState(STATE state);
//	virtual void getAttackPhase(ATTACK_PHASE _attckPhase, STATE state);
};
