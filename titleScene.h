#pragma once
#include "gameNode.h"
class titleScene : public gameNode
{
private:

	image* _image;
	RECT _gameStart;
	RECT _mapTool;
	RECT _option;
	RECT _exit;
	POINT _point;

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

