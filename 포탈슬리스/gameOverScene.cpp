#include "stdafx.h"
#include "gameOverScene.h"

gameOverScene::gameOverScene()
{
}

gameOverScene::~gameOverScene()
{
}

HRESULT gameOverScene::init()
{
	CAMERAMANAGER->setCameraX(0);
	char temp[128];	ZeroMemory(temp, sizeof(temp));
	vector<string> vStr;
	vStr = TXTDATA->txtLoad("기록.txt");
	_score = atoi(vStr[0].c_str());
	_highScore = atoi(vStr[1].c_str());
	return S_OK;
}

void gameOverScene::release()
{
}

void gameOverScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		PostQuitMessage(0);
	}
}

void gameOverScene::render()
{
	FINDIMG("게임오버씬")->render(getMemDC());
	FINDIMG("숫자")->frameRender(getMemDC(), 441, 318, _score / 100 % 10, 0);
	FINDIMG("숫자")->frameRender(getMemDC(), 465, 318, _score / 10 % 10, 0);
	FINDIMG("숫자")->frameRender(getMemDC(), 489, 318, _score % 10, 0);
	FINDIMG("숫자")->frameRender(getMemDC(), 441, 389, _highScore / 100 % 10, 0);
	FINDIMG("숫자")->frameRender(getMemDC(), 465, 389, _highScore / 10 % 10, 0);
	FINDIMG("숫자")->frameRender(getMemDC(), 489, 389, _highScore % 10, 0);
	if (_score == _highScore && _score != 0) FINDIMG("기록갱신")->render(getMemDC(), 530, 270);
}
