
#include "stdafx.h"
#include "baseball.h"

baseball::baseball()
{
}

baseball::~baseball()
{
}

HRESULT baseball::init(float x, float y)
{
	//상위 클래스(item) 변수.
	_image = IMAGEMANAGER->findImage("공");//이미지 삽입
	_gravity = -3;//중력
	_x = x;	_y = y;//공중렉트 중심
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());//공중렉트

	_pickup = false;//들려있지 않음.
	_moving = false;//던져지지 않음.

	_xg = _x;//땅렉트
	_yg = _y + 70;
	_rcg = RectMakeCenter(_xg, _yg, _image->getWidth(), _image->getHeight());//땅렉트

	_distance = _yg - _y;//렉트간 거리.
	int shadowWidth = _image->getWidth() - (_distance / 2);
	int shadowHeight = (_image->getHeight() / 3) - (_distance / 6);
	_shadow = RectMakeCenter(_xg, _rcg.bottom, shadowWidth, shadowHeight);//그림자 출력용.
	_time = 0;
	_angle = 0;
	_strach = false;
	_ID = 1;
	_food = false;
	return S_OK;
}

HRESULT baseball::init(float x, float y, float bottom)
{
	//상위 클래스(item) 변수.
	_image = IMAGEMANAGER->findImage("공");//이미지 삽입
	_gravity = -3;//중력
	_x = x;	_y = y;//공중렉트 중심
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());//공중렉트

	_pickup = false;//들려있지 않음.
	_moving = false;//던져지지 않음.

	_xg = _x;//땅렉트
	_yg = bottom;
	_rcg = RectMakeCenter(_xg, _yg, _image->getWidth(), _image->getHeight());//땅렉트

	_distance = _yg - _y;//렉트간 거리.
	int shadowWidth = _image->getWidth() - (_distance / 2);
	int shadowHeight = (_image->getHeight() / 3) - (_distance / 6);
	_shadow = RectMakeCenter(_xg, _rcg.bottom, shadowWidth, shadowHeight);//그림자 출력용.
	_time = 0;
	_angle = 0;
	_strach = false;
	_ID = 1;
	_food = false;
	return S_OK;
}

void baseball::release()
{
}

void baseball::update()
{
	if (!_pickup && !_moving) drop();

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_rcg = RectMakeCenter(_xg, _yg, _image->getWidth(), _image->getHeight());

	_distance = _yg - _y;//땅렉트랑 공중렉트랑 위치차이.

	//그림자 크기 조절. 멀어지면 작아지도록 합니다.
	int shadowWidth = _image->getWidth() - (_distance / 2);
	int shadowHeight = (_image->getHeight() / 3) - (_distance / 6);
	//0보다 작아지면 사라지도록 합시다.
	if (shadowWidth <= 10) shadowWidth = 10;
	if (shadowHeight <= 10)shadowHeight = 10;

	_shadow = RectMakeCenter(_xg, _rcg.bottom, shadowWidth, shadowHeight);

	if (_strach) _image = IMAGEMANAGER->findImage("찌그러진공");
	else _image = IMAGEMANAGER->findImage("공");


	if (_strach)_time -= TIMEMANAGER->getElapsedTime();
	if (_time < 0)_strach = false;
	if (_pickup)
	{
		_xg = _x;//땅렉트
		_rcg = RectMakeCenter(_xg, _yg, _image->getWidth(), _image->getHeight());//땅렉트
	}
	if (_moving)
	{
		_xg = _x;//땅렉트
		_rcg = RectMakeCenter(_xg, _yg, _image->getWidth(), _image->getHeight());//땅렉트
	}
}

void baseball::render()
{
	fillColorEllipse(80, 80, 80, _shadow);
	//Rectangle(getMemDC(), _rcg);
	_image->render(getMemDC(), _x - (_image->getWidth() / 2), _rc.top);
	//TextOut(getMemDC(), _rc.left, _rc.top, "난 야구공", strlen("난 야구공"));
}

void baseball::drop()
{
	if (_yg > _y)
	{
		_gravity += 0.2f;
		_y += _gravity;
	}
	else if (_yg < _y)
	{
		_strach = true;
		_time = 1.0f / 5;
		_y = _yg;
	}
	else
	{
		_y = _yg;
	}
}

void baseball::setHold(float x, float y)
{
	_pickup = true;
	_x = x;
	_y = y;
}

void baseball::setHold(float x, float y, float bottom)
{
	_pickup = true;
	_x = x;
	_y = y;
	_yg = bottom - (_image->getHeight() / 2);
	_tall = _yg - _y;
}

void baseball::attackMove(bool direction)
{//매니저에서 사용할 함수.
	_pickup = false;
	_moving = true;
	_direction = direction;
	if (_direction == true)
	{
		_x += 17.2f;
	}
	else
	{
		_x -= 17.2f;
	}
	_y -= 10 * sinf(_angle);//충돌시 튕겨나가는 느낌을 주기위해.
	_yg -= 10 * sinf(_angle);
}
