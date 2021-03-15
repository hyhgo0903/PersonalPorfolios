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
	SOUNDMANAGER->stop("보스브금");
	if(!SOUNDMANAGER->isPlaySound("클리어"))PLAYSND("클리어");
	_score = CAMX;
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	_mainRc = RectMakeCenter(WINSIZEX / 4 + 20, WINSIZEY / 2 + 150, 200, 80);
	_exitRc = RectMakeCenter(WINSIZEX / 2 + 250, WINSIZEY / 2 + 150, 200, 80);
	_retryRc = RectMakeCenter(1175, 25, 100, 100);
	return S_OK;
}

void endingScene::release()
{
}

void endingScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_mainRc, _ptMouse))
		{
			SCENEMANAGER->changeScene("타이틀씬");
		}
		if (PtInRect(&_exitRc, _ptMouse))
		{
			PostQuitMessage(0);
		}
		if (PtInRect(&_retryRc, _ptMouse))
		{
			SCENEMANAGER->changeScene("메인씬");
		}
	}
}

void endingScene::render()
{
	FINDIMG("롤승리")->render(getMemDC());
	/*Rectangle(getMemDC(), _mainRc);
	Rectangle(getMemDC(), _exitRc);
	Rectangle(getMemDC(), _retryRc);
*/
	// 최종스코어 보여주는거
	FINDIMG("스코어")->render(getMemDC(),WINSIZEX / 2 - 100 , WINSIZEY / 2 - 7);
	if (_score > 9999) FINDIMG("숫자")->frameRender(getMemDC(), WINSIZEX / 2 - 30, WINSIZEY / 2, _score / 10000 % 10, 0);
	if (_score > 999) FINDIMG("숫자")->frameRender(getMemDC(), WINSIZEX / 2 - 15, WINSIZEY / 2, _score / 1000 % 10, 0);
	if (_score > 99) FINDIMG("숫자")->frameRender(getMemDC(), WINSIZEX / 2 , WINSIZEY / 2, _score / 100 % 10, 0);
	if (_score > 9) FINDIMG("숫자")->frameRender(getMemDC(), WINSIZEX / 2 + 15, WINSIZEY / 2, _score / 10 % 10, 0);
	//if (_score > 9999) FINDIMG("숫자")->frameRender(getMemDC(), 600 - 30, WINSIZEY/2, _score / 10000 % 10, 0);
	//if (_score > 999) FINDIMG("숫자")->frameRender(getMemDC(), 600 - 15, WINSIZEY / 2, _score / 1000 % 10, 0);
	//if (_score > 99) FINDIMG("숫자")->frameRender(getMemDC(), 600, WINSIZEY / 2, _score / 100 % 10, 0);
	//if (_score > 9) FINDIMG("숫자")->frameRender(getMemDC(), 600 + 15, WINSIZEY / 2, _score / 10 % 10, 0);
	FINDIMG("숫자")->frameRender(getMemDC(), WINSIZEX / 2 + 30, WINSIZEY / 2, _score % 10, 0);
}
