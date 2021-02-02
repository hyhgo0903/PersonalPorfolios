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

	_sm->umLink(_um);								//유닛 매니저와 스테이지 매니저를 링크로 연결해줌
	_sm->setStage(STAGE1);

	/*_um->createBishop(PLAYER, 960, 16);
	_um->getVUnit()[0]->setVPath(_ia->aStarPath(0, 899));
	_um->getVUnit()[0]->getTileNum() = 0;
	_um->createCivilian(ENEMY, 960, 944);
	_um->getVUnit()[1]->setVPath(_ia->aStarPath(899, 0));
	_um->getVUnit()[1]->getTileNum() = 899;*/
	//_um->createZergling(PLAYER, 310, 530);
	//_um->createMarine(ENEMY, 1350, 400);
	//_um->createMarine(PLAYER, 110, 370);
	//_um->createMarine(ENEMY, 1350, 500);
	//_um->createMarine(PLAYER, 110, 500);
	//_um->createCivilian(ENEMY, 1100, 450);
	//_um->createCivilian(PLAYER, 110, 600);
	//_um->createTemplar(PLAYER, 200, 480);
	//_um->createBishop(ENEMY, 1200, 600);
	//_um->createBishop(PLAYER, 200, 350);
	//_um->createGhost(PLAYER, 250, 400);
	//_um->createGhost(ENEMY, 1250, 650);

	 _um->createDiablo(ENEMY, 400, 400);
	/*for (int i = 0; i < _um->getVUnit().size(); i++) // 디아블로 소환실험 1번 (유닛메니저에 2번이 있습니다)
	{
		if (!_um->getVUnit()[i]->getID() == 6) continue;
		if (_um->getVUnit()[i]->getID() == 6 &&
			_um->getVUnit()[i]->getState() == ATTACK &&
			_um->getVUnit()[i]->getState() != WALK &&
			_um->getVUnit()[i]->getState() != ATTACKWAIT &&
			_um->getVUnit()[i]->getState() != DEAD )
		{
			_um->createskeleton(ENEMY, _um->getVUnit()[i]->getX() + RND->getFromIntTo(10, 50), _um->getVUnit()[i]->getY() + RND->getFromIntTo(10, 50));
			_um->createskeleton(ENEMY, _um->getVUnit()[i]->getX() + RND->getFromIntTo(10, 50), _um->getVUnit()[i]->getY() + RND->getFromIntTo(10, 50));
		}
	}*/


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
{// 서순이 왜 이런지 주석을 달았읍니다
	_sm->render();			// 맵그려주구요
	_ia->render();			// 이건 사실 안 그릴듯?
	_um->render();			// 유닛그려줍니다
	_sm->objectRender();	// 유닛이 가려지게끔 오브젝트는 여기서 그리는 거
	_se->render();			// 스킬과 이펙트가 잘 보이게 나중에 그림
	_um->reRender();		// 반투명 유닛이 그려서 가려진건 반투명하게 보임
	_um->progressBarRender(); // 체력바는 안가려지게끔
	_sm->uiRender();
}