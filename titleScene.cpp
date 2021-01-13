#include "stdafx.h"
#include "titleScene.h"

titleScene::titleScene()
{
	_rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	_cursor = 0;
}

titleScene::~titleScene()
{
}

HRESULT titleScene::init()
{
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);

	_loopX = _loopY = _cursorCount = 0;
	_cursorFrame = 1;

	_selected = false;
	SOUNDMANAGER->play("¼¿·ºÆ®¾À");
	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	++_cursorCount;
	if (_cursorCount > 6)
	{
		_cursorCount = 0;
		_cursorFrame *= -1;
	}
	_loopX += 1;
	_loopY += 1;
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _cursor < 3 && !_selected)
	{
		++_cursor;
		SOUNDMANAGER->play("¼±ÅÃ ÀÌµ¿");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && _cursor > 0 && !_selected)
	{
		--_cursor;
		SOUNDMANAGER->play("¼±ÅÃ ÀÌµ¿");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (!_selected && _cursor == 0)
		{
			_selected = true;
			SOUNDMANAGER->play("¼±ÅÃ ¿£ÅÍ");
		}
		else if (_selected)
		{
			SOUNDMANAGER->stop("¼¿·ºÆ®¾À");
			SCENEMANAGER->changeScene("¸ÞÀÎ¾À");
		}
	}
}

void titleScene::render()
{
	FINDIMG("¼¿·º¹è°æ")->loopRender(getMemDC(), &_rc, _loopX, _loopY);
	if (_cursorFrame == 1 && !_selected) FINDIMG("¼¿·ºÄ¿¼­")->frameRender(getMemDC(), 134 + 240 * _cursor, 165, 0, 0);
	else if (_cursorFrame == -1 && !_selected) FINDIMG("¼¿·ºÄ¿¼­")->frameRender(getMemDC(), 134 + 240 * _cursor, 165, 1, 0);
	FINDIMG("¼¿·ºÄ³¸¯")->render(getMemDC());
	if (!_selected) FINDIMG("¼¿·º·¹µå")->frameRender(getMemDC(), 34, 178, 0, 0);
	else FINDIMG("¼¿·º·¹µå")->frameRender(getMemDC(), 34, 178, 1, 0);
}
