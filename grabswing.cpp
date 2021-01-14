#include "stdafx.h"
#include "grabswing.h"
#include "player.h"

void grabswing::EnterState()
{
    _pl->getIndex() = 0;
	_pl->getFlyCount() = 0;
    count = 0;
}

void grabswing::updateState()
{
    count++;
	_pl->getFlyCount()++;

	if (_pl->getIndex() >= 4 && _pl->getIndex() < 6)
	{
	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().right, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().left - 150, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); } 
	}

    if (count == 20)
    {
        SOUNDMANAGER->play("잡기공격");
    }
}

void grabswing::ExitState()
{
}
