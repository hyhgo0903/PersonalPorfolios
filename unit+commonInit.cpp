#include "stdafx.h"
#include "unit.h"

void unit::commonInit()
{
	// int
	_frameCount = _frame = _delay = _frameDirection = _tileNum = _stuck = 0;
	_deathDuration = 180; // 죽은다음 시체지속시간. 기본값은 3초인데 유닛에따라 줄일수있음(템플러참고)
	_target = -1; // 없는 상태면 -1
	// float
	if (_belong == PLAYER) setAngle(0.f);
	else setAngle(PI);
	// bool
	_attackReady = _erase = _active = _return = false;
	_state = ATTACKWAIT; // 이거 안하면 처음에 WALK로 안하니 이미지를 못넣어서 터짐	
	setState(WALK);		// 셋스테이트때매 워크로 바뀌니 놀라지말것..

	_rc = RectMakeCenter(_x, _y, _width, _height);
	setDest(_x, _y);
	_HP = _maxHP;
}