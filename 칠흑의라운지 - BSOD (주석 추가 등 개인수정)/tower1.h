#pragma once
#include "unit.h"
class tower1 :
	public unit
{
public:
	tower1();
	~tower1();

	virtual HRESULT init(BELONG belong, float x, float y);	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
	virtual void reRender();

	virtual void setState(STATE state);
};

