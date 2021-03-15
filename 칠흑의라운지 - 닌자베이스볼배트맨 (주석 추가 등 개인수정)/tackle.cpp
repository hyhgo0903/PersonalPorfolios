#include "stdafx.h"
#include "tackle.h"
#include "player.h"
#define GRAVITY 0.6f
void tackle::EnterState()
{
    _pl->getJumpPower() = 20;
	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().right + 50, _pl->getGroundRc().top); }
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().left - 200, _pl->getGroundRc().top); }
}

void tackle::updateState()
{
    _pl->getJumpPower() -= GRAVITY;
    _pl->getGroundX() = _pl->getFlyX();
    if (!_pl->getLeft()) // 앞으로 쭉 밀려나가다 점점 속도가 감소하는거처럼 보이게 만들었습니다
    {
        _pl->getFlyX() += _pl->getJumpPower();
		if (_pl->getFlyX() >= _pl->getGroundX())
		{
			_pl->getGroundX() = _pl->getFlyX();
		}
    }
    if (_pl->getLeft())
    {
        _pl->getFlyX() -= _pl->getJumpPower();
		if (_pl->getFlyX() <= _pl->getGroundX())
		{
			_pl->getGroundX() = _pl->getFlyX();
		}
    }

    if (_pl->getJumpPower() <= 0)
    {
        _pl->setState(IDLE);
    }
}

void tackle::ExitState()
{
    _pl->getIndex() = 0;
}
