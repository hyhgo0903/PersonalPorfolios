#pragma once
#include "gameNode.h"
#include "stageManager.h"
#include "unitManager.h"
#include "skillNEffectManager.h"
#include <vector>

struct tagAStarTile
{
	int tileNum;
	int parentNodeTileNum;
	int totalCost;
	int costFromStart;
	int costToGoal;
	bool isOpen;
};

class interaction :	public gameNode
{
private:
	stageManager*			_sm;
	unitManager*			_um;
	skillNEffectManager*	_se;

	vector<tagAStarTile*>			_vTotalList;
	vector<tagAStarTile*>::iterator _viTotalList;
	vector<tagAStarTile*>			_vOpenList;
	vector<tagAStarTile*>::iterator _viOpenList;
	vector<tagAStarTile*>			_vCloseList;
	vector<tagAStarTile*>::iterator _viCloseList;
	vector<int> _path;
	
	int _startTile;		//시작타일의 번호
	int _endTile;			//도착타일
	int _currentTile;		//현재타일

	bool _stop; // 못찾은거
	
public:
	interaction();
	~interaction();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void chanhoInit();		void chanhoUpdate();	void chanhoRender();
	void deokhoInit();		void deokhoUpdate();	void deokhoRender();
	void hyunjeongInit();	void hyunjeongUpdate();	void hyunjeongRender();
	void yoonghoInit();		void yoonghoUpdate();	void yoonghoRender();
	void younghanInit();	void younghanUpdate();	void younghanRender();
	
	void smLink(stageManager* sm) { _sm = sm; }
	void umLink(unitManager* um) { _um = um; }
	void seLink(skillNEffectManager* se) { _se = se; }

	inline POINT picking(long x, long y);

	vector<int> aStarPath(int fromTileNum, int toTileNum);

	//갈수 있는 길을 찾아내서 담아줄 함수
	vector<tagAStarTile*> addOpenList(int currentTile);
	//빠른 경로 찾을 함수
	void pathFinder(int currentTile);
};

