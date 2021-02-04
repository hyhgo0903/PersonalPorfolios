#include "stdafx.h"
#include "fire.h"

HRESULT fire::init(S_BELONG belong, float x, float y)
{
	_ID = 4;
	_belong = belong;
	_x = x; _y = y;
	_rc = RectMakeCenter(_x, _y, 32, 32);
	_image = FINDIMG("บา");
	_maxFrame = _image->getMaxFrameX();
	_duration = 54;

	commonInit();
	return S_OK;
}

void fire::release()
{
	SAFE_DELETE(_image);
}

void fire::update()
{
	commonUpdate();
}

void fire::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame, 0);
}
