#include "stdafx.h"
#include "collision.h"


void collision::deokhoInit()
{
}

void collision::deokhoUpdate()
{
	RECT temp;
	for (int i = 0; i < _im->getVItem().size(); i++)
	{
		if (IntersectRect(&temp, &_pl->getFlyRc(), &_im->getVItem()[i]->getRect()))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (!_im->getVItem()[i]->getPickup() && !_im->getVItem()[i]->getMoving())
				{
					_im->getVItem()[i]->setHold(_pl->getFlyX(), _pl->getFlyY());
					return;
				}
				if (_im->getVItem()[i]->getPickup() && !_im->getVItem()[i]->getMoving())
				{
					_im->throwing(!_pl->getLeft());
					_im->getVItem()[i]->attackMove(_pl->getLeft());
				}
			}
		}
		if(_im->getVItem()[i]->getPickup()==true) _im->getVItem()[i]->setHold(_pl->getFlyX(), _pl->getFlyY());
	}

	
}

void collision::deokhoRender()
{
}
