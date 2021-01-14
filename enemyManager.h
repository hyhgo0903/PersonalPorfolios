#pragma once
#include "gameNode.h"
#include <vector>
#include "boss.h"
#include "minion.h"
#include "minion2.h"
#include "minion3.h"

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
	// (�߿���) ���Ϳ��� ���ʹ̷ν�(�θ�Ŭ����) �ִ°ž�
	// ���� subclass���� ������ �Լ��� ����� �̿��ϰ� �ʹٸ�
	// [ex) (�ٸ�Ŭ��������) _getVEnemy()[i]->�����Լ�();]
	// ����� �� ���ٰ� ������ ��ž�. (���ͳ��� enemyŬ������� �ν��ϰ� �־�)

	// �׷��� enemy.h���� " ������ �Լ�() = 0; " �䷱������ ������ �Լ��� �����Ҽ� �־�.
	// �׷��� enemy�� �� �Լ��� ������ ������ �ȳ����� enemy�� �Լ��� �ƴ� ���Ŭ������ �� �����ϰ� ��

	int _wave;
	createEnemy _create;
	player* _pl;
	minion* _minion;
public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void createMinion(float x, float y);
	void createMinion2(float x, float y);
	void createMinion3(float x, float y);
	void createBoss(float x, float y);


	vector<enemy*> getVEnemy() { return _vEnemy; }
	vector<enemy*>::iterator getViEnemy() { return _viEnemy; }

	void setLinkPlayer(player* player) { _pl = player; }
};
