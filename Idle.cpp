#include "stdafx.h"
#include "Idle.h"
#include "player.h"
void Idle::EnterState()
{
	// 방향에따라 이미지넣고 인덱스 대충 초기화해줌
	//_player->setMainImg("전령일반상태");
    _pl->getJumpPower() = 15;
	
}

void Idle::updateState()
{
	// 상하좌우 키입력을 하면 그걸 잠시 저장해둬.
	// 30카운트가 지나면 저장한 값은 다시 0으로 초기화돼.
	// 허나, 30카운트(0.5초)지나기 전 그걸 다시 누르면 걷지 않고 뛰도록 설정해뒀어
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_pl->getDirMemory() != 1) // 저장해놓은게 1이 아니라면
		{
			_pl->getDirMemory() = 1; // 지금 들어온게 오른쪽이라고 저장
			_pl->setState(WALK); // 걷도록 하였음
		}
		else // 저장해둔게 1이라면. 즉 1을 연달아 두번 누른 경우야
		{
			_pl->setState(RUN); // 뛰도록 하였음
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_pl->getDirMemory() != 2)
		{
			_pl->getDirMemory() = 2;
			_pl->setState(WALK);
		}
		else
		{
			_pl->setState(RUN);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_pl->getDirMemory() != 3)
		{
			_pl->getDirMemory() = 3;
			_pl->setState(WALK);
		}
		else
		{
			_pl->setState(RUN);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_pl->getDirMemory() != 4)
		{
			_pl->getDirMemory() = 4;
			_pl->setState(WALK);
		}
		else
		{
			_pl->setState(RUN);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_pl->setState(COMBO1);
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_pl->setState(JUMP);
	}
}

void Idle::ExitState()
{

}
