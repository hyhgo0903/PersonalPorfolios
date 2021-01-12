#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	_pl = new player;
	//몬스터 웨이브 초기 설정
	_wave = 1;
	//몬스터 생성유무 체크(무한생성 방지)
	_create = WAIT;
	
	return S_OK;
}

void enemyManager::createMinion(float x, float y)
{
	minion* vminion;
	vminion = new minion;
	vminion->init(x, y);
	_vEnemy.push_back(vminion);
}

void enemyManager::createMinion2(float x, float y)
{
	minion2* vminion2;
	vminion2 = new minion2;
	vminion2->init(x, y);
	_vEnemy.push_back(vminion2);
}

void enemyManager::createMinion3(float x, float y)
{
	minion3* vminion3;
	vminion3 = new minion3;
	vminion3->init(x, y);
	_vEnemy.push_back(vminion3);
}

void enemyManager::createBoss(float x, float y)
{
	boss* vboss;
	vboss = new boss;
	vboss->init(x, y);
	_vEnemy.push_back(vboss);
}

void enemyManager::release()
{
	_vEnemy.clear();
}

void enemyManager::update()
{
	
	//만들어진 모든 에너미들의 업데이트 연산
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->update();
		_vEnemy[i]->setPlayerPt(_pl->getGroundX(), _pl->getGroundY());
	}

	//몬스터가 만들어졌는지 유무를 이넘으로 체크하여 몬스터 무한 생성 방지
	if (_wave == 1 && _create == WAIT)
	{
		//첫 몬스터 웨이브(볼 몬스터 3마리)
		createMinion(900, 600);
		createMinion2(700, 500);
		createMinion3(700, 600);
		createBoss(1600, 400);
		_create = END;
	}
}

void enemyManager::render()
{ // 적들은 제트오더에서 한번에 그릴거임
}
