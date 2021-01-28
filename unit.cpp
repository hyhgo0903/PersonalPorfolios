#include "stdafx.h"
#include "unit.h"

unit::unit()
{
}

unit::~unit()
{
}

HRESULT unit::init(BELONG belong, float x, float y)
{
	return S_OK;
}

void unit::release()
{
}

void unit::update()
{
}

void unit::render()
{
}

void unit::progressBarRender()
{
	if (_state == DEAD) return;
	// 체력바 렌더하는거
	FINDIMG("체력바뒤")->resizedRender(getMemDC(), _rc.left - 5, _rc.top - 10, _width + 10, 6);
	if (_HP / _maxHP > 0.5f)
	{
		FINDIMG("초록피")->resizedRender(getMemDC(), _rc.left - 5, _rc.top - 10, (_width + 10) *_HP / _maxHP, 6);
	}
	else if (_HP / _maxHP > 0.3f)
	{
		FINDIMG("노랑피")->resizedRender(getMemDC(), _rc.left - 5, _rc.top - 10, (_width + 10) *_HP / _maxHP, 6);
	}
	else
	{
		FINDIMG("빨간피")->resizedRender(getMemDC(), _rc.left - 5, _rc.top - 10, (_width + 10) *_HP / _maxHP, 6);
	}
}

void unit::RMC()
{
	_rc = RectMakeCenter(_x, _y, _width, _height);
}

void unit::setDest(float destX, float destY)
{ // 목적지 설정해주면서 앵글도 바꿔주고
	// 앵글에 따른 프레임도 바꿔주는 함수
	_destX = destX;
	_destY = destY;
	_angle = getAngle(_x, _y, _destX, _destY);
	if (_angle < 0) _angle += PI2;
	_frameDirection = 10 - (int)((_angle + PI8) / PI4);
	_frameDirection %= 8;
}

void unit::setAngle(float angle)
{
	_angle = angle;
	if (_angle < 0) _angle += PI2;
	_frameDirection = 10 - (int)((_angle + PI8) / PI4);
	_frameDirection %= 8;
}
