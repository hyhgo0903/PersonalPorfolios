#include "stdafx.h"
#include "groundEnemy.h"

HRESULT groundEnemy::init(int ID, float x, float y)
{
	commomInit();
	_arrived = _offGround = true;
	_state = IDLE;
	_ID = ID;		// 적의 종류
	_x = x; _y = y; _destX = GETCAM + 100 + rand()%650;
	_left = 1;
	_ySpd = 0.f;
	switch (_ID)
	{ // 0은 루돌프포로 1은 산타에리
	case 0: _currentHP = _maxHP = 100;	_width = 37; _height = 46; 	break;
	case 1: _currentHP = _maxHP = 100;	_width = 29; _height = 38; 	break;
	}
	_rc = RectMakeCenter(_x, _y, _width, _height);
	_hpBar = new progressBar;
	_hpBar->init(_width+20, 10);


	return S_OK;
}

void groundEnemy::release()
{
}

void groundEnemy::update()
{
	commonUpdate();
	pixelCollision();
	groundMove();
	_rc = RectMakeCenter(_x, _y, _width, _height);
	frameXUpdate();
	fireReady();
}

void groundEnemy::render()
{
	commonRender();
	stateRender();	
}

void groundEnemy::pixelCollision()
{
	if (_alphaValue < 255) return;
	_probeY = _rc.bottom;
	for (int i = _probeY - 4; i < _probeY + 8; ++i)
	{
		COLORREF color = GetPixel(FINDIMG("맵픽셀")->getMemDC(), _x, i);
		int r = GetRValue(color); int g = GetGValue(color); int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255) && _y > 0) // 착지한 상태면
		{	//Y축은 해당 픽셀값에서 높이만큼 뺀다
			_offGround = false;
			_ySpd = 0;
			_y = i - _height / 2;
			break;
		}
		if (_probeY + 7 == i) // 끝까지 갔는데 안착지한거
		{
			_ySpd -= GRAVITY;
		}
	}
	_y -= _ySpd;

}

void groundEnemy::frameXUpdate()
{
	if (_frameCount < 5) ++_frameCount;
	else
	{
		_frameCount = 0;
		if (_left <1) ++_frameX;
		else --_frameX;
	}
	if (_ID == 0 && _left < 1) // 0이고 오른쪽 -> 프레임이 올라간다 0으로 초기화
	{
		switch (_state)
		{
		case IDLE: if (_frameX > 9) _frameX = 0;	break; // 프레임10개
		case WALK: if (_frameX > 11) _frameX = 0;	break;
		case ATTACK:
			if (_frameX > 20)
			{
				_state = IDLE;
				stateChange();
			}
			break;
		}
	}
	else if (_ID == 1 && _left < 1) // 1이고 오른쪽 -> 프레임이 올라간다 0으로 초기화
	{
		switch (_state)
		{
		case IDLE:if (_frameX > 3) _frameX = 0;	break; // 프레임10개
		case WALK: if (_frameX > 11) _frameX = 0;	break;
		case ATTACK:
			if (_frameX > 8)
			{
				_state = IDLE;
				stateChange();
			}
			break;
		}
	}
	else if (_ID == 0 && _left > 0 && _frameX < 0) // 0이고 왼쪽 ->프레임이 내려간다 알맞게 초기화
	{
		switch (_state)
		{
		case IDLE: _frameX = 9;		break;
		case WALK:_frameX = 11;		break;
		case ATTACK:_state = IDLE; stateChange();	break;
		}
	}
	else if (_ID == 1 && _left > 0 && _frameX < 0)
	{
		switch (_state)
		{
		case IDLE: _frameX = 3;		break;
		case WALK:_frameX = 11;		break;
		case ATTACK:_state = IDLE; stateChange();	break;
		}
	}
}

// 상태 바뀔때마다 소환할 것. 상태 바꿀때 초기 프레임 맞춰주는 함수
void groundEnemy::stateChange()
{
	if (_left < 1)
	{
		_frameX = 0;
		return;
	}
	switch (_ID)
	{
	case 0:
		switch (_state)
		{		
		case IDLE:			_frameX = 9;	break;
		case WALK:		_frameX = 11;	break;
		case ATTACK:			_frameX = 20;	break;
		}
		break;
	case 1:
		switch (_state)
		{
		case IDLE:		_frameX = 3;	break;
		case WALK:		_frameX = 11;	break;
		case ATTACK:	_frameX = 8;	break;
		}
		break;
	}
}


void groundEnemy::fireReady() // 공격자세의 특정프레임에 도달했을때에 준비가 됨
{
	switch (_ID)
	{
	case 0:
		if (_duration > 10 && _state == ATTACK && _left < 1 && _frameX == 12)
		{
			_duration = 0;
			++_fireReady;
		}
		if (_duration > 10 && _state == ATTACK && _left > 0 && _frameX == 7)
		{
			_duration = 0;
			++_fireReady;
		}
		break;
	case 1:
		if (_duration > 10 && _state == ATTACK && _left<1 && _frameX == 5)
		{
			_duration = 0;
			++_fireReady;
		}
		if (_duration > 10 && _state == ATTACK && _left > 0 && _frameX == 4)
		{
			_duration = 0;
			++_fireReady;
		}
		break;
	}
}

void groundEnemy::groundMove()
{
	if (_alphaValue < 255 || _offGround)
	{ // 죽는놈은 이동안함
		_state = IDLE;
		stateChange();
		return;
	}	
	// 화면 왼쪽끝이면 붙여줌
	if (_rc.right < GETCAM) _x = GETCAM - _width / 2;

	if (_duration < 200 && _state != ATTACK &&
		(_destX - _x >= 10 || _destX - _x <= -10))
	{
		if (_destX < _x) _left = 1;
		else _left = 0;
		if (_state != WALK)
		{
			_state = WALK;
			stateChange();
		}
		if (_left) _x -= 3;
		if (!_left) _x += 3;
	}
	if (_duration < 200 && _state != ATTACK &&
		(_destX - _x < 10 && _destX - _x > -10))
	{
		if (_playerX < _x) _left = 1;
		else _left = 0;
		if (_state != IDLE)
		{
			_state = IDLE;
			stateChange();
		}
	}
	if (_duration >= 200)
	{
		if (_playerX < _x) _left = 1;
		else _left = 0;
		if (_state != ATTACK)
		{
			_state = ATTACK;
			stateChange();
		}
		_duration = 0;
		_destX = GETCAM + 100 + rand() % 650;
	}
}