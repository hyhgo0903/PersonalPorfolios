#include "stdafx.h"
#include "combo23.h"
#include "player.h"

void combo23::EnterState()
{

}

void combo23::updateState()
{

    if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().right, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }
    if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().left - 150, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }


}

void combo23::ExitState()
{
    _pl->getIndex() = 0;
}
