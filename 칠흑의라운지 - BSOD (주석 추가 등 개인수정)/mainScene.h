#pragma once
#include "gameNode.h"
#include "stageManager.h"
#include "unitManager.h"
#include "skillNEffectManager.h"
#include "interaction.h"

class mainScene :public gameNode
{
private:
	image*					_backGround;
	stageManager*			_sm;
	unitManager*			_um;
	skillNEffectManager*	_se;
	interaction*			_ia;

	int _alpha; // 밝아지며 등장시키려고

public:
	mainScene();
	~mainScene();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
	
	unitManager* getUM() { return _um; } // 이건 플레이그라운드에서 미니맵 그리라고 있는거

	
};

