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
				_um->getVUnit()[j]->getHP() -= 0.1f;
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
				_um->getVUnit()[tg]->getTarget() = i;
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

	for (int i = 0; i < _um->getVUnit().size(); ++i)
	{
		if (_um->getVUnit()[i]->getState() != WALK) continue;
		POINT tempPtLT = picking(_um->getVUnit()[i]->getRect().left, _um->getVUnit()[i]->getRect().top);
		if (_sm->getIsoTile()[tempPtLT.x + tempPtLT.y * 30].MUM == UNMOVE)
		{
			_um->getVUnit()[i]->moveCancel();
			_um->getVUnit()[i]->getX() += _um->getVUnit()[i]->getSpeed();
			continue;
		}
		POINT tempPtRT = picking(_um->getVUnit()[i]->getRect().right, _um->getVUnit()[i]->getRect().top);
		if (_sm->getIsoTile()[tempPtRT.x + tempPtRT.y * 30].MUM == UNMOVE)
		{
			_um->getVUnit()[i]->moveCancel();
			_um->getVUnit()[i]->getX() -= _um->getVUnit()[i]->getSpeed();
			continue;
		}
		POINT tempPtLB = picking(_um->getVUnit()[i]->getRect().left, _um->getVUnit()[i]->getRect().bottom);
		if (_sm->getIsoTile()[tempPtLB.x + tempPtLB.y * 30].MUM == UNMOVE)
		{
			_um->getVUnit()[i]->moveCancel();
			_um->getVUnit()[i]->getX() += _um->getVUnit()[i]->getSpeed();
			continue;
		}
		POINT tempPtRB = picking(_um->getVUnit()[i]->getRect().right, _um->getVUnit()[i]->getRect().bottom);
		if (_sm->getIsoTile()[tempPtRB.x + tempPtRB.y * 30].MUM == UNMOVE)
		{
			_um->getVUnit()[i]->moveCancel();
			_um->getVUnit()[i]->getX() -= _um->getVUnit()[i]->getSpeed();
			continue;
		}
	}

	for (int i = 0; i < _um->getVUnit().size(); ++i)
	{
		if (_um->getVUnit()[i]->getState() != WALK || _um->getVUnit()[i]->getTarget() != -1
			|| !_um->getVUnit()[i]->getReturn()) continue;
		_um->getVUnit()[i]->setDest(_sm->getIsoTile()[_um->getVUnit()[i]->getTileNum()].centerX,
			_sm->getIsoTile()[_um->getVUnit()[i]->getTileNum()].centerY);
		_um->getVUnit()[i]->getReturn() = false;
	}


	for (int i = 0; i < _um->getVUnit().size();++i)
	{ // 도달시 다음으로 넘겨주는 함수
		if (_um->getVUnit()[i]->getState() != WALK || _um->getVUnit()[i]->getTarget() != -1) continue;
		int tempTileNum = _um->getVUnit()[i]->getTileNum();
		RECT tempRc;
		RECT temp1 = RectMakeCenter(_um->getVUnit()[i]->getX(),
			_um->getVUnit()[i]->getY(), 4, 4);
		RECT temp2 = RectMakeCenter(_sm->getIsoTile()[tempTileNum].centerX,
			_sm->getIsoTile()[tempTileNum].centerY, 4, 4);
		if (IntersectRect(&tempRc, &temp1, &temp2))
		{	// 뒷번호부터 하는게 검사 덜함		
			for (int j = _um->getVUnit()[i]->getVPath().size()-1; j>=0; --j)
			{	//상하좌우 먼저검사함
				if (_um->getVUnit()[i]->getVPath()[j] == tempTileNum + 1
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum - 1
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum + 30
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum - 30)
				{
					tempTileNum = _um->getVUnit()[i]->getVPath()[j];
					_um->getVUnit()[i]->getTileNum() = tempTileNum;
					_um->getVUnit()[i]->setDest(_sm->getIsoTile()[tempTileNum].centerX, _sm->getIsoTile()[tempTileNum].centerY);
					_um->getVUnit()[i]->eraseVPath(j);
					break;
				}//대각선 검사함
				else if (_um->getVUnit()[i]->getVPath()[j] == tempTileNum + 29
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum + 31
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum - 29
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum - 31)
				{
					tempTileNum = _um->getVUnit()[i]->getVPath()[j];
					_um->getVUnit()[i]->getTileNum() = tempTileNum;
					_um->getVUnit()[i]->setDest(_sm->getIsoTile()[tempTileNum].centerX, _sm->getIsoTile()[tempTileNum].centerY);
					_um->getVUnit()[i]->eraseVPath(j);
					break;
				}
			}
		}
	}

}

void interaction::yoonghoRender()
{
}



inline POINT interaction::picking(long x, long y)
{
	int xx; int yy;
	if (2 * y < (x - 960))	return { -1,0 }; // y=1/2x보다 위에있는지 (맵밖 벗어남)
	if (2 * y < -(x - 960))	return { -1,0 }; // y=-1/2x보다 위에있는지 (맵밖 벗어남)
	xx = (2 * y + (x - 960)) / 64;
	if (xx > 29) return { -1,0 }; // 맵밖 벗어난거면 예외처리

	yy = (2 * y - (x - 960)) / 64;
	if (yy > 29) return { -1,0 };

	return { xx , yy };
}
