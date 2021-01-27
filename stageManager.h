#pragma once
#include "gameNode.h"
#include "tile.h"

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
	STAGEMOVE			_sMove[TILEX * TILEY];					//맵툴에서 가져온 속성이 무브인지 언무브인지 담아둘 곳
	tileObj				_tileObj[TILEX * TILEY];				//맵툴에서 가져온 오브젝트 속성이 무엇인지 담아둘 곳

public:
	stageManager();
	~stageManager();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void setStage(STAGE stage);
	isoTile* getIsoTile() { return _isoTile; }
	STAGEMOVE* getStageMove() { return _sMove; }				//무브 ,언무브 게터
	tileObj* getTileObj() { return _tileObj; }					//타일이 가진 오브젝트 속성 게터
};

