#include "stdafx.h"
#include "minion.h"

minion::minion()
{
}

minion::~minion()
{
}

//void minion::imageRect()
//{
//	//몬스터의 상태에 따라 렉트크기를 자동으로 조절해서 다시 그려주는 함수
//	if (_state == E_IDLE_L || _state == E_IDLE_R)
//	{
//		_rc = RectMakeCenter(_x, _y, IMAGEMANAGER->findImage("enemy1_idle")->getWidth() / 3,
//			IMAGEMANAGER->findImage("enemy1_idle")->getHeight() / 2);
//	}
//	
//	if (_state == E_WALK_L || _state == E_WALK_R)
//	{
//		_rc = RectMakeCenter(_x, _y, IMAGEMANAGER->findImage("enemy1_walk")->getWidth() / 6,
//			IMAGEMANAGER->findImage("enemy1_walk")->getHeight() / 2);
//	}
//
//	if (_state == E_ATK_L || _state == E_ATK_R)
//	{
//		_rc = RectMakeCenter(_x, _y, IMAGEMANAGER->findImage("enemy1_atk")->getWidth() / 3,
//			IMAGEMANAGER->findImage("enemy1_atk")->getHeight() / 2);
//	}
//
//}

void minion::move()
{
	//몬스터(_x,_y)와 플레이어(_pX,_pY)의 중점좌표를 비교하여 몬스터의 중점좌표를 이동시켜주는 함수
	if (_x > _pX) { _x -= 1; }
	if (_x < _pX) { _x += 1; }

	if (_y > _pY) { _y -= 1; }
	if (_y < _pY) { _y += 1; }
}

void minion::enemyState()
{
	//몬스터가 플레이어의 오른쪽에 있을때
	if (_pX - _x > 120)
	{
		if (_state != E_WALK_R) _index = 0;
		_state = E_WALK_R;
	}
	if (_pX - _x < 120 && _pX - _x > 0)
	{
		if (_state != E_ATK_R) _index = 0;
		_state = E_ATK_R;
	}

	//몬스터가 플레이어의 오른쪽에 있을때
	if (_pX - _x < -120)
	{
		if (_state != E_WALK_L) _index = 0;
		_state = E_WALK_L;
	}
	if (_pX - _x > -120 && _pX - _x < 0)
	{
		if (_state != E_ATK_L) _index = 0;
		_state = E_ATK_L;
	}
}

HRESULT minion::init(float x, float y)
{
	_x = x;	_y = y;
	_currentHP = _maxHP = 100;
	_count = _index = 0;
	_state = E_IDLE_L;
	//imageRect();
	return S_OK;

}

void minion::release()
{
}

void minion::update()
{
	move();
	_rc = RectMakeCenter(_x, _y, 150, 150);
	//imageRect();
	enemyState();

	//볼 몬스터 프레임 렌더
	_count++;
	
	if (_count % 10 == 0)
	{
		_index++;
		//볼 몬스터의 상태에 따라 초기화되는 인덱스 값의 범위를 조정(이미지마다 인덱스 크기가 다르기때문)
		if (_state == E_IDLE_L && _index > 2) _index = 0;
		if (_state == E_IDLE_R && _index > 2) _index = 0;
		if (_state == E_WALK_L && _index > 5) _index = 0;
		if (_state == E_WALK_R && _index > 5) _index = 0;
		if (_state == E_ATK_L && _index > 2) _index = 0;
		if (_state == E_ATK_R && _index > 2) _index = 0;





		_count = 0;
	}
}

void minion::render()
{
	//볼 몬스터의 상태에 따라 렌더되는 이미지를 정해줌
	if (_state == E_IDLE_L) IMAGEMANAGER->findImage("enemy1_idle")->frameRender(getMemDC(), _rc.left - 40, _rc.top - 10, _index, 0);
	if (_state == E_IDLE_R) IMAGEMANAGER->findImage("enemy1_idle")->frameRender(getMemDC(), _rc.left - 80, _rc.top - 10, _index, 1);
	if (_state == E_WALK_L) IMAGEMANAGER->findImage("enemy1_walk")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 0);
	if (_state == E_WALK_R) IMAGEMANAGER->findImage("enemy1_walk")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 1);
	if (_state == E_ATK_L) IMAGEMANAGER->findImage("enemy1_atk")->frameRender(getMemDC(), _rc.left - 150, _rc.top - 150, _index, 0);
	if (_state == E_ATK_R) IMAGEMANAGER->findImage("enemy1_atk")->frameRender(getMemDC(), _rc.left - 150, _rc.top - 150, _index, 1);
	if(KEYMANAGER->isToggleKey(VK_F1)) Rectangle(getMemDC(), _rc);
}
