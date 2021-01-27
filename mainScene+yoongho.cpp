#include "stdafx.h"
#include "mainScene.h"


void mainScene::yoonghoUpdate()
{
	if (_ptMouse.x < 240 && _ptMouse.y > 580 && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		CAMERAMANAGER->setCameraX(8*_ptMouse.x - 600);
		CAMERAMANAGER->setCameraY(8*_ptMouse.y-4990);
		if (CAMX < 0) CAMERAMANAGER->setCameraX(0);
		if (CAMY < 0) CAMERAMANAGER->setCameraY(0);
		if (CAMX > MAPSIZEX - WINSIZEX) CAMERAMANAGER->setCameraX(MAPSIZEX - WINSIZEX);
		if (CAMY > MAPSIZEY - WINSIZEY) CAMERAMANAGER->setCameraY(MAPSIZEY - WINSIZEY);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && CAMY > 0)
	{
		CAMERAMANAGER->setCameraY(CAMY - 5);
		if (CAMY < 0) CAMERAMANAGER->setCameraY(0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && CAMY < MAPSIZEY-WINSIZEY)
	{
		CAMERAMANAGER->setCameraY(CAMY + 5);
		if (CAMY > MAPSIZEY - WINSIZEY) CAMERAMANAGER->setCameraY(MAPSIZEY - WINSIZEY);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && CAMX > 0)
	{
		CAMERAMANAGER->setCameraX(CAMX - 5);
		if (CAMX < 0) CAMERAMANAGER->setCameraX(0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && CAMX < MAPSIZEX - WINSIZEX)
	{
		CAMERAMANAGER->setCameraX(CAMX + 5);
		if (CAMY > MAPSIZEX - WINSIZEX) CAMERAMANAGER->setCameraX(MAPSIZEX - WINSIZEX);
	}

	_camMap = RectMake(CAMX + CAMX/8, 580 + CAMY + CAMY/8, 150, 175.f / 2.f);
}