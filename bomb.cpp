#include "stdafx.h"
#include "bomb.h"

HRESULT bomb::init(float x, float y)
{
	_image = IMAGEMANAGER->findImage("ÆøÅº");
	_image->setFrameX(0);
	_image->setFrameY(0);
	_gravity = 3;
	_x = x;	_y = y;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());//°øÁß·ºÆ®
	_pickup = false;
	_moving = false;

	_xg = _x;
	_yg = _y + 70;
	_rcg = RectMakeCenter(_xg, _yg, _image->getFrameWidth(), _image->getFrameHeight());//¶¥·ºÆ®
	_distance = _yg - _y;
	_shadow = RectMakeCenter(_xg, _rcg.bottom, _image->getFrameWidth() - (_distance / 2), (_image->getFrameHeight() - (_distance / 2) / 3));
	_time = 0;
	_delete = false;
	
	_index = 0;
	_indexTime = 0;

	_ID = 2;
	_food = false;
	
	return S_OK;
}

HRESULT bomb::init(float x, float y, float bottom)
{
	_image = IMAGEMANAGER->findImage("ÆøÅº");
	_image->setFrameX(0);
	_image->setFrameY(0);
	_gravity = 3;
	_x = x;	_y = y;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());//°øÁß·ºÆ®
	_pickup = false;
	_moving = false;

	_xg = _x;
	_yg = bottom - _image->getHeight()*2 / 3;
	_rcg = RectMakeCenter(_xg, _yg, _image->getFrameWidth(), _image->getFrameHeight());//¶¥·ºÆ®
	_distance = _yg - _y;
	_shadow = RectMakeCenter(_xg, _rcg.bottom, _image->getFrameWidth() - (_distance / 2), (_image->getFrameHeight() - (_distance / 2) / 3));
	_time = 0;
	_delete = false;

	_index = 0;
	_indexTime = 0;

	_ID = 2;
	_food = false;
	_movement = 0;
	return S_OK;
}

void bomb::release()
{
}

void bomb::update()
{
	_ID = 2;
	if (!_moving && !_pickup)
	{
		drop();
	}
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_distance = _yg - _y;

	int shadowWidth = _image->getFrameWidth() - (_distance / 2);
	int shadowHeight = (_image->getFrameHeight() / 3) - (_distance / 6);
	if (shadowWidth <= 0) shadowWidth = 0;
	if (shadowHeight <= 0)shadowHeight = 0;

	_shadow = RectMakeCenter(_xg, _rcg.bottom, shadowWidth, shadowHeight);
	
	_indexTime += TIMEMANAGER->getElapsedTime();
	if (_pickup)
	{
		_xg = _x;//¶¥·ºÆ®
		_rcg = RectMakeCenter(_xg, _yg, _image->getWidth(), _image->getHeight());//¶¥·ºÆ®
	}
	if (_moving)
	{
		_xg = _x;//¶¥·ºÆ®
		_rcg = RectMakeCenter(_xg, _yg, _image->getWidth(), _image->getHeight());//¶¥·ºÆ®
	}
}

void bomb::render()
{
	fillColorEllipse(80, 80, 80, _shadow);
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
}

void bomb::attackMove(bool direction)
{
	if (_pickup)_gravity = 5;
	drop(0.5f);
	_pickup = false;
	_moving = true;
	_direction = direction;
	if (_y < _yg)
	{
		reverseFraming();
		if (_direction == true)
		{
			_x += 9.7f;
			_xg += 9.7f;
		}
		else
		{
			_x -= 9.7f;
			_xg -= 9.7f;
		}
	}
	else _delete = true;
	
}



void bomb::setHold(float x, float y)
{
	_pickup = true;
	_x = x;
	_y = y;
	framing(0, 1);
}

void bomb::setHold(float x, float y, float bottom)
{
	_pickup = true;
	_x = x;
	_y = y;
	_yg = bottom-(_image->getHeight()/2);
	_xg = _x;
	framing(0, 1);

	_tall = _yg - _y;
}

void bomb::drop()
{
	if (_yg > _y)
	{
		_gravity -= 0.2f;
		_y -= _gravity;
		framing();
	}
	else 
	{
		_y = _yg;
		framing(0, 1);
	}
}

void bomb::drop(float g)
{
	if (_yg > _y)
	{
		_gravity -= g;
		_y -= _gravity;
		framing();
	}
	else
	{
		_y = _yg;
		framing(0, 1);
	}
}

void bomb::framing()
{
	float indexTime = 1.0f / 20;
	if (_indexTime > (indexTime))
	{
		if (_index > _image->getMaxFrameX()) _index = 0;
		_index++;
		_image->setFrameX(_index);
		_indexTime -= indexTime;
	}
	
}

void bomb::framing(int start, int end)
{
	float indexTime = 1.0f / 7;
	if (start < end)
	{
		if (_indexTime > (indexTime))
		{
			if (_index > end) _index = start;
			_image->setFrameX(_index);
			_index++;
			_indexTime -= indexTime;
		}
	}
	if (start > end)
	{
		if (_indexTime > (indexTime))
		{
			if (_index > start) _index = end;
			_image->setFrameX(_index);
			_index++;
			_indexTime -= indexTime;
		}
	}
	
}

void bomb::reverseFraming()
{
	float indexTime = 1.0f / 20;
	if (_indexTime > (indexTime))
	{
		if (_index < 0) _index = _image->getMaxFrameX();
		_image->setFrameX(_index);
		_index--;
		_indexTime -= indexTime;
	}
}

void bomb::reverseFraming(int start, int end)
{
	float indexTime = 1.0f / 7;
	if (start > end)
	{
		if (_indexTime > (indexTime))
		{
			if (_index < end) _index = start;
			_image->setFrameX(_index);
			_index--;
			_indexTime -= indexTime;
		}
	}
	if (start < end)
	{
		if (_indexTime > (indexTime))
		{
			if (_index < start) _index = end;
			_image->setFrameX(_index);
			_index--;
			_indexTime -= indexTime;
		}
	}
}
	
