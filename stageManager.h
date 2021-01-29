#pragma once
#include "gameNode.h"
#include "tile.h"
#include "unitManager.h"

enum STAGE
{
	STAGE1,
	STAGE2,
	STAGE3
};

enum STAGEMOVE
{
	S_MOVE, S_UNMOVE
};

enum tileObj
{
	S_NONE, S_TREE1, S_TREE2, S_TREE3, S_TREE4, S_TREE5, S_ZERGLING = 11
};

class stageManager : public gameNode
{
private:
	isoTile _isoTile[TILEX*TILEY];
	STAGE _stage;
	int _gold; // 좋은 구조인진 모르겠지만 골드는 스테이지매니저에서 관리하기로 했음

	unitManager* _um;
	bool _battlePhase; // 이게 false면 배치페이즈 true면 교전페이즈
	
public:
	stageManager();
	~stageManager();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
	void objectRender();    //오브젝트 그리는건 따로 뻄. 왜냐면 유닛 다음에 그려줘야하므로

	void setStage(STAGE stage);
	isoTile* getIsoTile() { return _isoTile; }		//타일이 가진 오브젝트 속성 게터
	void umLink(unitManager * um) { _um = um; }
};

