#pragma once
#include "unit.h"
class templar :
	public unit
{
private:
	RECT _afterImage;
	POINT _afterImagePt;
	int _afterImageFrame;
	int _afterImageFrameDirection;
	int _afterImageCount;

public:
	templar();
	~templar();

	virtual HRESULT init(BELONG belong, float x, float y);	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
	virtual void reRender();

	virtual void setState(STATE state);
};

