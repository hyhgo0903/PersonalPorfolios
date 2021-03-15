#include "stdafx.h"
#include "psionic.h"

psionic::psionic()
{
}

psionic::~psionic()
{
}

HRESULT psionic::init(S_BELONG belong, float x, float y)
{
	_ID = 1;
	_belong = belong;
	_x = x; _y = y;
	_rc = RectMakeCenter(_x, _y, 167, 130);
	_image = FINDIMG("사이오닉스톰");
	_maxFrame = _image->getMaxFrameX();
	_duration = 300;

	commonInit();

	return S_OK;
}

void psionic::release()
{
	SAFE_DELETE(_image);
}

void psionic::update()
{
	commonUpdate();
}

void psionic::render()
{
	_image->frameRender(getMemDC(), _rc.left-9, _rc.top-10, _frame, 0);
}
