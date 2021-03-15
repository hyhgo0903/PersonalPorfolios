#include "stdafx.h"
#include "mainScene.h"

mainScene::mainScene()
{
}

mainScene::~mainScene()
{
}

HRESULT mainScene::init()
{
	_phase = NO_PHASE; _ending = false;
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(MAPSIZEY - WINSIZEY);
	_loopX = 0;	_loopY = 300; _loopCount = _timeCount = _score = _redCount = 0;
	_timeLimit = 99; _life = 3;
	_bossHpRatio = _playerHpRatio = 1.0f;
	_mapChanging = false;
	_pl = new player;		_pl->init();
	_em = new enemyManager;	_em->init();
	_sm = new stageManager; _sm->init();
	_im = new itemManager;	_im->init();
	_cl = new collision;	_cl->init();

	_cl->setPlMemoryAddressLink(_pl);
	_cl->setEmMemoryAddressLink(_em);
	_cl->setSmMemoryAddressLink(_sm);
	_cl->setImMemoryAddressLink(_im);
	_pl->setLinkEnemy(_em);
	_em->setLinkPlayer(_pl);

	SOUNDMANAGER->play("메인브금");
	_time = 0.0f;
	_volume = 1.0f;
	return S_OK;
}

void mainScene::release()
{
	_cl->release();
	_pl->release();
	_em->release();
	_sm->release();
	_im->release();
}

void mainScene::update()
{

	_pl->update();
	_em->update();
	_sm->update();
	_im->update();
	_cl->update();
	cameraControl();
	if (_timeCount < 120) ++_timeCount;
	else
	{
		_timeCount = 0;
		--_timeLimit;
	}
}

void mainScene::render()
{
	//FINDIMG("맵")->render(getMemDC()); //이렇게 하지 않고 아래처럼 화면부분만 갖고오게 하였음(클리핑)
	FINDIMG("맵")->render(getMemDC(), CAMX, CAMY, CAMX, CAMY, WINSIZEX, WINSIZEY);

	if (CAMY < 700) FINDIMG("창문배경")->loopRender(getMemDC(), &_loopRc, _loopX, _loopY + rand() % 4);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		TIMEMANAGER->render(getMemDC(), CAMX, CAMY);
	}
	_pl->render();
	_cl->render(); // 다른 벡터들은 z오더 함수에서 그리게 되어 있음.

	zOrderRender();
	
	if (CAMX > 2060 - WINSIZEX && CAMX < 2133)FINDIMG("기둥")->render(getMemDC(), 2060, 1536);
	uiRender(); // 길어질거같아서 따로 뺴다씀

	_pl->reRender();
	
	FINDIMG("볼륨바")->render(getMemDC(), CAMX + WINSIZEX - 58, CAMY + 5, 0, 0, 53 * _volume, 5);
}