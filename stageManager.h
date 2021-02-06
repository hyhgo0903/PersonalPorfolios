#pragma once
#include "gameNode.h"
#include "tile.h"
#include "unitManager.h"
#include "skillNEffectManager.h"

struct tagAStarTile
{
	int tileNum;
	int parentNodeTileNum;
	int totalCost;
	int costFromStart;
	int costToGoal;
	bool isOpen;
};

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

enum pickUnit
{
	P_NONE, P_ZERGLING, P_MARINE, P_CIVILIAN, P_TEMPLAR, P_BISHOP, P_GHOST, P_DRAGON, P_NARUTO
};

class stageManager : public gameNode
{
private:
	isoTile _isoTile[TILEX*TILEY];
	STAGE _stage;
	int _gold; // 좋은 구조인진 모르겠지만 골드는 스테이지매니저에서 관리하기로 했음
	POINT _pickingPt;
	POINT _cameraPtMouse; // 걍피티마우스말고 카메라위치 보정한 피티마우스

	RECT	_homeBt;
	RECT	_onBt;
	RECT	_offBt;
	RECT	_startBt;
	RECT	_retryBt;
	RECT	_clearBt;

	//유닛 생성 렉트
	RECT	_zerglingBt;
	RECT	_marineBt;
	RECT	_civilianBt;
	RECT	_templarBt;
	RECT	_bishopBt;
	RECT	_ghostBt;
	RECT	_dragonBt;
	RECT	_narutoBt;

	skillNEffectManager* _se;
	unitManager* _um;
	bool	_battlePhase; // 이게 false면 배치페이즈 true면 교전페이즈
	bool	_menuInPt;			//마우스가 메뉴안에 들어갔을때 불필요한 행동들을 제어하기 위해 만듬
	bool	_onOff;				//유닛구매 메뉴 온오프(게임시작누를때는 자동으로 오프로 변경되야함)
	pickUnit	_pickUnit;
	int _tempGold; //골드 음값으로 되면 이걸 다시 불러옴
	int _playerTile;
	int _enemyTile;
	int _alpha;
	
	int _score;

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

	bool _isVictory;
	bool _isDefeat;

public:
	stageManager();
	~stageManager();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
	void objectRender();    //오브젝트 그리는건 따로 뻄. 왜냐면 유닛 다음에 그려줘야하므로
	void uiRender();		//UI렌더 (최상단 노출을 위해 따로선언)
	void uiRect();			//UI위치에 렉트를 깔아서 기능을 부여해주기위함
	void homeBt();			//홈버튼 기능
	void onOffBt();			//메뉴 ON/OFF 버튼 기능
	void startBt();			//스타트 버튼 기능
	void retryBt();			//리트라이 버튼 기능
	void ptInIso();			//아이소타일안에 마우스가 들어왔는지 판단해줌
	void ptInCreateMenu();	//마우스가 생성 메뉴안에 들어갔을때
	void ptInMenu();		//메뉴안에 마우스가 들어갔는지 체크해주는 기능
	void createUnit();		//유닛 생성하는 코드
	void clearBt();			//클리어버튼 기능

	inline POINT picking(long x, long y); // 피킹하는 함수 

	void setStage(STAGE stage);
	isoTile* getIsoTile() { return _isoTile; }		//타일이 가진 오브젝트 속성 게터


	vector<int> aStarPath(int fromTileNum, int toTileNum);

	//갈수 있는 길을 찾아내서 담아줄 함수
	vector<tagAStarTile*> addOpenList(int currentTile);
	//빠른 경로 찾을 함수
	void pathFinder(int currentTile);

	void umLink(unitManager * um) { _um = um; }
	void seLink(skillNEffectManager * se) { _se = se; }

	void stageChange();
	int getPlayerTile() { return _playerTile; }
};

