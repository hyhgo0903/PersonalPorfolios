#include "stdafx.h"
#include "jumpAttack.h"
#include "player.h"
#define GRAVITY 0.6f

void jumpAttack::EnterState()
{
	_pl->getIndex() = 0;
	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().right, _pl->getGroundRc().top); }
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().left - 150, _pl->getGroundRc().top); }
}

void jumpAttack::updateState()
{

    _pl->getJumpPower() -= GRAVITY;
    _pl->getFlyY() -= _pl->getJumpPower();

    

    if (_pl->getFlyY() > _pl->getGroundY())
    {
        _pl->getFlyY() = _pl->getGroundY();
        _pl->setState(JUMP);
    }
}

void jumpAttack::ExitState()
{
}
