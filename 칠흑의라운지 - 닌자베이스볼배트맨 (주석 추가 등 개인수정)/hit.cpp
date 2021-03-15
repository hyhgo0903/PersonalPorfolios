#include "stdafx.h"
#include "hit.h"
#include "player.h"

void hit::EnterState()
{
	_pl->getFlyY() = _pl->getGroundY();
    _pl->getIndex() = 0;
    _pl->getPlHP() -= 10.0f;
    count = 30;
}

void hit::updateState()
{
    count--;
    if (count <= 0)
    {
        _pl->setState(IDLE);
    }
}

void hit::ExitState()
{
}
