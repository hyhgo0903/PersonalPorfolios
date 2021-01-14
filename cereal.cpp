#include "stdafx.h"
#include "cereal.h"
HRESULT cereal::init(float x, float y)
{
	_image = FINDIMG("¾¾¸®¾ó");
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

HRESULT cereal::init(float x, float y, float bottom)
{
	_image = FINDIMG("¾¾¸®¾ó");
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
	_movement = 0;
	_food = true;

	return S_OK;
}

//HRESULT cereal::init(float x, float y, float bottom)
//{
//	_image = FINDIMG("ÇÇÀÚ");
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

void cereal::release()
{
}

void cereal::update()
{
	_distance = _yg - _y;
	int shadowWidth = _image->getWidth() - (_distance / 2);
	int shadowHeight = (_image->getHeight() - (_distance / 2)) / 3;
	_shadow = RectMakeCenter(_xg, _rcg.bottom, shadowWidth, shadowHeight);
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	drop();

}

void cereal::render()
{
	shadowRender(_shadow);
	_image->render(getMemDC(), _rc.left, _rc.top);
}

void cereal::drop()
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

void cereal::setHold()
{
	_delete = true;
}

