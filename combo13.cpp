#include "stdafx.h"
#include "combo13.h"
#include "player.h"

void combo13::EnterState()
{
	_pl->getIndex() = 0;	
	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().right, _pl->getGroundRc().top); }
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().left - 150, _pl->getGroundRc().top); }
}

void combo13::updateState()
{




}

void combo13::ExitState()
{
}
