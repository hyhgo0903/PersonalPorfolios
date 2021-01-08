#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "player.h"
#include "stageManager.h"
#include "itemManager.h"
#include "collision.h"
#include <vector>

class mainScene : public gameNode
{
private:
	enemyManager*	_em;
	stageManager*	_sm;
	itemManager*	_im;
	player*			_pl;
	collision*		_cl;

	vector<int> bottomY;
	char _str[128];
	RECT _loopRc;  int _loopX;	int _loopY; int _loopCount; // 뒷배경 루프렌더용
	bool _mapChanging; // 맵이 바뀌는 중인지(위로 올라가는 효과)
	int _timeLimit; int _timeCount; // 제한시간
	int _life;
	int _score;

public:
	mainScene();
	~mainScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void zOrderRender();
	void cameraControl();
	void uiRender();
	void plusScore(int x) { _score += x; }
};

