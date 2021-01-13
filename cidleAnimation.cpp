#include "stdafx.h"
#include "cidleAnimation.h"
#include "player.h"

//character idle animationÀÔ´Ï´Ù
void cidleAnimation::EnterState()
{
}

void cidleAnimation::updateState()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_pl->getDirMemory() != 1)
		{
			_pl->getDirMemory() = 1;
			_pl->setState(WALK);
		}
		else
		{
			_pl->setState(RUN);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_pl->getDirMemory() != 2)
		{
			_pl->getDirMemory() = 2;
			_pl->setState(WALK);
		}
		else
		{
			_pl->setState(RUN);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_pl->getDirMemory() != 3)
		{
			_pl->getDirMemory() = 3;
			_pl->setState(WALK);
		}
		else
		{
			_pl->setState(RUN);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_pl->getDirMemory() != 4)
		{
			_pl->getDirMemory() = 4;
			_pl->setState(WALK);
		}
		else
		{
			_pl->setState(RUN);
		}
	}
}

void cidleAnimation::ExitState()
{
}
