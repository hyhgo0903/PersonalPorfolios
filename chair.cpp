#include "stdafx.h"
#include "chair.h"

chair::chair()
{
}

chair::~chair()
{
}

HRESULT chair::init(float x, float y)
{
	_x = x;	_y = y;
	_id = 0;
	_rc = RectMakeCenter(_x, _y, 233, 250);
	_img = IMAGEMANAGER->findImage("의자");
	_isFire = false;
	return S_OK;
}

void chair::release()
{
}

void chair::update()
{
}

void chair::render()
{
	// Rectangle(getMemDC(), _rc);
	_img->render(getMemDC(), _rc.left, _rc.top);
	// TextOut(getMemDC(), _rc.left, _rc.top, "난 의자", strlen("난 의자"));
}
