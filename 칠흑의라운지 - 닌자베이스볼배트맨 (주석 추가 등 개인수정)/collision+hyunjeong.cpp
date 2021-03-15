#include "stdafx.h"
#include "collision.h"


void collision::hyunjungInit()
{
	_itemOrder = 0;
}

void collision::hyunjungUpdate()
{
	for (int i = 0; i < _sm->getVObject().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_pl->getShadow(), &_sm->getVObject()[i]->getShadow()))
		{
			if (IntersectRect(&temp, &_pl->getAttack()->getAttackRect(), &_sm->getVObject()[i]->getRect()))
			{
				if (_sm->getVObject()[i]->getId() == 1)
				{
					SOUNDMANAGER->play("쓰레기통부수는소리");
					RECT src = _sm->getVObject()[i]->getRect();
					float cenX = (src.right + src.left) / 2;
					float cenY = (src.top + src.bottom) / 2;
					if (_itemOrder == 0)
					{
						_itemOrder++;
						_im->createBaseball(cenX, cenY, src.bottom);
					}
					else if (_itemOrder == 1)
					{
						_itemOrder++;
						_im->createPizza(cenX, cenY, src.bottom);
					}
					else if (_itemOrder == 2)
					{
						_itemOrder++;
						_im->createBomb(cenX, cenY, src.bottom);
					}
					else 
					{
						_im->createFood(cenX, cenY, src.bottom);
					}
				}
				if(_sm->getVObject()[i]->getId()==0)SOUNDMANAGER->play("의자부수는소리");
				_sm->removeObject(i);
			}
		}
	}

}

void collision::hyunjungRender()
{
}
