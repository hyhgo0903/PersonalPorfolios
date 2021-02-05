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

	_x = _y = _seeMinimap = 0;

	_ms = new mainScene;

	SCENEMANAGER->addScene("로딩씬", new loadingScene);
	SCENEMANAGER->addScene("메인씬", _ms);
	SCENEMANAGER->addScene("맵툴", new mapTool);
	SCENEMANAGER->addScene("타이틀씬", new titleScene);
	SCENEMANAGER->addScene("엔딩씬", new endingScene);
	
	SCENEMANAGER->changeScene("로딩씬");
	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();

	if (SCENEMANAGER->getMinimapScene() && !_seeMinimap)
	{
		_seeMinimap = true;
	}
	else if (!SCENEMANAGER->getMinimapScene() && _seeMinimap)
	{
		_seeMinimap = false;
	}

	if (KEYMANAGER->isStayKeyDown(VK_ADD) && _x < 300)
	{
		_x += 12;
		_y += 7;
	}
	if (KEYMANAGER->isStayKeyDown(VK_SUBTRACT) && _x > 0)
	{
		_x -= 12;
		_y -= 7;
	}
	if (!_seeMinimap && (CAMX != 0 || CAMY != 0))
	{
		CAMERAMANAGER->setCameraX(0);
		CAMERAMANAGER->setCameraY(0);
	}

	yoonghoUpdate();
	SCENEMANAGER->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, CAMX + WINSIZEX, CAMY + WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	SCENEMANAGER->render(); // 얘넨 다 확대축소..
	//================= 아래도 건들지 마라 ==============================
	if (_x == 0) // 확대안하는거면 이렇게 그림
	{
		if (KEYMANAGER->isToggleKey(VK_TAB)) TIMEMANAGER->render(getMemDC(), CAMX, CAMY);
		uiRender();
		if (SCENEMANAGER->getAlpha() > 0) FINDIMG("씬체인지")->alphaRender(getMemDC(), CAMX, CAMY, SCENEMANAGER->getAlpha());
		_backBuffer->render(getHDC(), 0, 0, CAMX, CAMY, WINSIZEX, WINSIZEY);
	}
	else
	{ // 확대축소하고 그리면 사이에 끼워넣어서 그리면 될듯
		_backBuffer->resizedRender(getMemDC(), CAMX, CAMY, CAMX + _x, CAMY + _y, WINSIZEX, WINSIZEY, WINSIZEX - 2 * _x, WINSIZEY - 2 * _y);
		if (KEYMANAGER->isToggleKey(VK_TAB)) TIMEMANAGER->render(getMemDC(), CAMX,CAMY);
		uiRender();
		if (SCENEMANAGER->getAlpha() > 0) FINDIMG("씬체인지")->alphaRender(getMemDC(), CAMX, CAMY, SCENEMANAGER->getAlpha());
		_backBuffer->render(getHDC(), 0, 0, CAMX, CAMY, WINSIZEX, WINSIZEY);
	}
}