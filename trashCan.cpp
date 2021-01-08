#include "stdafx.h"
#include "trashCan.h"

trashCan::trashCan()
{
}

trashCan::~trashCan()
{
}

HRESULT trashCan::init(float x, float y)
{
	_x = x; _y = y;
	_id = 1; // 부여받은 id ()
	_rc = RectMakeCenter(_x, _y, 110, 150);
	_img = IMAGEMANAGER->findImage("쓰레기통");
	_isFire = true;
	return S_OK;
}

void trashCan::release()
{
}

void trashCan::update()
{
}

void trashCan::render()
{
//	Rectangle(getMemDC(), _rc);
	_img->render(getMemDC(), _rc.left,  _rc.top);
//	TextOut(getMemDC(), _rc.left, _rc.top, "쓰레기통", strlen("쓰레기통"));
}
