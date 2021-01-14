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

	if (_pl->getEnumState() == GRABSWING)
	{
		for (int i = 0; i < _em->getVEnemy().size(); ++i)
		{
			RECT sour;
			if (_em->getVEnemy()[i]->getState() == E_HIT || _em->getVEnemy()[i]->getState() == E_DEAD) continue;
			if (IntersectRect(&sour, &_em->getVEnemy()[i]->getShadow(), &_pl->getShadow()))
			{
				for (int j = 0; j < _pl->getAttack()->getVAttack().size(); ++j)
				{
					RECT temp;
					if (IntersectRect(&temp, &_em->getVEnemy()[i]->getRect(), &_pl->getAttack()->getVAttack()[j].rc))
					{
						int effectSound = RND->getInt(4);
						switch (effectSound)
						{
						case 0:
							SOUNDMANAGER->play("타격1");
							break;
						case 1:
							SOUNDMANAGER->play("타격2");
							break;
						case 2:
							SOUNDMANAGER->play("타격3");
							break;
						case 3:
							SOUNDMANAGER->play("타격4");
							break;
						default:
							break;
						}
						if (_em->getVEnemy()[i]->getState() == E_GRAB)
						{
							_em->getVEnemy()[i]->getState() = E_FLYING;
							_em->getVEnemy()[i]->getDamage(20);
						}
						_score += 100;
						hitted = true;
						break;
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < _em->getVEnemy().size(); ++i)
		{
			RECT sour;
			if (_em->getVEnemy()[i]->getState() == E_HIT || _em->getVEnemy()[i]->getState() == E_DEAD) continue;
			if (IntersectRect(&sour, &_em->getVEnemy()[i]->getShadow(), &_pl->getShadow()))
			{
				for (int j = 0; j < _pl->getAttack()->getVAttack().size(); ++j)
				{
					RECT temp;
					if (IntersectRect(&temp, &_em->getVEnemy()[i]->getRect(), &_pl->getAttack()->getVAttack()[j].rc))
					{
						int effectSound = RND->getInt(4);
						switch (effectSound)
						{
						case 0:
							SOUNDMANAGER->play("타격1");
							break;
						case 1:
							SOUNDMANAGER->play("타격2");
							break;
						case 2:
							SOUNDMANAGER->play("타격3");
							break;
						case 3:
							SOUNDMANAGER->play("타격4");
							break;
						default:
							break;
						}
						_em->getVEnemy()[i]->getState() = E_HIT;
						_em->getVEnemy()[i]->getDamage(20);
						_score += 100;
						hitted = true;
						break;
					}
				}
				for (int i = 0; i < _em->getVEnemy().size(); ++i)
				{
					if (_pl->getIsGrab()) break;
					RECT temp;
					if (IntersectRect(&temp, &_pl->getFlyRc(), &_em->getVEnemy()[i]->getRect()))
					{
						if (temp.right - temp.left > (_em->getVEnemy()[i]->getRect().right - _em->getVEnemy()[i]->getRect().left) / 3 && _pl->getFlyY() - _em->getVEnemy()[i]->getY() < 4
							&& _pl->getFlyY() - _em->getVEnemy()[i]->getY() > -4 && (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)))
						{
							if (_pl->getLeft()) _em->getVEnemy()[i]->getLeft() = false;								
							else _em->getVEnemy()[i]->getLeft() = true;
							_em->getVEnemy()[i]->setState(E_GRAB);
							_pl->getIsGrab() = true;
							break;
						}
					}
				}
			}

		}
	}
	for (int i = 0; i < _em->getVEnemy().size(); ++i)
	{
		if (_pl->getIsHit()) break;
		RECT temp;
		if (IntersectRect(&temp, &_em->getVEnemy()[i]->getShadow(), &_pl->getShadow()))
		{
			if (IntersectRect(&temp, &_pl->getFlyRc(), &_em->getVEnemy()[i]->getAtkRc()))
			{
				_pl->getIsHit() = true;
				_em->getVEnemy()[i]->getAtkRc() = RectMake(0, 0, 0, 0);
				break;
			}
		}

	}
}

void collision::younghanRender()
{
}
