#include "stdafx.h"
#include "playerManager.h"
#include "itemManager.h"
#include "bulletManager.h"


void playerManager::fire()
{
	_tank.currentDelay = _tank.maxDelay; // 딜레이는 최대로	
	if (_tank.state == RIGHTATTACK || // 상태조정
		_tank.state == RIGHTRUN || _tank.state == RIGHTIDLE)
	{ _tank.state = RIGHTATTACK; stateChange();}
	else {_tank.state = LEFTATTACK; stateChange();}
	int ID; // 포탄의종류
	if (_specialCount < 2)
	{ // 0캐논기본, 2미사일기본, 4멀티기본, 6슈탱기본
		ID = 2 * _tank.type;
		_specialCount++;
	}
	else
	{ // 1캐논특수, 3미사일특수, 5멀티특수, 7슈탱특수
		ID = 2 * _tank.type + 1;
		_specialCount = 0;
	}
	int isRight;
	if (_tank.state == LEFTATTACK) isRight = 0;	else isRight = 1;
	
	if (ID < 4) // 이러면 한발
	{_bm->playerFire(ID, _tank.rc.left + TANKWIDTH * isRight, _tank.rc.top, _tank.angle, 3.f + 0.08f * _tank.currentPower, _damageCoefficient);}
	else if (ID == 4 || ID == 6) // 이러면 세발
	{
		for (int i = 0; i < 3; i++)
		{
			_bm->playerFire(ID, _tank.rc.left + TANKWIDTH * isRight, _tank.rc.top,
				_tank.angle - 0.175 + 0.175*i, 3.f + 0.08f * _tank.currentPower, _damageCoefficient);
		}
	}
	else // 이러면 9발
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				_bm->playerFire(ID, _tank.rc.left + TANKWIDTH * isRight, _tank.rc.top,
					_tank.angle- 0.175 + 0.175*i, 3.f + 0.08f * (_tank.currentPower - 10 + 10 * j), _damageCoefficient);
			}
		}
	}
}