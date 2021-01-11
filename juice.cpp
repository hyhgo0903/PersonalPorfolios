#include "stdafx.h"
#include "juice.h"
HRESULT juice::init(float x, float y)
{
	_image = FINDIMG("주스");
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

HRESULT juice::init(float x, float y, float bottom)
{
	_image = FINDIMG("주스");
	_x = _xg = x;
	_y = y;
	_yg = bottom;
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

//HRESULT juice::init(float x, float y, float bottom)
//{
//	_image = FINDIMG("피자");
//	_x = _xg = x;
//	_y = y;
//	_yg = bottom - (_image->getHeight()/2);
//	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
//	_rcg = RectMakeCenter(_xg, _yg, _image->getWidth(), _image->getHeight());
//
//	int shadowWidth = _image->getWidth() - (_distance / 2);
//	int shadowHeight = (_image->getHeight() - (_distance / 2)) / 3;
//	_shadow = RectMakeCenter(_xg, _rcg.bottom, shadowWidth, shadowHeight);
//
//	_food = true;
//	_gravity = 3;
//	_gravity = 2;
//	return S_OK;
//}

void juice::release()
{
}

void juice::update()
{
	_distance = _yg - _y;
	int shadowWidth = _image->getWidth() - (_distance / 2);
	int shadowHeight = (_image->getHeight() - (_distance / 2)) / 3;
	_shadow = RectMakeCenter(_xg, _rcg.bottom, shadowWidth, shadowHeight);
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	drop();

}

void juice::render()
{
	shadowRender(_shadow);
	_image->render(getMemDC(), _rc.left, _rc.top);
}

void juice::drop()
{
	if (_yg > _y)
	{
		_gravity -= 0.2f;
		_y -= _gravity;
	}
	else _y = _yg;
}

void juice::setHold()
{
	_delete = true;
}

