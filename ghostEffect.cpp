#include "stdafx.h"
#include "ghostEffect.h"

HRESULT ghostEffect::init(S_BELONG belong, float x, float y)
{
	_ID = 6;
	_belong = belong;
	_x = x; _y = y;
	_rc = RectMakeCenter(_x, _y, 35, 33);
	_image = FINDIMG("°í½ºÆ®Æã");
	_maxFrame = _image->getMaxFrameX();
	_duration = 60;

	commonInit();

	return S_OK;
}

void ghostEffect::release()
{
	SAFE_DELETE(_image);
}

void ghostEffect::update()
{
	commonUpdate();
}

void ghostEffect::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame, 0);
}
