#include "stdafx.h"
#include "thunder.h"

thunder::thunder()
{
}

thunder::~thunder()
{
}

HRESULT thunder::init(S_BELONG belong, float x, float y)
{

	_ID = 3;
	_belong = S_ENEMY;
	_x = x; _y = y;
	_rc = RectMakeCenter(_x, _y, 30, 300);
	_image = FINDIMG("¹ø°³ ÀÌÆåÆ®");
	_maxFrame = _image->getMaxFrameX();

	commonInit();

	_isOnce = true;
	_duration = 0;
	return S_OK;
}

void thunder::release()
{
	SAFE_DELETE(_image);
}

void thunder::update()
{
	commonUpdate();
}

void thunder::render()
{
	// Rectangle(getMemDC(), _rc);
	_image->frameRender(getMemDC(), _rc.left - 40, _rc.top, _frame, 0);
}
