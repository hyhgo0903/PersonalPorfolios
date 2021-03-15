#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "loadingScene.h"
#include "mainScene.h"
#include "titleScene.h"
#include "endingScene.h"


class playGround : public gameNode
{
private:
	float _x; int _y;
	bool _seeMinimap;
	image* _backGround;

	mainScene* _ms;
	RECT	_camMap;

	int _cursorCount;
	int _cursorIndex;
	
public:
	playGround();
	~playGround();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
	
	void yoonghoUpdate();
	void uiRender();
};

