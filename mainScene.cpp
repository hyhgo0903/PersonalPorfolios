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
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	_sm = new stageManager;
	_sm->init();
	_um = new unitManager;
	_um->init();
	_se = new skillNEffectManager;
	_se->init();
	_ia = new interaction;
	_ia->init();

	_ia->umLink(_um);
	_ia->smLink(_sm);
	_ia->seLink(_se);

	_um->createZergling(ENEMY, 800, 400);
	_um->createZergling(ENEMY, 900, 400);
	_um->createZergling(ENEMY, 700, 400);
	_um->createZergling(PLAYER, 210, 370);
	_um->createZergling(PLAYER, 310, 530);
	_um->createZergling(PLAYER, 270, 500);
	_um->createMarine(ENEMY, 800, 400);
	_um->createMarine(PLAYER, 110, 370);
	_um->createCivilian(ENEMY, 700, 400);
	_um->createCivilian(PLAYER, 110, 370);
	_um->createTemplar(ENEMY, 800, 480);
	_um->createTemplar(PLAYER, 200, 480);
	_um->createBishop(ENEMY, 800, 400);
	_um->createBishop(PLAYER, 200, 350);

	_um->setLinkSm(_sm);								//유닛 매니저와 스테이지 매니저를 링크로 연결해줌

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		if (_sm->getTileObj()[i] == ZERGLING)
		{
			_um->createZergling(ENEMY, _sm->getIsoTile()[i].drawX + 10, _sm->getIsoTile()[i].drawY - 5);
		}
	}


	return S_OK;
}

void mainScene::release()
{
	_sm->release();
	_um->release();
	_se->release();
	_ia->release();
}

void mainScene::update()
{
	_sm->update();
	_um->update();
	_se->update();
	_ia->update();

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < _um->getVUnit().size(); ++i)
		{
			_um->getVUnit()[i]->setState(DEAD);
		}
	}

	yoonghoUpdate();
}

void mainScene::render()
{
	_sm->render();
	_ia->render();
	_um->render();
	_se->render();

	uiRender();

}