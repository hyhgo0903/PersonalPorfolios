#pragma once
#include "gameNode.h"
#include "zergling.h"
#include "civilian.h"
#include "marine.h"
#include "templar.h"
#include "bishop.h"
#include "ghost.h"
#include <vector>
#include "stageManager.h"

class unitManager : public gameNode
{
private:
	vector<unit*> _vUnit;
	vector<unit*>::iterator _viUnit;

public:
	unitManager();
	~unitManager();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	vector<unit*> getVUnit() { return _vUnit; }
	vector<unit*>::iterator getViUnit() { return _viUnit; }

	stageManager*	_sm;

	void reRender();

	void chanhoUpdate();
	void deokhoUpdate();
	void hyunjeongUpdate();
	void yoonghoUpdate();
	void younghanUpdate();

	// 피0이하면 죽음으로만들고 죽었는데 일정프레임이상이면 지움
	void deadErase();
	void progressBarRender();

	void createZergling(BELONG belong, float x, float y);
	void createCivilian(BELONG belong, float x, float y);
	void createMarine(BELONG belong, float x, float y);
	void createTemplar(BELONG belong, float x, float y);
	void createBishop(BELONG belong, float x, float y);
	void createGhost(BELONG belong, float x, float y);

	void setLinkSm(stageManager* sm) { _sm = sm; }			//스테이지 매니저랑 링크시켜줌 그래야 타일의 속성을 체크가능함
};

