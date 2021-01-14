#include "stdafx.h"
#include "dead.h"
#include "player.h"

void dead::EnterState()
{

	if (!_pl->getLeft())
	{
		_pl->getIndex() = 0;
	}
	else
	{
		_pl->getIndex() = 4;
	}
	
}

void dead::updateState()
{
	if (!_pl->getLeft() && _pl->getIndex() < 4)
	{
		_pl->getGroundX() -= 10;
		_pl->getFlyX() -= 10;
	}
	else if (_pl->getLeft() && _pl->getIndex() > 0)
	{
		_pl->getGroundX() += 10;
		_pl->getFlyX() += 10;
	}

	

}

void dead::ExitState()
{
}
