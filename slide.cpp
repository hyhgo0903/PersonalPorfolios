#include "stdafx.h"
#include "slide.h"
#include "player.h"
#define GRAVITY 0.6f


void slide::EnterState()
{
    _pl->getJumpPower() = 20;
	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().right + 150, _pl->getGroundRc().top); }
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().left - 300, _pl->getGroundRc().top); }
}

void slide::updateState()
{
    
    _pl->getJumpPower() -= GRAVITY;
    _pl->getGroundX() = _pl->getFlyX();
    if (!_pl->getLeft())
    {
        _pl->getFlyX() += _pl->getJumpPower();
    }
    if (_pl->getLeft())
    {
        _pl->getFlyX() -= _pl->getJumpPower();
    }

    if (_pl->getJumpPower() <= 0)
    {
        _pl->setState(IDLE);
    }

}

void slide::ExitState()
{
    _pl->getIndex() = 0;
}
