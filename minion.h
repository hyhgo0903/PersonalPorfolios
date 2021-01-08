#pragma once
#include "enemy.h"

// 클래스명 맘에 안들면 없애도 됨. 그저 예시일 뿐이니까..
class minion :	public enemy
{
private:

public:
	minion();
	~minion();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	//void imageRect();				//이미지상태에 따라 렉트크기를 변환함
	void move();					//적의 움직임을 관리함
	void enemyState();				//적과 플레이어의 위치를 비교하여 상태값을 관리함
};
