#pragma once
#include "gameNode.h"
#include <vector>
#include "boss.h"
#include "minion.h"
#include "minion2.h"
#include "minion3.h"

class player;
class enemyManager :	public gameNode
{
private:
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;
	player* _pl;
	minion* _minion;
public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void createMinion(float x, float y);			//미니언1 생성(좌표값)
	void createMinion2(float x, float y);			//미니언2 생성(좌표값)
	void createMinion3(float x, float y);			//미니언3 생성(좌표값)
	void createBoss(float x, float y);				//보스 생성(좌표값)


	vector<enemy*> getVEnemy() { return _vEnemy; }
	vector<enemy*>::iterator getViEnemy() { return _viEnemy; }

	void setLinkPlayer(player* player) { _pl = player; }		//플레이어와 연결시켜주기 위한 함수
};

