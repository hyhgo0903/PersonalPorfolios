#pragma once
#include "enemy.h"

class minion3 : public enemy
{
private:

public:
	minion3();
	~minion3();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void enemyState();				//enemy의 상태에따라 특정기능을 수행시켜주는 함수
	void enemyStateRender();		//enemy의 상태에따라 렌더를 관리해주는 함수
};

