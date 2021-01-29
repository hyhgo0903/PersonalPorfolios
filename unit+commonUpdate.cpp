#include "stdafx.h"
#include "unit.h"


void unit::commonUpdate()
{
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

	if (_frameCount < 6) ++_frameCount; // 0.1ÃÊ¸¶´Ù
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
		if (_target == -1) setState(WALK);
		if (_target != -1 && _delay <= 0)
		{
			setState(ATTACK);
		}
		break;
	case ATTACK:
		if (_frame >= _maxFrame)
		{
			if (_target == -1)	setState(WALK);
			else		setState(ATTACKWAIT);
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