#include "stdafx.h"
#include "Jump.h"
#include "player.h"

#define GRAVITY 0.2f

void Jump::EnterState()
{
	_pl->getFlyRc() = _pl->getGroundRc();
	_jumpPower = 5;
	// 여기서 방향에따라 이미지넣고 인덱스 대충 초기화해줌
}

void Jump::updateState()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (!_pl->getLeft())
		{
			_pl->plusDirectionChanged();
			_pl->getLeft() = true; // 방향바뀜 카운트 올려주고 왼쪽으로
		}
		_pl->getFlyX() -= 3;	_pl->getGroundX() -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_pl->getLeft())
		{
			_pl->plusDirectionChanged();
			_pl->getLeft() = false; // 방향바뀜 카운트 올려주고 오른쪽으로
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

	_jumpPower -= GRAVITY;
	_pl->getFlyY() -= _jumpPower; // 늘상 보던 중력과 점프파워
	if (_pl->getFlyY() > _pl->getGroundY())
	{ // 
		_pl->getFlyY() = _pl->getGroundY();
		_pl->setState(IDLE);
	}
}

void Jump::ExitState()
{
}

