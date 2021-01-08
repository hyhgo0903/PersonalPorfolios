#include "stdafx.h"
#include "boss.h"

boss::boss()
{
}

boss::~boss()
{
}

HRESULT boss::init(float x, float y)
{
	_x = CAMX+x;	_y = CAMY + y;
	_currentHP = _maxHP = 500;
	_rc=RectMakeCenter(_x, _y, 100, 100);
	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	move();
}

void boss::render()
{
	Rectangle(getMemDC(), _rc);
	TextOut(getMemDC(), _rc.left, _rc.top, "난 보스", strlen("난 보스"));
}

void boss::move()
{ // 심심해서 부들부들 넣었으니 없애도 무방
	_y += rand()%11 -5;
	if (_y > CAMY + WINSIZEY || _y < CAMY) _y = CAMY + WINSIZEY/2;
	_rc = RectMakeCenter(_x, _y, 100, 100);
}
