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
			if (_vUnit[i]->getTarget() != -1 || _vUnit[j]->getState() == DEAD ||
				_vUnit[i]->getStuck() < 0) continue;
			if (_vUnit[i]->getBelong() == _vUnit[j]->getBelong()) continue; // 적아군구분
			if (IntersectRect(&temp, &_vUnit[j]->getRect(), &_vUnit[i]->getFocusRect()) && _vUnit[i]->getStuck() >= 0
				&& _vUnit[i]->getTarget() == -1)
			{ // 감지렉트에 온 경우 타겟팅이랑 목표를 그쪽으로
				_vUnit[i]->getTarget() = j;
				_vUnit[i]->setDest(_vUnit[j]->getX(), _vUnit[j]->getY());
				break;
			}
		}

		// 유닛과유닛 렉트충돌
		for (int j = 0; j < _vUnit.size(); ++j)
		{ // 끼어있는애는 지위치 찾을떄까지 충돌하지 말도록 컨티뉴해놨음
			if (_vUnit[i]->getState() != WALK || _vUnit[j]->getState() == DEAD || i==j
				|| _vUnit[i]->getStuck() < 0 || _vUnit[j]->getStuck() < 0) continue;
			if (IntersectRect(&temp, &_vUnit[j]->getRect(), &_vUnit[i]->getRect()))
			{ // 그냥 렉트간 충돌
				if (_vUnit[i]->getBelong() != _vUnit[j]->getBelong())
				{ // 소속다른데 어깨빵당하면 서로 싸우게했음.
					_vUnit[i]->getTarget() = j;
					_vUnit[j]->getTarget() = i;
				}				
				_vUnit[i]->moveCancel();
				_vUnit[i]->RMC();
				if (IntersectRect(&temp, &_vUnit[j]->getRect(), &_vUnit[i]->getRect()))
				{ // 이동취소해도 여전히 인터섹트한다면 (j를 취소해야함)
					_vUnit[i]->getX() += _vUnit[i]->getSpeed() * cosf(_vUnit[i]->getAngle1());
					_vUnit[i]->getY() -= _vUnit[i]->getSpeed() * sinf(_vUnit[i]->getAngle1());
					_vUnit[i]->RMC();
					_vUnit[j]->moveCancel();
					_vUnit[j]->RMC();
				}
				if (_vUnit[i]->getBelong() == _vUnit[j]->getBelong())
				{ // 같은팀이 밀면 원래 진행방향으로 좀 밀리게 해봤음
					_vUnit[j]->getStuck() += 1;
				}
				break;
			}
		}
	}
}

