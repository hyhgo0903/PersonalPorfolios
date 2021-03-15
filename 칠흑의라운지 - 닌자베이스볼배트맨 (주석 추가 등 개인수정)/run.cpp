#include "stdafx.h"
#include "run.h"
#include "player.h"

void run::EnterState()
{
    _pl->getIndex() = 0;
}

void run::updateState()
{

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (!_pl->getLeft())
		{
			_pl->plusDirectionChanged();
			_pl->getLeft() = true; //왼쪽키를 입력하면 isLeft 불값을 트루로 만들고 왼쪽을 보게 만들었습니다.
		}
		_pl->getFlyX() -= 8;	_pl->getGroundX() -= 8;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_pl->getLeft())
		{
			_pl->plusDirectionChanged();
			_pl->getLeft() = false; // 반대로 오른쪽으로 보게 만들었습니다.
		}
		_pl->getFlyX() += 8;	_pl->getGroundX() += 8;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_pl->getFlyY() -= 8;	_pl->getGroundY() -= 8;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_pl->getFlyY() += 8;	_pl->getGroundY() += 8;
	}

    if (_pl->getIsGrab()) // 플레이어의 isGrab이 트루라면 상태를 그랩으로 바꾸게 했습니다.
    {
        _pl->setState(GRAB);
    }

    if (KEYMANAGER->isOnceKeyDown('Z')) // 달리는 중에 Z키를 누르면 슬라이딩
    {
        _pl->setState(SLIDE);
    }
	if (KEYMANAGER->isOnceKeyDown('X')) // 아니면 태클로 이행하게 했습니다.
	{
		_pl->setState(TACKLE);
	}
	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) &&
		!KEYMANAGER->isStayKeyDown(VK_RIGHT) &&
		!KEYMANAGER->isStayKeyDown(VK_UP) &&
		!KEYMANAGER->isStayKeyDown(VK_DOWN)) // 방향키를 그만 입력하면 idle로 돌아가게 했습니다.
	{
		_pl->setState(IDLE);
	}
}

void run::ExitState()
{
}
