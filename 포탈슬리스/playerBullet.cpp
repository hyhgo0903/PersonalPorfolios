#include "stdafx.h"
#include "playerBullet.h"

HRESULT playerBullet::init(int ID, float x, float y,
	float angle, float power, float damageCoefficient)
{ // 종류, 위치x, y, 각도, 파워, 데미지계수
	_ID = ID;	_x = x;	_y = y;	_hits = 1;
	switch (_ID)
	{ // 검콩 빨콩 미탱 유도 3발 9발 슈탱기본 슈탱9발순
	case 0: _width = 23; _height = 23; _damage = 45; break;
	case 1: _width = 12; _height = 12; _damage = 70; break;
	case 2: _width = 27; _height = 27; _damage = 10; _hits = 4; break;
	case 3: _width = 30; _height = 30; _damage = 10; _hits = 4; break;
	case 4: _width = 29; _height = 29; _damage = 12; break;
	case 5: _width = 18; _height = 18; _damage = 8; break;
	case 6: _width = 33; _height = 33; _damage = 10; _hits = 4; break;
	case 7: _width = 18; _height = 19; _damage = 8; break;
	}
	_damage *= damageCoefficient;
	_rc = RectMakeCenter(_x, _y, _width, _height);
	_xSpd = power * cosf(angle);
	_ySpd = power * -sinf(angle);
	_isFire = true;
	_duration = _frameX = _frameCount = 0;
	_chase = false; // 유도탄이면 쫓아가고 있는지

	return S_OK;
}

void playerBullet::release()
{
}

void playerBullet::update()
{	
	if (!_chase)
	{
		_ySpd += GRAVITY;
		_xSpd += _wind;
	}
	move();
	if (_hits < 1) _isFire = false; // 히트수 다 쓰면 이즈파이어 꺼줌
	_rc = RectMakeCenter(_x, _y, _width, _height);
	if (_ID > 1) // 다른건 8방향으로 쏜다
	{
		_angle = getAngle(0,0,_xSpd,_ySpd) + PI8; // 현재 각도를 도출하고 더함
		if (_angle > 2 * PI) _angle -= 2 * PI;
		else if (_angle < 0) _angle += 2 * PI;
		_frameX = int(4.0f*_angle / PI);
	}
	else // 캐논탱은 뺑글뺑글
	{
		if (_duration % 3 == 0) ++_frameX;
		if (_frameX > 3) _frameX = 0;
	}
	if (_hits == 0) _isFire = false;
}

void playerBullet::render()
{

	if (KEYMANAGER->isToggleKey(VK_TAB))	{Rectangle(getMemDC(), _rc);}
	switch (_ID)
	{
	case 0: FINDIMG("캐논일반")->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0); break;
	case 1: FINDIMG("캐논특수")->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0); break;
	case 2: FINDIMG("미탱일반")->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0); break;
	case 3: FINDIMG("미탱특수")->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0); break;
	case 4: FINDIMG("멀탱일반")->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0); break;
	case 5: FINDIMG("멀탱특수")->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0); break;
	case 6: FINDIMG("슈탱일반")->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0); break;
	case 7: FINDIMG("슈탱특수")->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0); break;
	}
	if (_chase) FINDIMG("타겟")->resizedRender(getMemDC(), _targetRc.left, _targetRc.top, _targetRc.right - _targetRc.left, _targetRc.bottom - _targetRc.top);
}
