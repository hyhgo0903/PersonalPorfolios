#pragma once
#include "gameNode.h"
#include <vector>
#include "boss.h"
#include "minion.h"

class player;

enum createEnemy
{
	WAIT, END
};

class enemyManager :	public gameNode
{
private:
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;
	// (중요함) 벡터에는 에너미로써(부모클래스) 넣는거야
	// 따라서 subclass만의 고유한 함수를 만들어 이용하고 싶다면
	// [ex) (다른클래스에서) _getVEnemy()[i]->고유함수();]
	// 사용할 수 없다고 밑줄이 뜰거야. (벡터내의 enemy클래스라고 인식하고 있어)

	// 그럴떈 enemy.h에서 " 고유한 함수() = 0; " 요런식으로 껍데기 함수를 마련할수 있어.
	// 그러면 enemy에 그 함수가 있으니 에러는 안나지만 enemy의 함수가 아닌 상속클래스로 잘 연산하게 돼

	int _wave;
	createEnemy _create;
	player* _pl;
public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void createMinion(float x, float y);
	void createBoss(float x, float y);
	void enemyAi();

	vector<enemy*> getVEnemy() { return _vEnemy; }
	vector<enemy*>::iterator getViEnemy() { return _viEnemy; }

	void setLinkPlayer(player* player) { _pl = player; }
};

