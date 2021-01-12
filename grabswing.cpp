#include "stdafx.h"
#include "grabswing.h"
#include "player.h"

void grabswing::EnterState()
{

}

void grabswing::updateState()
{

	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().right, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getFlyRc().left - 150, (_pl->getFlyRc().bottom + _pl->getFlyRc().top) / 2); }


}

void grabswing::ExitState()
{
	_pl->getIndex() = 0;
}
