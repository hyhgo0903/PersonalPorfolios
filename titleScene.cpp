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
	_titleImage = FINDIMG("타이틀메뉴");
	_volumRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 300, 300);
	_volumeSetImage = FINDIMG("볼륨조절");
	_gameStart = RectMakeCenter(WINSIZEX / 2, 350, 200, 60);
	_mapTool = RectMakeCenter(WINSIZEX / 2, 430, 200, 60);
	_option = RectMakeCenter(WINSIZEX / 2, 510, 200, 60);
	_volumeExit = RectMakeCenter(_volumRect.bottom + 98, _volumRect.top + 271, 50, 30);
	_exit = RectMakeCenter(WINSIZEX / 2 - 1, 593, 200, 60);
	_isVolumeSetOn = false;

	_testBgm = RectMake(_volumRect.left+ 250, _volumRect.top+133, 18, 15);
	_testEffect = RectMake(_volumRect.left + 250, _volumRect.top + 181, 18, 15);
	_bgmPlus = RectMake(_volumRect.left + 216, _volumRect.top + 133, 15, 18);
	_bgmBar = RectMake(_volumRect.left + 88, _volumRect.top + 126, 120, 29);
	_bgmMinus = RectMake(_volumRect.left + 71, _volumRect.top + 133, 15, 18);
	_effectPlus = RectMake(_volumRect.left + 216, _volumRect.top + 181, 15, 18);
	_effectBar = RectMake(_volumRect.left + 88, _volumRect.top + 175, 120, 29);
	_effectMinus = RectMake(_volumRect.left + 71, _volumRect.top + 181, 15, 18);


	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON))
	{
		if (PtInRect(&_gameStart, _ptMouse) == true && !_isVolumeSetOn)
		{
			SCENEMANAGER->changeScene("메인씬");
		}

		else if (PtInRect(&_mapTool, _ptMouse) == true && !_isVolumeSetOn)
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
			SOUNDMANAGER->stop("테란브금");
			SOUNDMANAGER->stop("사이오닉스톰");
		}
		else if (_isVolumeSetOn && PtInRect(&_testBgm, _ptMouse))
		{
			if (SOUNDMANAGER->isPlaySound("테란브금")) SOUNDMANAGER->stop("테란브금");
			else  SOUNDMANAGER->play("테란브금");
		}
		else if (_isVolumeSetOn && PtInRect(&_testEffect, _ptMouse))
		{
			if (SOUNDMANAGER->isPlaySound("사이오닉스톰")) SOUNDMANAGER->stop("사이오닉스톰");
			else  SOUNDMANAGER->play("사이오닉스톰");
		}

		else if (PtInRect(&_exit, _ptMouse) == true)
		{
			PostQuitMessage(0);
		}
	}
	if (KEYMANAGER->isStayKeyDown(MK_LBUTTON))
	{		
		if (_isVolumeSetOn && PtInRect(&_bgmBar, _ptMouse))
		{
			SOUNDMANAGER->setBgmVolume((_ptMouse.x - _bgmBar.left) / 120.f);
		}
		else if (_isVolumeSetOn && PtInRect(&_effectBar, _ptMouse))
		{
			SOUNDMANAGER->setEffectVolume((_ptMouse.x - _effectBar.left) / 120.f);
		}
		else if (_isVolumeSetOn && PtInRect(&_bgmPlus, _ptMouse))
		{
			SOUNDMANAGER->setBgmVolume(SOUNDMANAGER->getBgmVolume() + 0.01f);
			if (SOUNDMANAGER->getBgmVolume() > 1.f) SOUNDMANAGER->setBgmVolume(1.f);
		}
		else if (_isVolumeSetOn && PtInRect(&_bgmMinus, _ptMouse))
		{
			SOUNDMANAGER->setBgmVolume(SOUNDMANAGER->getBgmVolume() - 0.01f);
			if (SOUNDMANAGER->getBgmVolume() < 0.f) SOUNDMANAGER->setBgmVolume(0.f);
			
		}
		else if (_isVolumeSetOn && PtInRect(&_effectPlus, _ptMouse))
		{
			SOUNDMANAGER->setEffectVolume(SOUNDMANAGER->getEffectVolume() + 0.01f);
			if (SOUNDMANAGER->getEffectVolume() > 1.f) SOUNDMANAGER->setEffectVolume(1.f);
		}
		else if (_isVolumeSetOn && PtInRect(&_effectMinus, _ptMouse))
		{
			SOUNDMANAGER->setEffectVolume(SOUNDMANAGER->getEffectVolume() - 0.01f);
			if (SOUNDMANAGER->getEffectVolume() < 0.f) SOUNDMANAGER->setEffectVolume(0.f);
		}
	}
}

void titleScene::render()
{
	_titleImage->render(getMemDC());
	if (_isVolumeSetOn == true)
	{
		_volumeSetImage->render(getMemDC(), _volumRect.left, _volumRect.top);
		
		FINDIMG("브금조절바")->render(getMemDC(), _volumRect.left + 88, _volumRect.top + 126, 0, 0,
			120 * SOUNDMANAGER->getBgmVolume(), 29);
		FINDIMG("효과음조절바")->render(getMemDC(), _volumRect.left + 88, _volumRect.top + 175, 0, 0,
			120 * SOUNDMANAGER->getEffectVolume(), 29);
		if (SOUNDMANAGER->isPlaySound("테란브금"))
			FINDIMG("소리키고끄기")->frameRender(getMemDC(), _testBgm.left, _testBgm.top, 1, 0);
		else FINDIMG("소리키고끄기")->frameRender(getMemDC(), _testBgm.left, _testBgm.top, 0, 0);
		if (SOUNDMANAGER->isPlaySound("사이오닉스톰"))
			FINDIMG("소리키고끄기")->frameRender(getMemDC(), _testEffect.left, _testEffect.top, 1, 0);
		else
			FINDIMG("소리키고끄기")->frameRender(getMemDC(), _testEffect.left, _testEffect.top, 0, 0);
	}
}
