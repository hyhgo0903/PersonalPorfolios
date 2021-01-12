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
	SOUNDMANAGER->play("¿£µù");
	_loopX = _characterY = 0.f;
	_dialCount = 0;
	_dialog1index=0;	_dialog2index=0;	_dialog3index=0;
	_yUp = false;
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	return S_OK;
}

void endingScene::release()
{
}

void endingScene::update()
{
	if (_loopX < 514) _loopX += 0.5;
	if (!_yUp) _characterY += 0.1f;
	if (_characterY > 20) _yUp = true;
	if (_yUp) _characterY -= 0.1f;
	if (_characterY < 0.1f) _yUp = false;
	if (_dialCount < 10) ++_dialCount;
	else
	{
		_dialCount = 0;
		if (_dialog1index < 21) ++_dialog1index;
		else if (_dialog2index < 26) ++_dialog2index;
		else if (_dialog3index < 15) ++_dialog3index;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (_dialog1index < 21) _dialog1index = 21;
		else if (_dialog2index < 26) _dialog2index = 26;
		else if (_dialog3index < 15) _dialog3index = 15;
		else PostQuitMessage(0);
	}
}

void endingScene::render()
{
	FINDIMG("ÄÆ¾À·çÇÁ¹è°æ")->render(getMemDC(), 0, 154, _loopX, 0, 1024, 768);
	FINDIMG("ÄÆ¾À¹è°æ")->render(getMemDC()); 
	FINDIMG("ÄÆ¾ÀÄ³¸¯")->render(getMemDC(), 0, 154+_characterY);
	FINDIMG("ÄÆ¾À´ë»çÃ¢")->render(getMemDC(), 0, 564);
	if (_dialog1index == 21) FINDIMG("ÄÆ¾À·¹µå")->render(getMemDC(), 53, 662);
	FINDIMG("ÄÆ¾À´ë»ç1")->render(getMemDC(), 167, 591, 0, 0, _dialog1[_dialog1index], 28);
	FINDIMG("ÄÆ¾À´ë»ç2")->render(getMemDC(), 167, 680, 0, 0, _dialog2[_dialog2index], 26);
	FINDIMG("ÄÆ¾À´ë»ç3")->render(getMemDC(), 167, 706, 0, 0, _dialog3[_dialog3index], 27);
}
