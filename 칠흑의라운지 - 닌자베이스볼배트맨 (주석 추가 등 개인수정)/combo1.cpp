#include "stdafx.h"
#include "combo1.h"
#include "player.h"

void combo1::EnterState()
{
	//상태에 들어오면 정상적인 프레임 이미지 작동을 위해 index 수치를 초기화해줍니다.
	_pl->getIndex() = 0;
	// 오른쪽이면 오른쪽부터 공격 범위만큼 공격 렉트를 생성하게
	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().right, _pl->getGroundRc().top); }
	// 왼쪽이면 왼쪽부터 공격 범위만큼 빼서 생성하게했습니다.
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().left - 150, _pl->getGroundRc().top); }
}

void combo1::updateState()
{
	
	//방향키를 입력한 채로 Z키를 누르면 콤보 2행으로, 아니면 1행으로 이동하게 했습니다.

    if ((KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)) && KEYMANAGER->isOnceKeyDown('Z'))
    {
        _pl->setState(COMBO21);
    }

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_pl->setState(COMBO11);
	}

}

void combo1::ExitState()
{
}
