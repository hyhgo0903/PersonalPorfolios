#include "stdafx.h"
#include "playGround.h"


void playGround::uiRender()
{
	if (!_seeMinimap) return;
	CAMERAMANAGER->minimap(getMemDC(), 0, 580, 240, 120, true);
	Rectangle(getMemDC(), _camMap);


	LineMake(getMemDC(), CAMX + 120, CAMY + 580, CAMX + 0, CAMY + 640);
	LineMake(getMemDC(), CAMX + 120, CAMY + 580, CAMX + 240, CAMY + 640);
	LineMake(getMemDC(), CAMX + 120, CAMY + 700, CAMX + 0, CAMY + 640);
	LineMake(getMemDC(), CAMX + 120, CAMY + 700, CAMX + 240, CAMY + 640);

	if (!_ms->getUM()) return; // 메인씬이닛 안한거면 리턴해야 안터져
	for (int i = 0; i < _ms->getUM()->getVUnit().size(); ++i)
	{
		RECT temp = _ms->getUM()->getVUnit()[i]->getRect();
		if (_ms->getUM()->getVUnit()[i]->getState() == DEAD) continue;
		if (_ms->getUM()->getVUnit()[i]->getBelong() == PLAYER)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
			CAMERAMANAGER->minimapObject(getMemDC(), temp);
			SelectObject(getMemDC(), oldBrush);	DeleteObject(brush);
			SelectObject(getMemDC(), oldPen);	DeleteObject(pen);
		}
		else
		{
			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
			CAMERAMANAGER->minimapObject(getMemDC(), temp);
			SelectObject(getMemDC(), oldBrush);	DeleteObject(brush);
			SelectObject(getMemDC(), oldPen);	DeleteObject(pen);
		}
	}
}

void playGround::yoonghoUpdate()
{
	if (!_seeMinimap) return;
	if (_ptMouse.x < 240 && _ptMouse.y > 580)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			CAMERAMANAGER->setCameraX(8 * _ptMouse.x - 600);
			CAMERAMANAGER->setCameraY(8 * _ptMouse.y - 4990);
			if (CAMX < 0) CAMERAMANAGER->setCameraX(0);
			if (CAMY < 0) CAMERAMANAGER->setCameraY(0);
			if (CAMX > MAPSIZEX - WINSIZEX) CAMERAMANAGER->setCameraX(MAPSIZEX - WINSIZEX);
			if (CAMY > MAPSIZEY - WINSIZEY) CAMERAMANAGER->setCameraY(MAPSIZEY - WINSIZEY);
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && CAMY > 0)
	{
		CAMERAMANAGER->setCameraY(CAMY - 10);
		if (CAMY < 0) CAMERAMANAGER->setCameraY(0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && CAMY < MAPSIZEY - WINSIZEY)
	{
		CAMERAMANAGER->setCameraY(CAMY + 10);
		if (CAMY > MAPSIZEY - WINSIZEY) CAMERAMANAGER->setCameraY(MAPSIZEY - WINSIZEY);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && CAMX > 0)
	{
		CAMERAMANAGER->setCameraX(CAMX - 10);
		if (CAMX < 0) CAMERAMANAGER->setCameraX(0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && CAMX < MAPSIZEX - WINSIZEX)
	{
		CAMERAMANAGER->setCameraX(CAMX + 10);
		if (CAMY > MAPSIZEX - WINSIZEX) CAMERAMANAGER->setCameraX(MAPSIZEX - WINSIZEX);
	}

	_camMap = RectMake(CAMX + (CAMX+_x/4) / 8, 580 + CAMY + (CAMY+_y/4) / 8, 150-_x/8, 175.f / 2.f - _y/8);
}