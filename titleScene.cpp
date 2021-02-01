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
	_image = IMAGEMANAGER->addImage("타이틀메뉴", "image/title.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_gameStart = RectMakeCenter(WINSIZEX / 2, 350, 200, 60);
	_mapTool = RectMakeCenter(WINSIZEX / 2, 430, 200, 60);
	_option = RectMakeCenter(WINSIZEX / 2, 510, 200, 60);
	_exit = RectMakeCenter(WINSIZEX / 2, 592, 200, 60);
	return S_OK;
}

void titleScene::release()
{
}


void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON))
	{
		if (PtInRect(&_gameStart, _ptMouse) == true && PtInRect(&_gameStart, _ptMouse) == true)
		{
			SCENEMANAGER->changeScene("메인씬");
		}

		else if (PtInRect(&_mapTool, _ptMouse) == true && PtInRect(&_mapTool, _ptMouse) == true)
		{
			SCENEMANAGER->changeScene("맵툴");
		}

		if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON) && PtInRect(&_option, _ptMouse) == true)
		{
			// 볼륨조절 키입력 할 예정입니다.
			SCENEMANAGER->changeScene("옵션");
		}
		if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON) && PtInRect(&_exit, _ptMouse) == true)
		{
			// 나가는 함수 찾아서 적을예정
		}
	}

}

void titleScene::render()
{

	_image->render(getMemDC());


}
