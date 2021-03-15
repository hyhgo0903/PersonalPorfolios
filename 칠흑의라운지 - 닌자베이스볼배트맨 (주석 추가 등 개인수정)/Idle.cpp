#include "stdafx.h"
#include "Idle.h"
#include "player.h"
void Idle::EnterState()
{
	//상태에 들어오면 각 상태마다 초기화를 해줍니다 
	//각각의 상태에 따라 이미지 재생을 위한 index를 초기화하거나 점프를 위한 jumpPower 초기화 등을 해줬습니다
	_pl->getJumpPower() = 15;
	
}

void Idle::updateState()
{
	count++;
	// 상하좌우 키입력을 하면 그걸 잠시 저장해둔 뒤
	// 30카운트가 지나면 저장한 값은 다시 0으로 초기화 됩니다
	// 30카운트(0.5초)지나기 전 재입력하면 달리는 상태가 되게 해줬습니다

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{ // (오른쪽을 1, 왼쪽2, 위3, 아래4로 저장합니다)
		if (_pl->getDirMemory() != 1) // 저장해놓은게 1이 아니라면
		{
			_pl->getDirMemory() = 1; // 지금 들어온게 오른쪽이라고 저장
			_pl->setState(WALK); // 걷도록 하였습니다
		}
		else // 저장해둔게 1이라면. 즉 1을 연달아 두번 누른 경우
		{
			_pl->setState(RUN); // 뛰도록 하였습니다
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

    if (_pl->getIsGrab())
    {
        _pl->setState(GRAB);
    }

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{	// 방향전환 카운트가 2번 쌓였고 Z를 눌렀을때 특수기
		if (_pl->getDirectionChanged() >= 2) _pl->setState(WINDMILL);
		//이외엔 일반 공격
		else 		_pl->setState(COMBO1);
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_pl->setState(JUMP);
	}

	if (count >= 120) // 카운트가 약 2초가 되면 대기모션으로 넘어가게 해줬습니다
	{
		_pl->setState(CIDLEANIMATION);
	}


}

void Idle::ExitState()
{
	count = 0; // 상태를 탈출할때 대기모션용 카운트를 초기화하게 했습니다.
}
