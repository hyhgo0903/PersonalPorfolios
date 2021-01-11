#include "stdafx.h"
#include "jumpAttack.h"
#include "player.h"
#define GRAVITY 0.6f

void jumpAttack::EnterState()
{
}

void jumpAttack::updateState()
{

    _pl->getJumpPower() -= GRAVITY;
    _pl->getFlyY() -= _pl->getJumpPower();

    if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().right, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }
    if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().left - 150, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }

    if (_pl->getFlyY() > _pl->getGroundY())
    {
        _pl->getFlyY() = _pl->getGroundY();
        _pl->setState(JUMP);
    }
}

void jumpAttack::ExitState()
{
}
