#include "stdafx.h"
#include "combo21.h"
#include "player.h"

void combo21::EnterState()
{
	_pl->getIndex() = 0; 
	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().right, _pl->getGroundRc().top); }
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().left - 150, _pl->getGroundRc().top); }
}

void combo21::updateState()
{

   

    if (KEYMANAGER->isOnceKeyDown('Z'))
    {
        _pl->setState(COMBO22);
    }

}

void combo21::ExitState()
{
}
