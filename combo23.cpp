#include "stdafx.h"
#include "combo23.h"
#include "player.h"

void combo23::EnterState()
{
	_pl->getIndex() = 0; 
	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().right, _pl->getGroundRc().top); }
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().left - 150, _pl->getGroundRc().top); }

}

void combo23::updateState()
{

   

}

void combo23::ExitState()
{
}
