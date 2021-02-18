#include "stdafx.h"
#include "flyingEnemy.h"

HRESULT flyingEnemy::init(int ID, float x, float y)
{
	commomInit();
	_ID = ID;		// 적의 종류
	_x = x; _y = y;
	if (_ID == 1) _phase = 2;
	if (_ID == 2) _phase = 0;
	_destinationCount = 300; // 도착후 한번 바꿔주기 위해
	switch (_ID)
	{ // 0은 그냥 외계인 ,, 1은 커다란 ufo ,, 2는 솔데로커
	case 0: _currentHP = _maxHP = 100;	_width = 47; _height = 40; _destY = 20;
		_duration = rand() % 100;	break;
	case 1: _currentHP = _maxHP = 1500;	_width = 163; _height = 121; _destY = 61;	break;
	case 2: _currentHP = _maxHP = 2000;	_width = 24; _height = 20; _destY = 65;		break;
	}
	_rc = RectMakeCenter(_x, _y, _width, _height);
	_hpBar = new progressBar;
	if (_ID != 2) _hpBar->init(_width, 10);
	else _hpBar->init(220, 10);

	return S_OK;
}

void flyingEnemy::release()
{
}

void flyingEnemy::update()
{
	commonUpdate();
	frameXUpdate();
	if (_rc.top < 10 && _ID != 0) _y += 0.5f; // 보스니까 무게감있게 천천히 등장
	if (_rc.top < 0 && _ID == 0) _y += 5.f;	// 쫄병은 빠르게 등장
	if (_rc.top >= 0) _arrived = true;
	if (_rc.right < GETCAM) _x = GETCAM - _width/2;
	flyingMove();
	_rc = RectMakeCenter(_x, _y, _width, _height);
	if (_ID == 2)
	{
		_hpBar->setPoint(_x, _rc.top - 47);
		_hpBar->setGauge(_currentHP, _maxHP);
		_hpBar->update();
	}
	fireReady();
}

void flyingEnemy::render()
{
	switch (_ID)
	{ // 0은 그냥 외계인 ,, 1은 커다란 ufo ,, 2는 솔데로커
	case 0: FINDIMG("적3")->alphaFrameRender(getMemDC(), _rc.left, _rc.top,_frameX,0, _alphaValue);		break;
	case 1: FINDIMG("적4")->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0, _alphaValue);	break;
	case 2: FINDIMG("적5")->alphaRender(getMemDC(), _rc.left-98, _rc.top-35, _alphaValue);		break;
	}

	commonRender();

}

void flyingEnemy::frameXUpdate()
{
	if (_ID < 2 && _frameCount < 5) ++_frameCount;
	else if (_ID < 2)
	{
		_frameCount = 0;
		++_frameX;
	}
	if (_ID == 0 && _frameX > 15) _frameX = 0;
	if (_ID == 1 && _frameX > 23) _frameX = 0;
}

void flyingEnemy::fireReady()
{

	switch (_ID)
	{
	case 0:
		if (_duration > 200)
		{
			_duration = rand()%100;
			++_fireReady;
		}
		break;
	case 1:
		if (_duration > 150)
		{
			_duration = 0;
			++_fireReady;
		}
		break;
	case 2:
		if (_duration > 150 && _phase == 0)
		{
			_duration = -100;
			_fireReady = 75;
		}
		if (_duration > 50 && _phase != 0)
		{
			_duration = 0;
			_fireReady = 1;
		}
		break;
	}
}

void flyingEnemy::flyingMove()
{
	if (!_arrived || _alphaValue < 255) return;
	if (_destinationCount < 200)
	{
		++_destinationCount;
		if (getDistance(_x, _y, _destX, _destY) > 20)
		{
			float angle;
			angle = getAngle(_x, _y, _destX, _destY);
			if (_ID == 0)
			{
				_x += 4.f * cosf(angle);
				_y -= 4.f * sinf(angle);
			}
			else
			{
				_x += 0.5f * cosf(angle);
				_y -= 0.5f * sinf(angle);
			}
		}
	}
	else
	{
		_destinationCount = rand()%100;
		_destX = GETCAM + rand() % 480 + 110;
		_destY = rand() % 50 + 70;
	}
}
