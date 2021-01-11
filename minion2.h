#pragma once
#include "enemy.h"

class minion2 : public enemy
{
private:

public:
	minion2();
	~minion2();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void enemyState();				//적과 플레이어의 위치를 비교하여 상태값을 관리함
	void enemyStateRender();		//가독성을 위해 렌더함수로 따로 관리함
	void keyManager();				//그냥 나 편하려고만든 테스트용
};

