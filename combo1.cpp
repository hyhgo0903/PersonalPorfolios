#include "stdafx.h"
#include "combo1.h"
#include "player.h"

void combo1::EnterState()
{
	
}

void combo1::updateState()
{
	_pl->getAttack()->Attack(_pl->getFlyRc().right + 50, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2);

	if (!KEYMANAGER->isStayKeyDown(VK_LEFT) &&
		!KEYMANAGER->isStayKeyDown(VK_RIGHT) &&
		!KEYMANAGER->isStayKeyDown(VK_UP) &&
		!KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_pl->setState(IDLE);
	}
	

}

void combo1::ExitState()
{
}
