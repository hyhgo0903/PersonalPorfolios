#include "stdafx.h"
#include "combo21.h"
#include "player.h"

void combo21::EnterState()
{

}

void combo21::updateState()
{

    if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().right, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }
    if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().left - 150, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }

    if (KEYMANAGER->isOnceKeyDown('Z'))
    {
        _pl->setState(COMBO22);
    }

}

void combo21::ExitState()
{
    _pl->getIndex() = 0;
}
