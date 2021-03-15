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

	_shadow = RectMakeCenter(_x, _rc.bottom - 10, 110, 30);
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

	shadowRender(_shadow);

	//	Rectangle(getMemDC(), _rc);
	_img->render(getMemDC(), _rc.left, _rc.top);
	//	TextOut(getMemDC(), _rc.left, _rc.top, "쓰레기통", strlen("쓰레기통"));
}

void trashCan::shadowRender(RECT rc)
{
	HPEN pen = CreatePen(0, 2, RGB(80, 80, 80));
	HPEN oldpen = (HPEN)SelectObject(getMemDC(), pen);
	HBRUSH brush = CreateSolidBrush(RGB(80, 80, 80));
	HBRUSH oldbrush = (HBRUSH)SelectObject(getMemDC(), brush);

	Ellipse(getMemDC(), rc);

	SelectObject(getMemDC(), oldbrush);
	DeleteObject(brush);
	SelectObject(getMemDC(), oldpen);
	DeleteObject(pen);
}
