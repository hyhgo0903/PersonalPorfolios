#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "stageManager.h"
#include "itemManager.h"

// 이건 모두가 건드려야하는 클래스인데,
// 각자 사용하는 cpp파일에 작업해야 안 꼬일거 같아서 따로 cpp를 마련해두었음.

// 만약 여기다 작업중인데 누가 푸시했다길래 풀받아야 되긴 할텐데
// 내가 어디 작업했는지 모호하면 풀받고 따로 쓰기도 애매하잖아
// 그러니까 각자 파일에 빼와서 하다가 풀받고 했던파일 추가로 넣어서 다시 푸시하는 식으로 하면 될거같음

// 말이 콜리전이지 참조필요한 연산을 죄다 여기 하는걸로 구상했음. 사실상 1번충돌때의 플레이그라운드역할(단방향참조)
// 구상은 이렇게 했지만 참조 필요할떄마다 클래스간 상호참조나 그냥참조걸고 하는건 자유임
// 각자 본인 스타일대로 참조해도 된다고 봄

class collision : public gameNode
{
private:
	player*			_pl;
	enemyManager*	_em;
	stageManager*	_sm;
	itemManager*	_im;

	int _itemOrder; //이걸로 아이템 순서 정해보려고 만듬;

public:
	collision();
	~collision();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void chanhoInit();		void chanhoUpdate();	void chanhoRender();
	void deokhoInit();		void deokhoUpdate();	void deokhoRender();
	void hyunjungInit();	void hyunjungUpdate();	void hyunjungRender();
	void yoonghoInit();		void yoonghoUpdate();	void yoonghoRender();
	void younghanInit();	void younghanUpdate();	void younghanRender();

	void setPlMemoryAddressLink(player* pl)			{ _pl = pl; }
	void setEmMemoryAddressLink(enemyManager* em)	{ _em = em; }
	void setSmMemoryAddressLink(stageManager* sm)	{ _sm = sm; }
	void setImMemoryAddressLink(itemManager* im)	{ _im = im; }
};

