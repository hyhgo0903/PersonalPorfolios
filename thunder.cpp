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
	_rc = RectMakeCenter(_x + 5, _y - 250, 30, 30);
	_image = FINDIMG("¹ø°³ ÀÌÆåÆ®");
	_maxFrame = _image->getMaxFrameX();
	_duration = 130;

	commonInit();

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
	_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 10, _frame, 0);
}
