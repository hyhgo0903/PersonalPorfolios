#include "stdafx.h"
#include "interaction.h"

void interaction::yoonghoInit()
{
}

void interaction::yoonghoUpdate()
{
	for (int i = 0; i < _se->getVSne().size(); ++i)
	{ // 사이오닉스톰
		if (_se->getVSne()[i]->getID() != 1) continue;
		for (int j = 0; j < _um->getVUnit().size(); ++j)
		{
			if (_um->getVUnit()[j]->getState() == DEAD) continue;
			if (_um->getVUnit()[j]->getBelong() == _se->getVSne()[i]->getBelong()) continue;
			RECT temp; // 피아식별을 하는 사이오닉스톰으로.. 이넘문은 다르지만 0,1로 비교하므로 비교가능하다
			if (IntersectRect(&temp, &_um->getVUnit()[j]->getRect(), &_se->getVSne()[i]->getRect()))
			{
				_um->getVUnit()[j]->getHP() -= 0.2f;
			}
		}
	}



	for (int i = 0; i < _um->getVUnit().size(); ++i)
	{ // 타겟있는놈만
		int tg = _um->getVUnit()[i]->getTarget();
		if (tg == -1) continue; // 타겟없는놈은 컨티뉴
		RECT temp;
		if (_um->getVUnit()[tg]->getState() == DEAD)
		{
			_um->getVUnit()[i]->getTarget() = -1; // 타겟이 죽은놈이면 풀어줌
			continue;
		}
		if (_um->getVUnit()[i]->getAttackReady())
		{ // 타겟이 있는 상태에서 공격준비되면
			if (_um->getVUnit()[i]->getID() == 3)
			{ // 시민이면 어그로끔(타겟을 내쪽으로)
				for (int j = 0; j < _um->getVUnit().size(); ++j)
				{
					if (IntersectRect(&temp, &_um->getVUnit()[i]->getFocusRect(), &_um->getVUnit()[j]->getRect())
						&& _um->getVUnit()[j]->getState() != DEAD 
						&& _um->getVUnit()[i]->getBelong() != _um->getVUnit()[j]->getBelong())
					{
						_um->getVUnit()[j]->getTarget() = i;
					}
				}
			}
			else if (_um->getVUnit()[i]->getID() == 4)
			{ // 템플러면 스톰을 생성함
				if (_um->getVUnit()[i]->getBelong() == PLAYER)
				{
					_se->createPsionic(S_PLAYER, _um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY());
				}
				if (_um->getVUnit()[i]->getBelong() == ENEMY)
				{
					_se->createPsionic(S_ENEMY, _um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY());
				}
			}
			_um->getVUnit()[i]->getAttackReady() = false;
			_um->getVUnit()[tg]->getHP() -= _um->getVUnit()[i]->getDamage();
		}
		else if (IntersectRect(&temp, &_um->getVUnit()[tg]->getRect(), &_um->getVUnit()[i]->getRangeRect())
			&& _um->getVUnit()[i]->getState() != ATTACK)
		{
			_um->getVUnit()[i]->setState(ATTACKWAIT);
		}
		else if (!IntersectRect(&temp, &_um->getVUnit()[tg]->getRect(), &_um->getVUnit()[i]->getRangeRect())
			&& _um->getVUnit()[i]->getState() == ATTACKWAIT) // 공격대기중에서 타겟이 사거리 벗어나면 추적
		{
			_um->getVUnit()[i]->setState(WALK);
		}
		if (_um->getVUnit()[i]->getState() == WALK)
		{ // 타겟있을떄 워크는 상대를 목표로 한다
			_um->getVUnit()[i]->setDest(_um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY());
		}
	}

}

void interaction::yoonghoRender()
{
}