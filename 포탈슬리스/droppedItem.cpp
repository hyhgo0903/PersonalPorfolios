#include "stdafx.h"
#include "droppedItem.h"


droppedItem::droppedItem()
{

}

droppedItem::~droppedItem()
{

}

HRESULT droppedItem::init(bool stateType, float x, float y)
{
	_stateType = stateType;			  
	_x = x;	_y = y;
	_landed = _disappear = false;
	_xSpd = 0;
	
	if (_stateType) // 상태타입이면
	{
		_ySpd = -5; // 상태타입이면 튀어오르기
		_itemType = rand() % 3;
		_frameX = _itemType;
		_rc = RectMakeCenter(_x, _y, 45 ,39);
	}
	else // 사용타입이면 아이템박스
	{
		_itemType = -1;
		_ySpd = 0;
		_frameX= rand()%4;
		_rc = RectMakeCenter(_x, _y, 36, 31);
	}
	_durCount = 0;
	_alphaValue = 255;

	return S_OK;
}

void droppedItem::release()
{
}

void droppedItem::update()
{
	if (_durCount < ITEMDURMAX) _durCount++;
	else _disappear = true;
	if (_durCount > ITEMDURMAX - 50) _alphaValue -= 5; // 사라진다아앍
	
	if (_rc.right < GETCAM) _disappear = true;

	if (!_stateType && _durCount % 5 == 0 && !_landed) // 도착안한상태면 상자가 빙글빙글 돌아
	{
		_frameX++;
		if (_frameX > 3) _frameX = 0;
	}

	move();
}

void droppedItem::render()
{
	if (_stateType)	FINDIMG("상태템")->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0, _alphaValue);
	else	FINDIMG("아이템상자")->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _frameX,0, _alphaValue);
	
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
}

void droppedItem::move()
{
	if (!_landed)
	{
		_y += _ySpd;
		if (!_stateType) _x += 0.5f * _xSpd; // xspd(바람영향)은 아이템매니저에서 입력받습니다.
		_ySpd += GRAVITY/2;

		if (_stateType) _rc = RectMakeCenter(_x, _y, 45, 39);
		else
		{
			_rc = RectMakeCenter(_x, _y, 36, 31);						
		}

		COLORREF color = GetPixel(FINDIMG("맵픽셀")->getMemDC(), _x, _rc.bottom+1);
		int r = GetRValue(color); int g = GetGValue(color); int b = GetBValue(color);
		if ((r == 0 && g == 255 && b == 0) && _ySpd > 0)
		{
			_landed = true;
		}

	}
	if (_landed) // 착륙했으면 제자리 둥실둥실
	{
		if (_durCount % 60 > 29) _y += 0.2f;
		else _y -= 0.2f;
		if (_stateType) _rc = RectMakeCenter(_x, _y, 45, 39);
		else _rc = RectMakeCenter(_x, _y, 36, 31);
	}
}
