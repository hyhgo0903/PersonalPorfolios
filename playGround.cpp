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
	srand(time(NULL));
	imageInitChanho(); imageInitDeokho(); imageInitHyunjeong(); imageInitYoongho(); imageInitYounghan();
	SCENEMANAGER->addScene("메인씬", new mainScene);
	SCENEMANAGER->addScene("타이틀씬", new titleScene);
	SCENEMANAGER->addScene("엔딩씬", new endingScene);
	SCENEMANAGER->addScene("비디오씬", new videoScene);

	//SCENEMANAGER->changeScene("비디오씬");
	//_videoPlaying = true;
	SCENEMANAGER->changeScene("타이틀씬");
	_videoPlaying = false;
	
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

	if (_videoPlaying)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RETURN))
		{
			_videoPlaying = false;
			SCENEMANAGER->changeScene("타이틀씬");
		}
	}

	SCENEMANAGER->update();	
	EFFECTMANAGER->update();
}


void playGround::render()
{
	if (!_videoPlaying) PatBlt(getMemDC(), 0, 0, CAMX+WINSIZEX, CAMY+WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	SCENEMANAGER->render();
	EFFECTMANAGER->render();
	
	//================= 아래도 건들지 마라 ==============================
	if (!_videoPlaying) _backBuffer->render(getHDC(), 0, 0, CAMX, CAMY, WINSIZEX, WINSIZEY);
}

