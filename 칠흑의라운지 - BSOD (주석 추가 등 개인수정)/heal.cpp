#include "stdafx.h"
#include "heal.h"

HRESULT heal::init(S_BELONG belong, float x, float y)
{
	_ID = 2;
	_belong = belong;
	_x = x; _y = y;
	_rc = RectMakeCenter(_x, _y, 96, 96);
	_image = FINDIMG("Èú");
	_maxFrame = _image->getMaxFrameX();
	_duration = 252;

	commonInit();
	return S_OK;
}

void heal::release()
{
	SAFE_DELETE(_image);
}

void heal::update()
{
	commonUpdate();
}

void heal::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame, 0);
}
