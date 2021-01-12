#pragma once
#include "gameNode.h"
#include <vector>



class player;

// 콤보공격에 쓸 공격 벡터입니다.
struct tagAttack
{
	RECT rc;				//공격에 사용될 렉트
	float x, y;				//중점 좌표
	float attackX, attackY;	//공격 위치
	bool isAttack;			//공격 여부
};


class attack : public gameNode
{
private:
	vector<tagAttack> _vAttack;
	vector<tagAttack>::iterator _viAttack;

	int _count;
	int _attackMax; // 공격 렉트 한계치. (없어도 될 거 같은데 넣었습니다)
	player* _pl;

	RECT _attackRect; // 현정_콜리전위해 추가한것 2

public:

	
	attack() {};
	~attack() {};

	HRESULT init(int attackMax, int count);
	void release();
	void update(int count);
	void render();

	void Attack(float x, float y);
	RECT getAttackRect() { return _attackRect; } // 현정_콜리전위해 추가한것 3. 끝.
	void removeAttack(int arrNum);

	vector<tagAttack> getVAttack()				{ return _vAttack; }
	vector<tagAttack>::iterator getViAttack() { return _viAttack; }
};