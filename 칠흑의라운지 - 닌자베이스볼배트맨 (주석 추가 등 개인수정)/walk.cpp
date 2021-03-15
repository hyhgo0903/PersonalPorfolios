#include "stdafx.h"
#include "walk.h"
#include "player.h"

void walk::EnterState()
{
	_pl->getIndex() = 0;
}

void walk::updateState()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (!_pl->getLeft())
		{ // 원래 방향과 달랐으면 방향전환 변수를 1 올려줌
			_pl->plusDirectionChanged();
			_pl->getLeft() = true;
		}
		_pl->getFlyX() -= 3;	_pl->getGroundX() -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)&& !KEYMANAGER->isStayKeyDown(VK_LEFT))
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

    if (_pl->getDirectionChanged() >= 2 && KEYMANAGER->isOnceKeyDown('Z'))
    {
        _pl->setState(WINDMILL);
    }

    if (_pl->getIsGrab())
    {
        _pl->setState(GRAB);
    }

    if (KEYMANAGER->isOnceKeyDown('Z'))
    {
        _pl->setState(COMBO1);
    }

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_pl->setState(JUMP);
	}
	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) &&		!KEYMANAGER->isStayKeyDown(VK_RIGHT) &&
		!KEYMANAGER->isStayKeyDown(VK_UP) &&		!KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_pl->setState(IDLE);
	}
}

void walk::ExitState()
{
	_pl->getIndex() = 0;
}
