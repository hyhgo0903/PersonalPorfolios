#include "stdafx.h"
#include "bullets.h"


HRESULT bullets::init()
{	// 이걸로 만들어낼 일은 없어서 패스 (상속클래스의 이닛호출로)
	return S_OK;
}

void bullets::release()
{
}

void bullets::update()
{

}

void bullets::render()
{
}

void bullets::move()
{
	// 속도만큼 옮겨줌
	_x += _xSpd;	_y += _ySpd;
	// 픽셀충돌시 꺼짐(초록색만)
	COLORREF color = GetPixel(FINDIMG("맵픽셀")->getMemDC(), _x, _y+1);
	int r = GetRValue(color); int g = GetGValue(color); int b = GetBValue(color);
	if (r == 0 && g == 255 && b == 0) _isFire = false; // 초록색 만나면 꺼짐	   
	// 화면밖 꺼짐. 잠시 갔다 돌아올수도 있으니까 200만큼 버퍼 부여
	if (_x+_width/2 < GETCAM-200 || _x-_width / 2 > GETCAM + WINSIZEX+200) _isFire = false;
	if (_y > WINSIZEY+_height / 2) _isFire = false;
	// 지속시간 끝나면 꺼짐
	if (_duration < BULLETDURATION) ++_duration;
	else _isFire = false;
}
