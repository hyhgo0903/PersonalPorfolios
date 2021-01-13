#include "stdafx.h"
#include "grab.h"
#include "player.h"

void grab::EnterState()
{
    _pl->getIndex() = 0;
    count = 90;
}

void grab::updateState()
{
    count--;
    if (KEYMANAGER->isOnceKeyDown('Z'))
    {
        _pl->setState(GRABSWING);
    }

    if (count <= 0)
    {
        _pl->setState(IDLE);
    }

}

void grab::ExitState()
{
    _pl->getIsGrab() = false;
}
