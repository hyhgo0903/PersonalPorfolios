#include "stdafx.h"
#include "collision.h"


void collision::deokhoInit()
{
}

void collision::deokhoUpdate()
{
	RECT temp;
	for (int i = 0; i < _im->getVItem().size(); i++)
	{// 아이템 잡고 던지기. 먹기
		if (IntersectRect(&temp, &_pl->getShadow(), &_im->getVItem()[i]->getShadow()))
		{
			if (KEYMANAGER->isOnceKeyDown('C'))
			{
				if (_im->getVItem()[i]->isFood()) //먹을 거임.
				{
					SOUNDMANAGER->play("먹는소리");
					EFFECTMANAGER->play("라이프업", _im->getVItem()[i]->getRect().left, _im->getVItem()[i]->getRect().top - 150);
					_im->getVItem()[i]->setHold();
					_pl->getPlHP() += 30.0f;
					if (_pl->getPlHP() > 100) _pl->getPlHP() = 100.0f;
				}

				if (!_im->getVItem()[i]->isFood())
				{//먹을 거 아님 : 공이나 폭탄같이 집어 던지거나 하는 것들
					if (!_im->getVItem()[i]->getPickup() && !_im->getVItem()[i]->getMoving())
					{//줍기-> 들려있지 않고, 움직이도록 하지 않음.
						_im->getVItem()[i]->setHold(_pl->getFlyX(), _pl->getFlyY() - 50, _pl->getFlyRc().bottom);
						return;
					}
					if (_im->getVItem()[i]->getPickup() && !_im->getVItem()[i]->getMoving())
					{//던지기. 들려있고, 움직이도록 하지 않음.
						if (_im->getVItem()[i]->getID() != 0)	SOUNDMANAGER->play("던지기");
						_im->throwing(!_pl->getLeft());
						_im->getVItem()[i]->attackMove(_pl->getLeft());
					}
				}
			}
		}
		if (_im->getVItem()[i]->getPickup() == true) _im->getVItem()[i]->setHold(_pl->getFlyX(), _pl->getFlyY() - 50, _pl->getFlyRc().bottom);
		//if(들고있는 상태) 아이템 위치 계속 초기화.
	}

	for (int i = 0; i < _im->getVItem().size(); ++i)
	{//아이템 벡터.
		for (int j = 0; j < _em->getVEnemy().size(); ++j)
		{//적 벡터
			if (_im->getVItem()[i]->getMoving())
			{//아이템이 움직이라고 명령받은 상태임?? -> 던졌단 얘기임.
				if (IntersectRect(&temp, &_im->getVItem()[i]->getShadow(), &_em->getVEnemy()[j]->getShadow()))
				{//충돌했니?
					if (_im->getVItem()[i]->getID() == 1)
					{//야구공이니?
						if(_em->getVEnemy()[j]->getState()!=E_HIT) SOUNDMANAGER->play("타격2");
						_em->getVEnemy()[j]->setState(E_HIT);
						if (_im->getVItem()[i]->getDirection()) _im->getVItem()[i]->makeInflect(-1.5f);
						//오른쪽으로 던져졌니?
						else _im->getVItem()[i]->makeInflect(-1.5f);
					}
					if (_im->getVItem()[i]->getID() == 2)
					{//폭탄이니?
						_em->getVEnemy()[j]->setState(E_DEAD);
						_im->getVItem()[i]->makeBoom();
					}
				}
			}
		}
	}
}

void collision::deokhoRender()
{
}
