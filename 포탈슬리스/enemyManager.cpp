#include "stdafx.h"
#include "enemyManager.h"
#include "bulletManager.h"


HRESULT enemyManager::init()
{
	_isVictory = false;
	for (int i = 0; i < ENEMYTABLE; ++i)
	{
		_enemyTable[i] = false;
	}
	return S_OK;
}

void enemyManager::release()
{
	_vGEnemy.clear();	_vFEnemy.clear();
}

void enemyManager::update()
{
	createEnemy();
	enemyUpdate();
	enemyFire();
	test();
}

void enemyManager::render()
{
	for (int i = 0; i < _vGEnemy.size(); ++i)
	{
		_vGEnemy[i]->render();
	}
	for (int i = 0; i < _vFEnemy.size(); ++i)
	{
		_vFEnemy[i]->render();
	}
}

void enemyManager::enemyUpdate()
{
	CAMERAMANAGER->cameraLockOff();
	for (int i = 0; i < _vGEnemy.size(); ++i)
	{
		_vGEnemy[i]->update();
		CAMERAMANAGER->cameraLockOn(); // 적이 있는거면 카메라잠금
		_vGEnemy[i]->setPlayerX((_pm->getRect().left + _pm->getRect().right) / 2); // 땅에 있는 놈이면 플레이어 위치를 입력받는다
	}
	for (int i = 0; i < _vGEnemy.size(); ++i)
	{
		if (!_vGEnemy[i]->getAppear())
		{
			RECT temp = _vGEnemy[i]->getRect();
			if (rand() % 3 == 0) _im->dropStateItem((temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);
			SAFE_RELEASE(_vGEnemy[i]);
			SAFE_DELETE(_vGEnemy[i]);
			_vGEnemy.erase(_vGEnemy.begin() + i); // 33%로 아이템 떨구고 벡터 삭제
			break;
		}
	}
	for (int i = 0; i < _vFEnemy.size(); ++i)
	{
		_vFEnemy[i]->update();
		CAMERAMANAGER->cameraLockOn(); // 적이 있는거면 카메라잠금
	}
	for (int i = 0; i < _vFEnemy.size(); ++i)
	{
		if (!_vFEnemy[i]->getAppear() && _vFEnemy[i]->getID() != 2)
		{
			RECT temp = _vFEnemy[i]->getRect();
			if (rand() % 3 == 0) _im->dropStateItem((temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);
			SAFE_RELEASE(_vFEnemy[i]);
			SAFE_DELETE(_vFEnemy[i]);
			_vFEnemy.erase(_vFEnemy.begin() + i); // 33%로 아이템 떨구고 벡터 삭제
			break;
		}
		else if (!_vFEnemy[i]->getAppear() && _vFEnemy[i]->getID() == 2) _isVictory = true;
	} // 보스를 잡았으면 빅토리
}

void enemyManager::enemyFire()
{
	{
		for (int i = 0; i < _vGEnemy.size(); ++i)
		{
			if (_vGEnemy[i]->getFireReady() == 0) continue;
			_vGEnemy[i]->getFireReady() = 0;
			RECT rc = _vGEnemy[i]->getRect();
			switch (_vGEnemy[i]->getID())
			{ // 0은 루돌프포로 1은 산타에리
			case 0: // 얜 그냥 직선으로 쏜다.
			_bm->enemyFire(0, rc.right - _vGEnemy[i]->getLeft() * 37, (rc.top+rc.bottom)/2, _vGEnemy[i]->getLeft(), 0);
			break;
			case 1:
			for (float j = 0; j< 3; j++) // 3발을 포물선으로 쏜다
			{
				_bm->enemyFire(1, rc.right - _vGEnemy[i]->getLeft() * 29, rc.top, _vGEnemy[i]->getLeft(), PI/4.f+ j * PI/10.f);
			}
			break;
			}
		}
		for (int i = 0; i < _vFEnemy.size(); ++i)
		{
			if (_vFEnemy[i]->getFireReady() == 0) continue;
			--_vFEnemy[i]->getFireReady();
			RECT rc1 = _vFEnemy[i]->getRect();
			RECT rc2 = _pm->getRect();
			float angle;
			switch (_vFEnemy[i]->getID())
			{ // 0은 유에프오 1중보 2보스
			case 0:  // 얘는 플레이어 위치로 쏜다
				angle = getAngle((rc1.left + rc1.right) / 2, (rc1.top + rc1.bottom) / 2,
					(rc2.left + rc2.right) / 2, (rc2.top + rc2.bottom) / 2);
				_bm->enemyFire(2, (rc1.left + rc1.right) / 2, rc1.bottom, 0, angle);
				break;
			case 1:
				++_vFEnemy[i]->getPhase();
				for (float j = 0; j < 16; j++) // 이중포문인데 i넣지말고..
				{
					_bm->enemyFire(3, (rc1.left + rc1.right) / 2, (rc1.top + rc1.bottom) / 2, 0, 0.4f * j);
				}
				if (_vFEnemy[i]->getPhase() == 3) // 외계인을 소환
				{
					_vFEnemy[i]->getPhase() = 0;
					flyingEnemy* fEnemy;
					fEnemy = new flyingEnemy;
					fEnemy->init(0, (rc1.left + rc1.right) / 2, rc1.bottom);
					_vFEnemy.push_back(fEnemy);
				}
				break;
			case 2:
				if (_vFEnemy[i]->getPhase() == 0)
				{
					_bm->enemyFire(5, (rc1.left + rc1.right) / 2, (rc1.top + rc1.bottom) / 2, 0, 0.1f * (rand() % 63));
				}
				if (_vFEnemy[i]->getPhase() != 0)
				{
					for (int j = 0; j < 8; j++)
					{
						int x = rc1.left - 98 + rand() % 225;
						int y = rc1.top - 35 + rand() % 170;
						angle = getAngle(x, y,	(rc2.left + rc2.right) / 2, (rc2.top + rc2.bottom) / 2);
						_bm->enemyFire(4, x, y, 0, angle);
					}
				}
				if (_vFEnemy[i]->getFireReady() == 0) ++_vFEnemy[i]->getPhase();
				if (_vFEnemy[i]->getPhase() > 3) _vFEnemy[i]->getPhase() = 0;
				break;
			}
		}
	}
}

void enemyManager::test()
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9))
	{
		flyingEnemy* fEnemy;
		fEnemy = new flyingEnemy;
		fEnemy->init(2, GETCAM + 400, -170);
		_vFEnemy.push_back(fEnemy);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3))
	{
		groundEnemy* gEnemy;
		gEnemy = new groundEnemy;
		gEnemy->init(0, GETCAM+400, 170);
		_vGEnemy.push_back(gEnemy);
		gEnemy = new groundEnemy;
		gEnemy->init(1, GETCAM + 500, 170);
		_vGEnemy.push_back(gEnemy);
	}
}
