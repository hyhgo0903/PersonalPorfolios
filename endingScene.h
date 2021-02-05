#pragma once
#include "gameNode.h"

enum RESULT
{
	VICTORY,
	DEFEAT
};

class endingScene : public gameNode
{
private:

	RECT _mainSelectRc;
	RECT _exitSelectRc;
	RECT _mainRc;
	RECT	_exitRc;
	RECT	_retryRc;
	RESULT _result;
	int _score;

public:
	endingScene();
	~endingScene();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
};

