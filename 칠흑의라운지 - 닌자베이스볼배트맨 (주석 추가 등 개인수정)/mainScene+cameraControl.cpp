#include "stdafx.h"
#include "mainScene.h"

void mainScene::cameraControl()
{
	RECT temp = _pl->getGroundRc();
	if (_em->getVEnemy().size() == 0) CAMERAMANAGER->cameraLockOff();
	else CAMERAMANAGER->cameraLock(); // 적이 있으면 캠고정, 적이 없으면 캠고정 풂
	CAMERAMANAGER->focusOnRect(temp, 3);
	if (CAMY <= 55 && CAMX < 1849) CAMERAMANAGER->setCameraX(1849);
	if (CAMY > 55 && CAMX > 2816) CAMERAMANAGER->setCameraX(2816);
	// 맵밖 카메라 가는거 막는 역할
	if (CAMY != 55 && CAMX == 2816 && !_mapChanging)
	{
		_pl->getJumpPower() = 0;
		_tempX = _pl->getGroundX();
		_mapChanging = true;
	}

	_playerHeight = _pl->getGroundRc().bottom - _pl->getGroundRc().top;
	_playerWidth = _pl->getGroundRc().right - _pl->getGroundRc().left;
	// 플레이어가 화면 일정범위내만 이동하도록 막음
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
	{ // 맵바뀌는중(2층으로)
		CAMERAMANAGER->setCameraY(CAMY - 20);
		_pl->setState(JUMP);
		_pl->getGroundX() = _tempX;
		_pl->getGroundY() -= 20;
		_pl->getJumpPower() = 20;
		_pl->getFlyX() = _tempX;
		_pl->getFlyY() = _pl->getGroundY() - 21;
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
	if (_redCount < 29) ++_redCount;
	else _redCount = 0; // 빨피 카운트

	// 몹젠
	if (_phase == NO_PHASE && CAMX > 500)
	{
		_phase = FIRST_PHASE;
		_em->createMinion(- 100, 500);
		_em->createMinion(WINSIZEX + 100, 500);
		_em->createMinion(WINSIZEX + 100, 700);
	}
	else if (_phase == FIRST_PHASE && CAMX > 2300)
	{
		_phase = SECOND_PHASE;
		_em->createMinion2(- 200, 500);
		_em->createMinion2(WINSIZEX + 100, 500);
		_em->createMinion2(WINSIZEX + 100, 700);
	}
	else if (_phase == SECOND_PHASE && CAMX > 3500)
	{
		_phase = THIRD_PHASE;
		_em->createMinion3(- 100, 500);
		_em->createMinion3(WINSIZEX + 100, 500);
		_em->createMinion3(WINSIZEX + 100, 700);
	}
	else if (_phase == THIRD_PHASE && _em->getVEnemy().size() == 0)
	{
		_phase = BOSS_PHASE;
		_em->createBoss(WINSIZEX + 200, 500);
		// 의자 출력 추가 부분. 
		for (int i = 0; i < 3; i++)
		{
			_sm->createChair(3100 + (i * 360), 465);
		}
		for (int i = 0; i < 3; i++)
		{
			_sm->createChair(3135 + (i * 360), 490);
			for (int j = 0; j < 3; j++)
			{
				_sm->createChair(3300 + (j * 355), 760);
			}
		}
	}
	else if (_phase == BOSS_PHASE && _bossHpRatio <= 0)
	{
		_phase = END_PHASE;
		_im->createBat((_em->getVEnemy()[0]->getRect().left + _em->getVEnemy()[0]->getRect().right) / 2, _em->getVEnemy()[0]->getY());
		_im->createFood(_em->getVEnemy()[0]->getRect().left + 150, _em->getVEnemy()[0]->getY());
		_im->createFood(_em->getVEnemy()[0]->getRect().right - 150, _em->getVEnemy()[0]->getY());
		_im->createFood(_em->getVEnemy()[0]->getRect().left  + 70, _em->getVEnemy()[0]->getY());
		_im->createFood(_em->getVEnemy()[0]->getRect().right - 70, _em->getVEnemy()[0]->getY());
		_im->createFood((_em->getVEnemy()[0]->getRect().left + _em->getVEnemy()[0]->getRect().right) / 2, _em->getVEnemy()[0]->getY()+120);
	}
	
	for (int i = 0; i < _im->getVItem().size(); i++)
	{// 배트먹으면 엔딩
		if (IntersectRect(&temp, &_pl->getShadow(), &_im->getVItem()[i]->getShadow()))
		{
			if (KEYMANAGER->isStayKeyDown('C'))
			{
				if (_im->getVItem()[i]->getID() == 0 && !_im->getVItem()[i]->isFood())
				{
					_ending = true;
					break;
				}
			}
		}
	}
	if (_ending)
	{ // 일정시간이후 엔딩으로
		_time += TIMEMANAGER->getElapsedTime();
	}
	if (_time > 3.4f)
	{
		CAMERAMANAGER->cameraLockOff();
		CAMERAMANAGER->setCameraX(0);
		CAMERAMANAGER->setCameraY(0);
		SCENEMANAGER->changeScene("엔딩씬");
	}
	if ((_playerHpRatio <= 0 || _timeLimit <= 0) && _pl->getEnumState() != DEAD)
	{ // 플레이어 죽음처리
		_pl->setState(DEAD);
		_pl->getPlHP() = 0;
		--_life;
		if (_life < 0) _life = 0;
	}
	if (_pl->getEnumState() == DEAD && KEYMANAGER->isStayKeyDown(VK_RETURN))
	{ // 플레이어 리젠
		_timeLimit = 99;
		_pl->setState(JUMP);
		_pl->getPlHP() = 100;
		_pl->getGroundX() = CAMX + 100;
		_pl->getGroundY() = CAMY + 500;
		_pl->getFlyX() = CAMX + 100;
		_pl->getFlyY() = CAMY - 200;
	}



	if (KEYMANAGER->isOnceKeyDown(VK_ADD))
	{
		if (_volume < 1.0f) _volume += 0.1f;
		SOUNDMANAGER->setVolume(_volume);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SUBTRACT))
	{
		if (_volume > 0.0f) _volume -= 0.1f;
		SOUNDMANAGER->setVolume(_volume);
	}

}

