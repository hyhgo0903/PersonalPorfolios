#include "stdafx.h"
#include "unit.h"


void unit::commonUpdate()
{
	if (_stuck < 0)
	{
		++_stuck;
	}
	if (_stuck > 60 && _state == WALK)
	{ // 1초이상 맵에 끼이면 우회하는거(이땐 타겟팅을 안하고 원래 경로로 다시 감)
		_stuck = -120;
		_target = -1;
		int x = _tileNum % 30;
		int y = _tileNum / 30;
		setDest(960+(x-y)*32, (x+y)*16);
	}
	if (_stuck > 12 && (_state == ATTACK || _state == ATTACKWAIT) && _target != -1)
	{ // 무지막지하게 밀어내지는 않도록
		_stuck = 0;
		_x += _speed * cosf(_angle);
		_y -= _speed * sinf(_angle);
		RMC(); // 앞으로 이동시킴
	}

	if (_x < -100 || _x > MAPSIZEX + 100 || _y < -100 || _y > MAPSIZEY + 100)
	{
		_HP = 0;
	}

	if (_HP <= 0 && _state != DEAD)
	{
		_target = -1;
		setState(DEAD);
	}
	if (_delay > 0) --_delay;

	if (_frameCount < 6) ++_frameCount; // 0.1초마다
	else
	{
		_frameCount = 0;
		++_frame;
		if (_state != DEAD && _state != ATTACK && _frame > _maxFrame)
		{
			_frame = 0;
		}
		if (_state == ATTACK && _frame == _attackIndex && _target != -1)
		{
			_delay = _maxDelay;
			_attackReady = true;
		}
	}

	switch (_state)
	{
	case WALK:
		_x += _speed * cosf(_angle);
		_y -= _speed * sinf(_angle);
		RMC();
		break;
	case ATTACKWAIT:
		if (_target == -1)
		{
			_return = true;
			setState(WALK);
		}	
		if (_target != -1 && _delay <= 0)
		{
			setState(ATTACK);
		}
		break;
	case ATTACK:
		if (_frame > _maxFrame)
		{
			if (_target == -1)
			{
				_return = true;
				setState(WALK);
			}
			else	setState(ATTACKWAIT);
		}
		break;
	case DEAD:
		if (_frame >= _maxFrame)
		{
			_frame = _maxFrame;
			if (_deathDuration > 0) --_deathDuration;
			else _erase = true;
		}
		break;
	}
	_focusRc = RectMakeCenter(_x, _y, 300, 300);
}