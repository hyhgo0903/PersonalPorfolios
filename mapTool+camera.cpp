#include "stdafx.h"
#include "mapTool.h"

//이거 카메라 움직여주는 부분
void mapTool::cameraControl()
{
	_cameraPtMouse.x = _ptMouse.x + CAMX;
	_cameraPtMouse.y = _ptMouse.y + CAMY;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->setCameraX(CAMX - 5);
		if (CAMX < 0) CAMERAMANAGER->setCameraX(0);
		sampleTileMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->setCameraX(CAMX + 5);
		if (CAMX > MAPSIZEX - WINSIZEX) CAMERAMANAGER->setCameraX(MAPSIZEX - WINSIZEX);
		sampleTileMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->setCameraY(CAMY - 5);
		if (CAMY < 0) CAMERAMANAGER->setCameraY(0);
		sampleTileMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->setCameraY(CAMY + 5);
		if (CAMY > MAPSIZEY - WINSIZEY) CAMERAMANAGER->setCameraY(MAPSIZEY - WINSIZEY);
		sampleTileMove();
	}
}

//이건 화면이 움직임에따라 같이 움직여야하는 샘플타일의 움직임
void mapTool::sampleTileMove()
{
	for (int i = 0; i < SAMPLEY; ++i)
	{
		for (int j = 0; j < SAMPLEX; ++j)
		{
			_sample[i * SAMPLEX + j].rc = RectMake((WINSIZEX + CAMX - 512) + (j*TILESIZEX), CAMY + (i*TILESIZEY), TILESIZEX, TILESIZEY);
		}
	}
}