#include "stdafx.h"
#include "videoScene.h"

videoScene::videoScene()
{
}

videoScene::~videoScene()
{
}

HRESULT videoScene::init()
{
	LogoVideo = MCIWndCreate(_hWnd, NULL, MCIWNDF_NOPLAYBAR |
		WS_VISIBLE | WS_CHILD, "sample_1280x720.wmv");
	MoveWindow(LogoVideo, 0, 0, WINSIZEX, WINSIZEY, NULL);
	MCIWndPlay(LogoVideo);
	return S_OK;
}

void videoScene::release()
{
	MCIWndClose(LogoVideo);
}

void videoScene::update()
{
}

void videoScene::render()
{
}
