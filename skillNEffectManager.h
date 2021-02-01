#pragma once
#include "gameNode.h"
#include <vector>
#include "flague.h"
#include "psionic.h"
#include "heal.h"

class skillNEffectManager :	public gameNode
{
private:
	vector<skillNEffect*> _vSne;
	vector<skillNEffect*>::iterator _viSne;

public:
	skillNEffectManager();
	~skillNEffectManager();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void createPsionic(S_BELONG belong, float x, float y);
	void createPlague(S_BELONG belong, float x, float y);
	void createHeal(S_BELONG belong, float x, float y);

	vector<skillNEffect*> getVSne() { return _vSne; }
	vector<skillNEffect*>::iterator getViSne() { return _viSne; }
};

