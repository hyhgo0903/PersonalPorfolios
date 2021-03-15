#include "stdafx.h"
#include "combo12.h"
#include "player.h"

void combo12::EnterState()
{
	_pl->getIndex() = 0;
	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().right, _pl->getGroundRc().top); }
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().left - 150, _pl->getGroundRc().top); }
}

void combo12::updateState()
{

	
	
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_pl->setState(COMBO13);
	}

}

void combo12::ExitState()
{
}
