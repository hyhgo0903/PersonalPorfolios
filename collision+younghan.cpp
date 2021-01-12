#include "stdafx.h"
#include "collision.h"


void collision::younghanInit()
{
}

void collision::younghanUpdate()
{
	//플레이어 어택 렉트와 에너미 렉트 충돌시 HIT상태로 변경시키고 체력을 깎음
	bool hitted;
	hitted = false;

	for (int i = 0; i < _em->getVEnemy().size(); ++i)
	{
		for (int j = 0; j < _pl->getAttack()->getVAttack().size(); ++j)
		{
			RECT temp;
			if (IntersectRect(&temp, &_em->getVEnemy()[i]->getRect(), &_pl->getAttack()->getVAttack()[j].rc))
			{
				_em->getVEnemy()[i]->getState() = E_HIT;
				//_em->getVEnemy()[i]->
				hitted = true;
			}
		}
	}

	if (hitted) _pl->getAttack()->getVAttack().clear();
}

void collision::younghanRender()
{
}
