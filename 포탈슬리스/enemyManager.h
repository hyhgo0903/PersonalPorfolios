#pragma once
#include "gameNode.h"
#include <vector>
#include "groundEnemy.h"
#include "flyingEnemy.h"
#include "itemManager.h" // 에너미(벡터) 지우면서 아이템 드랍함수 호출하기 위해
#include "playerManager.h" // 플레이어 위치 갖고와서 그에따른 액션 부여하기 위해(지상유닛)

class bulletManager;

#define ENEMYTABLE 10 // 적 등장 몇번할건지?

class enemyManager : public gameNode
{
private:
	vector<groundEnemy*> _vGEnemy;
	vector<groundEnemy*>::iterator _viGEnemy;
	vector<flyingEnemy*> _vFEnemy;
	vector<flyingEnemy*>::iterator _viFEnemy;

	bulletManager* _bm;
	itemManager* _im;
	playerManager* _pm;
	bool _enemyTable[ENEMYTABLE];
	bool _isVictory; // 보스판정을 여기서 하는게 쉬우므로..
	// 보스 피가 0이하가 되면 이게 켜지고 플레이씬에서 씬전환

public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void enemyUpdate();
	void createEnemy();
	void enemyFire();

	vector<groundEnemy*> getVGEnemy() { return _vGEnemy; }
	vector<groundEnemy*>::iterator getViGEnemy() { return _viGEnemy; }
	vector<flyingEnemy*> getVFEnemy() { return _vFEnemy; }
	vector<flyingEnemy*>::iterator getViFEnemy() { return _viFEnemy; }
	bool getIsVictory() { return _isVictory; }
	
	void test();	

	void setBmMemoryAddressLink(bulletManager* bm) { _bm = bm; }
	void setImMemoryAddressLink(itemManager* im) { _im = im; }
	void setPmMemoryAddressLink(playerManager* pm) { _pm = pm; }
};

