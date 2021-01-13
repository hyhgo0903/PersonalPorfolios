#include "stdafx.h"
#include "mainScene.h"

void mainScene::cameraControl()
{
	RECT temp = _pl->getGroundRc();
	//if (_em->getVEnemy().size() == 0) CAMERAMANAGER->cameraLockOff();
	//else CAMERAMANAGER->cameraLock(); // 적이 있으면 캠고정, 적이 없으면 캠고정 풂
	CAMERAMANAGER->focusOnRect(temp, 3);
	if (CAMY <= 55 && CAMX < 1849) CAMERAMANAGER->setCameraX(1849);
	if (CAMY > 55 && CAMX > 2816) CAMERAMANAGER->setCameraX(2816);
	if (CAMY != 55 && CAMX == 2816 && !_mapChanging)
	{
		_pl->getJumpPower() = 0;
		_tempX = _pl->getGroundX();
		_mapChanging = true;
	}

	_playerHeight = _pl->getGroundRc().bottom - _pl->getGroundRc().top;
	_playerWidth = _pl->getGroundRc().right - _pl->getGroundRc().left;
	if (_pl->getGroundRc().bottom < CAMY + 442)
	{
		_pl->getGroundY() = CAMY + 442 - _playerHeight / 2;
		_pl->getFlyY() = CAMY + 442 - _playerHeight / 2;
	}
	if (_pl->getGroundRc().bottom > CAMY + WINSIZEY)
	{
		_pl->getGroundY() = CAMY + WINSIZEY - _playerHeight / 2;
		_pl->getFlyY() = CAMY + WINSIZEY - _playerHeight / 2;
	}
	if (_pl->getGroundRc().left < CAMX)
	{
		_pl->getGroundX() = CAMX + _playerWidth / 2;
		_pl->getFlyX() = CAMX + _playerWidth / 2;
	}
	if (_pl->getGroundRc().right > CAMX + WINSIZEX)
	{
		_pl->getGroundX() = CAMX + WINSIZEX - _playerWidth / 2;
		_pl->getFlyX() = CAMX + WINSIZEX - _playerWidth / 2;
	}

	if (_mapChanging && CAMY > 55)
	{
		CAMERAMANAGER->setCameraY(CAMY - 20);
		_pl->setState(JUMP);
		_pl->getGroundX() = _tempX;
		_pl->getGroundY() -= 20;
		_pl->getJumpPower() = 20;
		_pl->getFlyX() = _tempX;
		_pl->getFlyY() = _pl->getGroundY() - 21;
		if (CAMY < 55)
		{
			CAMERAMANAGER->setCameraY(55);
			_mapChanging = false;
			SOUNDMANAGER->stop("메인브금");
			SOUNDMANAGER->play("보스등장");
		}
	}
	if (CAMY < 700) // 루프렌더용
	{
		_loopRc = RectMake(2040, 55, 4691, 500);
		_loopX += 10;
		if (_loopX >= 1024) _loopX -= 1024;
		if (_loopCount < 6 && _loopY > 0) ++_loopCount;
		if (_loopCount >= 6)
		{
			_loopCount = 0;
			--_loopY;
		}
	}
	if (CAMY==55 &&!SOUNDMANAGER->isPlaySound("보스등장") && !SOUNDMANAGER->isPlaySound("보스브금")) SOUNDMANAGER->play("보스브금");
	if (_redCount < 29) ++_redCount;
	else _redCount = 0;


	if (CAMX >= MAPSIZEX - WINSIZEX) SCENEMANAGER->changeScene("엔딩씬");
}

