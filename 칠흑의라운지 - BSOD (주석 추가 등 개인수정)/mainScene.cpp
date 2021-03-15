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
	CAMERAMANAGER->setCameraY((MAPSIZEY-WINSIZEY)/2);
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
	_sm->seLink(_se);								//스테이지 이동과함께 지우려고
	_sm->umLink(_um);								//유닛 매니저와 스테이지 매니저를 링크로 연결해줌
	_sm->setStage(STAGE1);

	/*_um->createBishop(PLAYER, 960, 16);
	_um->getVUnit()[0]->setVPath(_ia->aStarPath(0, 899));
	_um->getVUnit()[0]->getTileNum() = 0;
	_um->createCivilian(ENEMY, 960, 944);
	_um->getVUnit()[1]->setVPath(_ia->aStarPath(899, 0));
	_um->getVUnit()[1]->getTileNum() = 899;*//*
	_um->createZergling(PLAYER, 310, 530);
	_um->createMarine(ENEMY, 1350, 400);
	_um->createMarine(PLAYER, 110, 370);
	_um->createMarine(ENEMY, 1350, 500);
	_um->createMarine(PLAYER, 110, 500);
	_um->createCivilian(ENEMY, 1100, 450);
	_um->createCivilian(PLAYER, 110, 600);
	_um->createTemplar(PLAYER, 200, 480);
	_um->createBishop(ENEMY, 1200, 600);
	_um->createBishop(PLAYER, 200, 350);
	_um->createGhost(PLAYER, 250, 400);
	_um->createGhost(ENEMY, 1250, 650);*/
	// _um->createTower1(ENEMY, 450, 450);

	// _um->createDiablo(ENEMY, 650, 450);

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
	{ // 죽음애니메이션 빨리보기용도
		for (int i = 0; i < _um->getVUnit().size(); ++i)
		{
			_um->getVUnit()[i]->setState(DEAD);
		}
	}
}

void mainScene::render()
{// 서순이 왜 이런지 주석을 달았습니다
	_sm->render();			// 맵타일을 그려줍니다
	_um->render();			// 유닛들을 그려줍니다
	_sm->objectRender();	// 유닛이 가려지게 오브젝트는 여기서 그립니다
	_um->reRender();		// 유닛을 반투명하게 그립니다(가려진건 반투명)
	_se->render();			// 스킬과 이펙트는 유닛 나중에 그립니다
	_um->progressBarRender(); // 체력바는 안가려지게끔 그 다음에 그립니다
	_sm->uiRender();		// ui는 가장 마지막에 그립니다
}