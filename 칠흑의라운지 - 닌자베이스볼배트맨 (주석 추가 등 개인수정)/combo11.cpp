#include "stdafx.h"
#include "combo11.h"
#include "player.h"

void combo11::EnterState()
{
	_pl->getIndex() = 0;
	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().right, _pl->getGroundRc().top); }
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().left - 150, _pl->getGroundRc().top); }
}

void combo11::updateState()
{

	

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_pl->setState(COMBO12);
	}

}

void combo11::ExitState()
{
}
