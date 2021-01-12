#include "stdafx.h"
#include "combo1.h"
#include "player.h"

void combo1::EnterState()
{
	_pl->getIndex() = 0;
	// 오른쪽이면 오른쪽부터 공격 범위만큼 생성하게
	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().right, _pl->getGroundRc().top); }
	// 왼쪽이면 왼쪽부터 공격 범위만큼 빼서 생성하게
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().left - 150, _pl->getGroundRc().top); }
}

void combo1::updateState()
{
	
	

    if ((KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)) && KEYMANAGER->isOnceKeyDown('Z'))
    {
        _pl->setState(COMBO21);
    }

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_pl->setState(COMBO11);
	}

}

void combo1::ExitState()
{
}
