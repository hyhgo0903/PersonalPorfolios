#include "stdafx.h"
#include "item.h"

item::item()
{
}

item::~item()
{
}

HRESULT item::init(float x, float y)
{
	return S_OK;
}

HRESULT item::init(float x, float y, float bottom)
{
	return S_OK;
}

void item::release()
{
}

void item::update()
{
}

void item::render()
{
}


void item::shadowRender(RECT rc)
{
	HPEN pen = CreatePen(0, 2, RGB(80, 80, 80));
	HPEN oldpen = (HPEN)SelectObject(getMemDC(), pen);
	HBRUSH brush = CreateSolidBrush(RGB(80, 80, 80));
	HBRUSH oldbrush = (HBRUSH)SelectObject(getMemDC(), brush);
	Ellipse(getMemDC(), rc);
	SelectObject(getMemDC(), oldbrush);
	DeleteObject(brush);
	SelectObject(getMemDC(), oldpen);
	DeleteObject(pen);
}

void item::fillColorEllipse(int R, int G, int B, RECT rc)
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

void item::attackMove(bool direction)
{
}


void item::setHold(float x, float y)
{
}

