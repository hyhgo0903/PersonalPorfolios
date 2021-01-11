#include "stdafx.h"
#include "combo22.h"
#include "player.h"

void combo22::EnterState()
{

}

void combo22::updateState()
{

    if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().right, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }
    if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().left - 150, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }

    if (KEYMANAGER->isOnceKeyDown('Z'))
    {
        _pl->setState(COMBO23);
    }

}

void combo22::ExitState()
{
    _pl->getIndex() = 0;
}
