#include "stdafx.h"
#include "playerManager.h"

void playerManager::animationUpdate()
{
	if (_tank.aniCount < 6) _tank.aniCount++; // 60될떄마다 1초니까 6될때마다면 0.1초마다 갱신
	else
	{
		_tank.aniCount = 0;
		switch (_tank.type)
		{
		case CANNON:
			switch (_tank.state)
			{
			case RIGHTIDLE: ++_tank.frameX;			if (_tank.frameX >= 39) _tank.frameX = 0; break;
			case RIGHTRUN: ++_tank.frameX;			if (_tank.frameX >= 7) _tank.frameX = 0; break;
			case RIGHTATTACK: ++_tank.frameX;
				if (_tank.frameX >= 5)
				{	_tank.state = RIGHTIDLE; stateChange();	}	break;
			case LEFTIDLE: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 38; break;
			case LEFTRUN: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 6; break;
			case LEFTATTACK: --_tank.frameX;		
				if (_tank.frameX < 0) { _tank.state = LEFTIDLE;	stateChange(); }	break;
			}
			break;
		case MISSILE:
			switch (_tank.state)
			{
			case RIGHTIDLE: ++_tank.frameX;			if (_tank.frameX >= 24) _tank.frameX = 0; break;
			case RIGHTRUN: ++_tank.frameX;			if (_tank.frameX >= 4) _tank.frameX = 0; break;
			case RIGHTATTACK: ++_tank.frameX;
				if (_tank.frameX >= 7)
				{
					_tank.state = RIGHTIDLE; stateChange();
				}	break;
			case LEFTIDLE: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 23; break;
			case LEFTRUN: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 3; break;
			case LEFTATTACK: --_tank.frameX;
				if (_tank.frameX < 0) { _tank.state = LEFTIDLE;	stateChange(); }	break;
			}
			break;
		case MULTI:
			switch (_tank.state)
			{
			case RIGHTIDLE: ++_tank.frameX;			if (_tank.frameX >= 10) _tank.frameX = 0; break;
			case RIGHTRUN: ++_tank.frameX;			if (_tank.frameX >= 8) _tank.frameX = 0; break;
			case RIGHTATTACK: ++_tank.frameX;
				if (_tank.frameX >= 13)
				{
					_tank.state = RIGHTIDLE; stateChange();
				}	break;
			case LEFTIDLE: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 9; break;
			case LEFTRUN: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 7; break;
			case LEFTATTACK: --_tank.frameX;
				if (_tank.frameX < 0) { _tank.state = LEFTIDLE;	stateChange(); }	break;
			}
			break;
		case SUPER:
			switch (_tank.state)
			{
			case RIGHTIDLE:
			case RIGHTRUN: ++_tank.frameX;			if (_tank.frameX >= 7) _tank.frameX = 0; break;
			case RIGHTATTACK: ++_tank.frameX;
				if (_tank.frameX >= 8)
				{
					_tank.state = RIGHTIDLE; stateChange();
				}	break;
			case LEFTIDLE:
			case LEFTRUN: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 6; break;
			case LEFTATTACK: --_tank.frameX;
				if (_tank.frameX < 0) { _tank.state = LEFTIDLE;	stateChange(); }	break;
			}
			break;
		}
	}
}

// 상태 바뀔때마다 소환할 것. 상태 바꿀때 초기 프레임 맞춰주는 함수
void playerManager::stateChange()
{
	switch (_tank.type)
	{
	case CANNON:
		switch (_tank.state)
		{
		case RIGHTIDLE:			case RIGHTRUN:
		case RIGHTATTACK:		_tank.frameX = 0;	break;
		case LEFTIDLE:			_tank.frameX = 38;	break;
		case LEFTRUN:			_tank.frameX = 6;	break;
		case LEFTATTACK:		_tank.frameX = 4;	break;
		}
		break;
	case MISSILE:
		switch (_tank.state)
		{
		case RIGHTIDLE:			case RIGHTRUN:
		case RIGHTATTACK:		_tank.frameX = 0;	break;
		case LEFTIDLE:			_tank.frameX = 23;	break;
		case LEFTRUN:			_tank.frameX = 3;	break;
		case LEFTATTACK:		_tank.frameX = 6;	break;
		}
		break;
	case MULTI:
		switch (_tank.state)
		{
		case RIGHTIDLE:			case RIGHTRUN:	_tank.frameX = 0; break;
		case RIGHTATTACK:		_tank.frameX = 5;	break;
		case LEFTIDLE:			_tank.frameX = 9;	break;
		case LEFTRUN:			_tank.frameX = 7;	break;
		case LEFTATTACK:		_tank.frameX = 7;	break;
		}
		break;
	case SUPER:
		switch (_tank.state)
		{
		case RIGHTIDLE:			case RIGHTRUN:
		case RIGHTATTACK:		_tank.frameX = 0;	break;
		case LEFTIDLE:	case LEFTRUN:	_tank.frameX = 6;	break;
		case LEFTATTACK:		_tank.frameX = 7;	break;
		}
		break;
	}
}