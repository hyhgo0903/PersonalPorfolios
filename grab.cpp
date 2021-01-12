#include "stdafx.h"
#include "grab.h"
#include "player.h"

void grab::EnterState()
{

}

void grab::updateState()
{

	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().right, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().left - 150, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }


}

void grab::ExitState()
{
	_pl->getIndex() = 0;
}
