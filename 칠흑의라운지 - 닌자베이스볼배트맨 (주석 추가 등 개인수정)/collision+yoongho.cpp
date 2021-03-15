#include "stdafx.h"
#include "collision.h"


void collision::yoonghoInit()
{
}

void collision::yoonghoUpdate()
{ // 아무도 잡히지 않았으면 풀음
	bool check = false;
	for (int i = 0; i < _em->getVEnemy().size(); ++i)
	{
		if (_pl->getEnumState() != GRAB) break;
		if (_em->getVEnemy()[i]->getState() == E_GRAB)
		{
			check = true;
			break;
		}
	}
	if (!check && _pl->getEnumState() == GRAB) _pl->setState(IDLE);
	
	// 잡거나 잡기스윙이 아니면 풀림
	if (_pl->getEnumState() != GRAB && _pl->getEnumState() != GRABSWING)
	{
		for (int i = 0; i < _em->getVEnemy().size(); ++i)
		{
			if (_em->getVEnemy()[i]->getState() == E_GRAB)
			{
				_em->getVEnemy()[i]->setState(E_WALK);
			}
		}
	}
}

void collision::yoonghoRender()
{
}
