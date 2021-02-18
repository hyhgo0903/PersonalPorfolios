#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);
	imageInit();	
	SCENEMANAGER->addScene("¼¿·ºÆ®¾À", new selectScene);
	SCENEMANAGER->addScene("ÇÃ·¹ÀÌ¾À", new playScene);
	SCENEMANAGER->addScene("°ÔÀÓ¿À¹ö¾À", new gameOverScene);
	SCENEMANAGER->addScene("½Â¸®¾À", new victoryScene);
	SCENEMANAGER->changeScene("¼¿·ºÆ®¾À");
	return S_OK;
}


void playGround::release()
{
	gameNode::release();
	SCENEMANAGER->release();
}

void playGround::update()
{
	gameNode::update();
	SCENEMANAGER->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, GETCAM+WINSIZEX, WINSIZEY, WHITENESS);
	//================ À§¿¡ °ÇµéÁö ¸¶¶ó ==============================
	SCENEMANAGER->render();
	//================= ¾Æ·¡µµ °ÇµéÁö ¸¶¶ó ==============================
	_backBuffer->render(getHDC(), 0, 0, GETCAM, CAMERAMANAGER->getCameraY(), WINSIZEX, WINSIZEY);
}