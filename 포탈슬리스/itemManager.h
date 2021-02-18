#pragma once
#include "gameNode.h"
#include <vector>
#include "droppedItem.h"
#include "effect.h"

class playerManager; // 이건 상호참조위한 전방선언. 헤더는 cpp파일에 추가돼있음

enum usingItemSlot
{
	DOUBLEFIRE, POWERUP, SHIELD, REPAIR, EMPTY
};

class itemManager : public gameNode
{
private:
	RECT _heliRC; // 상태아이템을 드롭하는 헬기위치(하나만 운용)
	bool _heliAppear; // 헬기가 등장한 상태인지
	bool _heliUp;		// 헬기가 내려올만큼 내려왔는지
	bool _heliArr[MAPSIZEX / 600]; // 600마다 헬기가 등장했는지
	int _heliRegenCount;
	float _wind;
	
	usingItemSlot _usingSlot[4];
	bool _stateSlot[4];

	vector<droppedItem*> _vDroppedItem;
	vector<droppedItem*>::iterator _viDroppedItem; // 필드의 아이템을 관리합니다
	effect* _spdUpEffect;
	effect* _powUpEffect;
	effect* _delDownEffect;
	effect* _scoreUpEffect;

	//이하는 참조를 위해
	playerManager* _pm;
	int _itemScore;

public:
	itemManager();
	~itemManager();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void generateUsingItem(); // 호출 받으면 사용아이템을 드랍한다
	void heliMove();		// 헬기가 최하점에 도달하면 아이템드랍
	void dropUsingItem();
	void dropStateItem(float x, float y); // 호출 받으면 상태아이템을 만든다
	void itemUpdate();
	void getItem(int x);
	void slotRender();

	int getScore() { return _itemScore; }
	void setWind(float wind) { _wind = wind; }

	void test();
	void _getEffect(int x); // 처음 먹을때면 우하하하팡파레(까진 아니고 spd up, pow up, delay down)

	void setPmMemoryAddressLink(playerManager* pm) { _pm = pm; }
	
	bool getStateSlot(int x) { return _stateSlot[x]; } // 보기만 할거니까 참조자 없이 쓰자
	usingItemSlot& getUsingSlot(int x) {	return _usingSlot[x];	} // 비워줘야하니까 참조자 포함해서..
	vector<droppedItem*> getVDroppedItem() { return _vDroppedItem; }
	vector<droppedItem*>::iterator getViDroppedItem() { return _viDroppedItem; }
	RECT getRect() { return _heliRC; }
};

