#include "stdafx.h"
#include "narutoEffect.h"

HRESULT narutoEffect::init(S_BELONG belong, float x, float y)
{
    _ID = 5;
    _belong = belong;
    _x = x; _y = y;
    _rc = RectMakeCenter(_x, _y, 64, 64);
    _image = FINDIMG("³ª¼±È¯");
    _maxFrame = _image->getMaxFrameX();
    _duration = 114;

    commonInit();
    return S_OK;
}

void narutoEffect::release()
{
    SAFE_DELETE(_image);
}

void narutoEffect::update()
{
    commonUpdate();
}

void narutoEffect::render()
{
    _image->frameRender(getMemDC(), _rc.left, _rc.top, _frame, 0);
}
