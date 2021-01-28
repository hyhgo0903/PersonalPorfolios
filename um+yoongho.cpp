#include "stdafx.h"
#include "unitManager.h"

void unitManager::yoonghoUpdate()
{
	for (int i = 0; i < _vUnit.size(); ++i)
	{
		if (_vUnit[i]->getState() == DEAD) continue;
		RECT temp;

		// 감지범위 적발견시 타겟팅
		for (int j = 0; j < _vUnit.size(); ++j)
		{
			if (_vUnit[i]->getTarget() != -1 || _vUnit[j]->getState() == DEAD) continue;
			if (_vUnit[i]->getBelong() == _vUnit[j]->getBelong()) continue; // 적아군구분
			if (IntersectRect(&temp, &_vUnit[j]->getRect(), &_vUnit[i]->getFocusRect()) &&
				_vUnit[i]->getTarget() == -1)
			{ // 감지렉트에 온 경우 타겟팅이랑 목표를 그쪽으로
				_vUnit[i]->getTarget() = j;
				_vUnit[i]->setDest(_vUnit[j]->getX(), _vUnit[j]->getY());
				break;
			}
		}

		// 유닛과유닛 렉트충돌
		if (_vUnit[i]->getID() == 1 || _vUnit[i]->getID() == 3) continue; // 일단 근접유닛간 충돌은 막아둠
		for (int j = 0; j < _vUnit.size(); ++j)
		{// 타겟팅하는 포문(타겟 없는놈 대상)
			if (_vUnit[j]->getState() == DEAD) continue;
			if (IntersectRect(&temp, &_vUnit[j]->getRect(), &_vUnit[i]->getRect()))
			{ // 그냥 렉트간 충돌
				if (_vUnit[i]->getBelong() != _vUnit[j]->getBelong())
				{ // 소속다른데 어깨빵당하면 서로 싸우게했음.
					_vUnit[i]->getTarget() = j;
					_vUnit[j]->getTarget() = i;
				}
				int widthHalf = (temp.right - temp.left)/2;
				int heightHalf = (temp.bottom - temp.top)/2;
				if (widthHalf > heightHalf)
				{ // 위아래로 부딪힌 경우임
					if (_vUnit[i]->getY() < _vUnit[j]->getY())
					{
						_vUnit[i]->getY() -= heightHalf;
						_vUnit[j]->getY() += heightHalf;
					} // 서로 반씩 미는걸로 해봄
					else if(_vUnit[i]->getY() > _vUnit[j]->getY())
					{
						_vUnit[i]->getY() += heightHalf;
						_vUnit[j]->getY() -= heightHalf;
					}
				}
				else if (widthHalf < heightHalf)
				{
					if (_vUnit[i]->getX() < _vUnit[j]->getX())
					{
						_vUnit[i]->getX() -= widthHalf;
						_vUnit[j]->getX() += widthHalf;
					}
					else if(_vUnit[i]->getX() > _vUnit[j]->getX())
					{
						_vUnit[i]->getX() += widthHalf;
						_vUnit[j]->getX() -= widthHalf;
					}
				}
				_vUnit[i]->RMC();
				_vUnit[j]->RMC();
			}
		}
	}
}

