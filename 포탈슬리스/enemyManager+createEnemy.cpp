#include "stdafx.h"
#include "enemyManager.h"
#include "bulletManager.h"
// 에너미 생성 함수를 따로 cpp 만들어서 관리
// ##############################################################
// ID표				0			1				2
// groundEnemy : 루돌프포로	산타에리
// flyingEnemy : 외계인		큰UFO(화면락)	솔데로카(화면락)
// ##############################################################

void enemyManager::createEnemy()
{
	if (GETCAM > 3700 && !_enemyTable[0])
	{ // 중간보스
		_enemyTable[0] = true; // 한번만 나오도록 불값을 켜줌
		flyingEnemy* fEnemy;
		fEnemy = new flyingEnemy;
		fEnemy->init(1, 3950, -121);
		_vFEnemy.push_back(fEnemy);
		fEnemy = new flyingEnemy;
		fEnemy->init(1, 4250, -121);
		_vFEnemy.push_back(fEnemy);
	}
	if (GETCAM > MAPSIZEX-WINSIZEX-5 && !_enemyTable[1])
	{ // 보스
		_enemyTable[1] = true;
		flyingEnemy* fEnemy;
		fEnemy = new flyingEnemy;
		fEnemy->init(2, GETCAM + 400, -121);
		_vFEnemy.push_back(fEnemy);
	}
	if (GETCAM > 500 && !_enemyTable[2])
	{ // 산타3
		_enemyTable[2] = true;
		groundEnemy* gEnemy;
		gEnemy = new groundEnemy;
		gEnemy->init(1, 1330, 200);
		_vGEnemy.push_back(gEnemy);
		gEnemy = new groundEnemy;
		gEnemy->init(1, 1360, 200);
		_vGEnemy.push_back(gEnemy);
		gEnemy = new groundEnemy;
		gEnemy->init(1, 1390, 200);
		_vGEnemy.push_back(gEnemy);
	}
	if (GETCAM > 1100 && !_enemyTable[3])
	{ // 루돌2산타1
		_enemyTable[3] = true;
		groundEnemy* gEnemy;
		gEnemy = new groundEnemy;
		gEnemy->init(0, GETCAM + WINSIZEX + 30, 300);
		_vGEnemy.push_back(gEnemy);
		gEnemy = new groundEnemy;
		gEnemy->init(0, GETCAM + WINSIZEX + 60, 300);
		_vGEnemy.push_back(gEnemy);
		gEnemy = new groundEnemy;
		gEnemy->init(1, 1580, -100);
		_vGEnemy.push_back(gEnemy);
	}
	if (GETCAM > 1900 && !_enemyTable[4])
	{ // 루돌2산타1외계인1
		_enemyTable[4] = true;
		groundEnemy* gEnemy;
		gEnemy = new groundEnemy;
		gEnemy->init(0, 2730, 300);
		_vGEnemy.push_back(gEnemy);
		gEnemy = new groundEnemy;
		gEnemy->init(0, 1870, 300);
		_vGEnemy.push_back(gEnemy);
		gEnemy = new groundEnemy;
		gEnemy->init(1, 2462, -100);
		_vGEnemy.push_back(gEnemy);
		flyingEnemy* fEnemy;
		fEnemy = new flyingEnemy;
		fEnemy->init(0, 2300, -100);
		_vFEnemy.push_back(fEnemy);
	}

	if (GETCAM > 3200 && !_enemyTable[5])
	{ // 외계인만 5
		_enemyTable[5] = true;
		flyingEnemy* fEnemy;
		for (int i = 0; i < 5; i++)
		{
			fEnemy = new flyingEnemy;
			fEnemy->init(0, 3300 + rand()% 500, -100);
			_vFEnemy.push_back(fEnemy);
		}
	}

	if (GETCAM > 2600 && !_enemyTable[6])
	{ // 루돌2산타2외계인2
		_enemyTable[6] = true;
		groundEnemy* gEnemy;
		gEnemy = new groundEnemy;
		gEnemy->init(1, 3420, 100);
		_vGEnemy.push_back(gEnemy);
		gEnemy = new groundEnemy;
		gEnemy->init(1, 3420, 177);
		_vGEnemy.push_back(gEnemy);
		gEnemy = new groundEnemy;
		gEnemy->init(0, 3420, 300);
		_vGEnemy.push_back(gEnemy);
		gEnemy = new groundEnemy;
		gEnemy->init(0, 2580, 300);
		_vGEnemy.push_back(gEnemy);
		flyingEnemy* fEnemy;
		fEnemy = new flyingEnemy;
		fEnemy->init(0, 2900, -100);
		_vFEnemy.push_back(fEnemy);
		fEnemy = new flyingEnemy;
		fEnemy->init(0, 3200, -200);
		_vFEnemy.push_back(fEnemy);
	}
}