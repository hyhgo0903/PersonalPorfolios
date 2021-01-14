#include "stdafx.h"
#include "collision.h"


void collision::younghanInit()
{
}

void collision::younghanUpdate()
{
	//플레이어 어택 렉트와 에너미 렉트 충돌시 HIT상태로 변경시키고 체력을 깎음

	//플레이어의 상태가 GRABSWING이라면
	if (_pl->getEnumState() == GRABSWING)
	{
		for (int i = 0; i < _em->getVEnemy().size(); ++i)
		{
			RECT sour;
			//적에게 phase가 존재하는 boss라면 phase 1, 2상태일때 공격이 불가능하도록 설정
			if (_em->getVEnemy()[i]->getPhase() == 1 || _em->getVEnemy()[i]->getPhase() == 2) continue;

			//적이 이미 E_HIT상태이거나 E_DEAD상태라면 공격이 불가능하도록 설정
			if (_em->getVEnemy()[i]->getState() == E_HIT || _em->getVEnemy()[i]->getState() == E_DEAD) continue;

			//적과 플레이어의 그림자가 충돌되고
			if (IntersectRect(&sour, &_em->getVEnemy()[i]->getShadow(), &_pl->getShadow()))
			{
				for (int j = 0; j < _pl->getAttack()->getVAttack().size(); ++j)
				{
					RECT temp;
					//적의 렉트와 플레이어의 공격렉트가 충돌되면
					if (IntersectRect(&temp, &_em->getVEnemy()[i]->getRect(), &_pl->getAttack()->getVAttack()[j].rc))
					{
						//중복 데미지를 방지하기위해 공격렉트를 삭제하고
						_pl->getAttack()->removeAttack(j);

						//????
						if (_em->getVEnemy()[i]->getState() == E_GRAB && _pl->getFlyCount() >= 20)
						{
							//적의 상태를 E_FLYING으로 변경
							_em->getVEnemy()[i]->getState() = E_FLYING;
						}
						_score += 100; //점수를 100만큼 더해준다
						break;
					}
				}
			}
		}
	}
	else//플레이어가 GRABSWING상태가 아니라면
	{
		for (int i = 0; i < _em->getVEnemy().size(); ++i)
		{
			RECT sour;
			//적에게 phase가 존재하는 boss라면 phase 1, 2상태일때 공격이 불가능하도록 설정
			if (_em->getVEnemy()[i]->getPhase() == 1 || _em->getVEnemy()[i]->getPhase() == 2) continue;

			//적이 이미 E_HIT상태이거나 E_DEAD상태라면 공격이 불가능하도록 설정
			if (_em->getVEnemy()[i]->getState() == E_HIT || _em->getVEnemy()[i]->getState() == E_DEAD) continue;

			//적과 플레이어의 그림자가 충돌되고
			if (IntersectRect(&sour, &_em->getVEnemy()[i]->getShadow(), &_pl->getShadow()))
			{
				for (int j = 0; j < _pl->getAttack()->getVAttack().size(); ++j)
				{
					RECT temp;
					//적의 렉트와 플레이어의 공격렉트가 충돌되면
					if (IntersectRect(&temp, &_em->getVEnemy()[i]->getRect(), &_pl->getAttack()->getVAttack()[j].rc))
					{
						//랜덤 사운드를 출력시키고
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
						_em->getVEnemy()[i]->setAlpha(); //enemy의 알파를 255로 설정
						_em->getVEnemy()[i]->setAtkNum(); //enemy1이라면 피격모션을 랜덤으로 출력시키고
						_em->getVEnemy()[i]->getState() = E_HIT; //enemy를 E_HIT상태로 변경
						_em->getVEnemy()[i]->getDamage(20); //enemy에게 20의 데미지를 가한다
						_score += 100; //점수를 100만큼 더해준다
						break;
					}
				}
				for (int i = 0; i < _em->getVEnemy().size(); ++i)
				{
					//????
					if (_pl->getIsGrab()) break;
					RECT temp;

					//플레이어의 렉트와 적의 렉트가 충돌하고
					if (IntersectRect(&temp, &_pl->getFlyRc(), &_em->getVEnemy()[i]->getRect()))
					{
						//아래의 조건의 충족된다면
						if (temp.right - temp.left > (_em->getVEnemy()[i]->getRect().right - _em->getVEnemy()[i]->getRect().left) / 3 && _pl->getFlyY() - _em->getVEnemy()[i]->getY() < 4
							&& _pl->getFlyY() - _em->getVEnemy()[i]->getY() > -4 && (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)))
						{
							if (_pl->getLeft()) _em->getVEnemy()[i]->getLeft() = false; //플레이어가 왼쪽을 보고있다면 적은 오른쪽을	보게만든다		
							else _em->getVEnemy()[i]->getLeft() = true; //플레이어가 오른쪽을 보고있다면 적은 왼쪽을 보게만든다
							_em->getVEnemy()[i]->setState(E_GRAB); //적을 E_GRAB상태로 변경
							_pl->getIsGrab() = true; //??
							break;
						}
					}
				}
			}

		}
	}
	for (int i = 0; i < _em->getVEnemy().size(); ++i)
	{
		//플레이어가 HIT, GRAB, DEAD상태가 아니라면
		if (_pl->getEnumState() == HIT || _pl->getEnumState() == GRAB || _pl->getEnumState() == DEAD) break;
		RECT temp;
		//적의 그림자와 플레이어가 충돌되고
		if (IntersectRect(&temp, &_em->getVEnemy()[i]->getShadow(), &_pl->getShadow()))
		{
			//플레이어와 적의 공격렉트가 충돌되면
			if (IntersectRect(&temp, &_pl->getFlyRc(), &_em->getVEnemy()[i]->getAtkRc()))
			{
				_pl->setState(HIT); //플레이어의 상태를 HIT로 변경
				_em->getVEnemy()[i]->getAtkRc() = RectMake(0, 0, 0, 0); //적의 공격렉트의 위치를 변경
				break;
			}
		}
	}
}

void collision::younghanRender()
{
}
