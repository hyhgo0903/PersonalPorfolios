#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init(float x, float y)
{ // 얘는 안쓸거야. 상속한 것의 이닛이 돌아감
	return S_OK;
}


void enemy::release()
{
}

void enemy::update()
{
	
}

void enemy::render()
{
}

void enemy::fillColorEllipse(int R, int G, int B, RECT rc)
{
	HPEN pen = CreatePen(0, 2, RGB(R, G, B));
	HPEN oldpen = (HPEN)SelectObject(getMemDC(), pen);
	HBRUSH brush = CreateSolidBrush(RGB(R, G, B));
	HBRUSH oldbrush = (HBRUSH)SelectObject(getMemDC(), brush);
	Ellipse(getMemDC(), rc);
	SelectObject(getMemDC(), oldbrush);
	DeleteObject(brush);
	SelectObject(getMemDC(), oldpen);
	DeleteObject(pen);
}

void enemy::setState(enemyState state)
{
	_state = state;
	_index = 0;
	_count = 0;
}

