#include "stdafx.h"
#include "titleScene.h"

titleScene::titleScene()
{
}

titleScene::~titleScene()
{
}

HRESULT titleScene::init()
{
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		SCENEMANAGER->changeScene("메인씬");
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		SCENEMANAGER->changeScene("맵툴");
	}
}

void titleScene::render()
{
	TextOut(getMemDC(), WINSIZEX / 3, WINSIZEY / 2,
		"A스타트     S맵툴     D옵션(아직X)",
		strlen("A스타트     S맵툴     D옵션(아직X)"));
}
