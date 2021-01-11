#include "stdafx.h"
#include "combo11.h"
#include "player.h"

void combo11::EnterState()
{

}

void combo11::updateState()
{

	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().right, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().left - 150, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_pl->setState(COMBO12);
	}

}

void combo11::ExitState()
{
    _pl->getIndex() = 0;
}
