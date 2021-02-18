#pragma once
#include "image.h"

#define GRAVITY 0.2f
#define MAXWIND 1.0f
#define SNOWMAX 25

//백버퍼라는 빈 비트맵 이미지를 하나 생성해둔다
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", MAPSIZEX, MAPSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;		//매니저 초기화 할껀지 유무

public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();			//초기화 전용 함수
	virtual HRESULT init(bool managerInit);
	virtual HRESULT init(int x);    //여기서 만들어줘야하는구나..
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render();			//그리기 전용

	
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

