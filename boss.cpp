#include "stdafx.h"
#include "boss.h"

boss::boss()
{
}

boss::~boss()
{
}

void boss::bossState()
{

}


HRESULT boss::init(float x, float y)
{
	_x = CAMX + x;	_y = CAMY + y;
	_currentHP = _maxHP = 500;
	_count = _index = _attackCount = 0;
	_bState = B_IDLE;
	_left = false;
	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	_rc = RectMakeCenter(_x, _y, 150, 150);
}

void boss::render()
{
	Rectangle(getMemDC(), _rc);
}
