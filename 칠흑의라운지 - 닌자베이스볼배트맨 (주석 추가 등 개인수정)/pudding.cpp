#include "stdafx.h"
#include "pudding.h"
HRESULT pudding::init(float x, float y)
{
	_image = FINDIMG("Çªµù");
	_x = _xg = x;
	_y = y;
	_yg = _y + 50;
	_distance = _yg - _y;
	int shadowWidth = _image->getWidth() - (_distance / 2);
	int shadowHeight = (_image->getHeight() - (_distance / 2)) / 3;

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_rcg = RectMakeCenter(_xg, _yg, _image->getWidth(), _image->getHeight());
	_shadow = RectMakeCenter(_xg, _rcg.bottom, shadowWidth, shadowHeight);

	_delete = false;
	_gravity = 2;
	_food = true;

	return S_OK;
}

HRESULT pudding::init(float x, float y, float bottom)
{
	_image = FINDIMG("Çªµù");
	_x = _xg = x;
	_y = y;
	_yg = bottom - _image->getHeight() * 2 / 3;
	_distance = _yg - _y;
	int shadowWidth = _image->getWidth() - (_distance / 2);
	int shadowHeight = (_image->getHeight() - (_distance / 2)) / 3;

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_rcg = RectMakeCenter(_xg, _yg, _image->getWidth(), _image->getHeight());
	_shadow = RectMakeCenter(_xg, _rcg.bottom, shadowWidth, shadowHeight);

	_delete = false;
	_gravity = 2;
	_food = true;
	_movement = 0;
	return S_OK;
}

void pudding::release()
{
}

void pudding::update()
{
	_distance = _yg - _y;
	int shadowWidth = _image->getWidth() - (_distance / 2);
	int shadowHeight = (_image->getHeight() - (_distance / 2)) / 3;
	_shadow = RectMakeCenter(_xg, _rcg.bottom, shadowWidth, shadowHeight);
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	drop();

}

void pudding::render()
{
	shadowRender(_shadow);
	_image->render(getMemDC(), _rc.left, _rc.top);
}

void pudding::drop()
{
	if (_yg > _y)
	{
		_gravity -= 0.2f;
		_y -= _gravity;
		_x += _movement;
		_xg += _movement;
	}
	else _y = _yg;
}

void pudding::setHold()
{
	_delete = true;
}