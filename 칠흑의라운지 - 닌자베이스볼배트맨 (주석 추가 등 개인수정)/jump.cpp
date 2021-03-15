#include "stdafx.h"
#include "Jump.h"
#include "player.h"

#define GRAVITY 0.6f

void Jump::EnterState()
{
	_pl->getFlyRc() = _pl->getGroundRc();
}

void Jump::updateState()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (!_pl->getLeft())
		{
			_pl->plusDirectionChanged();
			_pl->getLeft() = true;
		}
		_pl->getFlyX() -= 3;	_pl->getGroundX() -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_pl->getLeft())
		{
			_pl->plusDirectionChanged();
			_pl->getLeft() = false;
		}
		_pl->getFlyX() += 3;	_pl->getGroundX() += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_pl->getFlyY() -= 3;	_pl->getGroundY() -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_pl->getFlyY() += 3;	_pl->getGroundY() += 3;
	}

    _pl->getJumpPower() -= GRAVITY;
    _pl->getFlyY() -= _pl->getJumpPower(); // 중력만큼 점프파워를 점점 떨어트려 자연스럽게 점프하는거처럼 보이게 만들었습니다
	if (_pl->getFlyY() > _pl->getGroundY()) // 점프중인 렉트가 땅에 있는 렉트보다 내려간다면 상태를 바꾸고 각각의 위치를 같게 해줬습니다
	{ 
		_pl->getFlyY() = _pl->getGroundY();
		_pl->setState(IDLE);
	}

    if (KEYMANAGER->isOnceKeyDown('Z'))
    {
        _pl->setState(JUMPATTACK);
    }
}

void Jump::ExitState()
{
}

