#pragma once
#include "gameNode.h"
class titleScene : public gameNode
{
private:

	image* _titleImage;
	image* _volumeSetImage;
	RECT _gameStart;
	RECT _mapTool;
	RECT _option;
	RECT _exit;
	RECT _volumeExit; 
	RECT _volumRect;
	POINT _point;

	RECT _testBgm;
	RECT _testEffect;

	RECT _bgmPlus;
	RECT _bgmBar;
	RECT _bgmMinus;
	RECT _effectPlus;
	RECT _effectBar;
	RECT _effectMinus;

	bool _isVolumeSetOn;

public:
	titleScene();
	~titleScene();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	RECT getGameStart() { return _gameStart; }
	RECT getMaptool() { return _mapTool; }
	RECT getOption() { return _option; }
	RECT getExit() { return _exit; }
};

