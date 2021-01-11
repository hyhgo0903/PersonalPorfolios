#include "stdafx.h"
#include "combo1.h"
#include "player.h"

void combo1::EnterState()
{
	
}

void combo1::updateState()
{
	// 오른쪽이면 오른쪽부터 공격 범위만큼 생성하게
	if(!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().right, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }
	// 왼쪽이면 왼쪽부터 공격 범위만큼 빼서 생성하게
	if(_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().left - 150, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }
	

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
    _pl->getIndex() = 0;
}
