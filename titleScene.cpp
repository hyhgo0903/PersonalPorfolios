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
	_titleImage = IMAGEMANAGER->addImage("타이틀메뉴", "image/title.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_volumRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 300, 300);
	_volumeSetImage = IMAGEMANAGER->addImage("볼륨조절", "image/VolumeSet.bmp",300, 300, true, RGB(255, 0, 255));
	_gameStart = RectMakeCenter(WINSIZEX / 2, 350, 200, 60);
	_mapTool = RectMakeCenter(WINSIZEX / 2, 430, 200, 60);
	_option = RectMakeCenter(WINSIZEX / 2, 510, 200, 60);
	_volumeExit = RectMakeCenter(_volumRect.bottom + 98, _volumRect.top + 271, 50, 30);
	_exit = RectMakeCenter(WINSIZEX / 2 - 1, 593, 200, 60);;
	_isVolumeSetOn = false;
	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON))
	{
		if (PtInRect(&_gameStart, _ptMouse) == true)
		{
			SCENEMANAGER->changeScene("메인씬");
		}

		else if (PtInRect(&_mapTool, _ptMouse) == true)
		{
			SCENEMANAGER->changeScene("맵툴");
		}

		else if (PtInRect(&_option, _ptMouse) == true && _isVolumeSetOn == false)
		{
			SCENEMANAGER->changeScene("볼륨조절");
			_isVolumeSetOn = true;
		}
		if (PtInRect(&_volumeExit, _ptMouse) == true && _isVolumeSetOn == true)
		{
			_isVolumeSetOn = false;
		}

		else if (PtInRect(&_exit, _ptMouse) == true)
		{
			// 나가는 함수 찾아서 적을예정
		}
	}
}

void titleScene::render()
{
	_titleImage->render(getMemDC());
	if (_isVolumeSetOn == true)
	{
		_volumeSetImage->render(getMemDC(), _volumRect.left, _volumRect.top);
		
	}
}
