#include "stdafx.h"
#include "endingScene.h"

endingScene::endingScene()
{
}

endingScene::~endingScene()
{
}

HRESULT endingScene::init()
{
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	return S_OK;
}

void endingScene::release()
{
}

void endingScene::update()
{
}

void endingScene::render()
{
	FINDIMG("플레이어깃발")->render(getMemDC(), 500, 300);
}
