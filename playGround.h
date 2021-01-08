#pragma once
#include "mainScene.h"
#include "endingScene.h"
#include "titleScene.h"
#include "videoScene.h"

class playGround : public gameNode
{
private:
	bool _videoPlaying;

public:
	playGround();
	~playGround();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void imageInitChanho();
	void imageInitDeokho();
	void imageInitHyunjeong();
	void imageInitYoongho();
	void imageInitYounghan();
};

