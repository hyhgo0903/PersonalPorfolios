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
	_rc = RectMakeCenter(_x, _y, 100, 70);
	_chairRect = RectMakeCenter(_x, _y, 100, 70);
	_img = IMAGEMANAGER->findImage("의자");
	_isFire = true;
	_isBossOn = false;
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
	_img->render(getMemDC(), _rc.left - 50, _rc.top - 60);
	// TextOut(getMemDC(), _rc.left, _rc.top, "난 의자", strlen("난 의자"));
	if (KEYMANAGER->isToggleKey('O'))
	{
		//Rectangle(getMemDC(), _chairRect);
		Rectangle(getMemDC(), _rc);
	}
}
