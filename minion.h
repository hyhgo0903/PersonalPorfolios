#pragma once
#include "enemy.h"

// 클래스명 맘에 안들면 없애도 됨. 그저 예시일 뿐이니까..
class minion :	public enemy
{
private:

public:
	minion();
	~minion();
	int _plAtkNum;				//테스트용 플레이어 공격상태

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void enemyState();				//적과 플레이어의 위치를 비교하여 상태값을 관리함
	void enemyStateRender();		//가독성을 위해 렌더함수로 따로 관리함
	void keyManager();				//그냥 나 편하려고만든 테스트용
};
