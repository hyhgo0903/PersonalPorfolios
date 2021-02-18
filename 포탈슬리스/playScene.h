#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "UIManager.h"
#include "itemManager.h"
#include "bulletManager.h"
#include "enemyManager.h"

#pragma warning(disable:4996) // itoa를 쓰고싶어요..

class playScene : public gameNode
{
private:	
	playerManager*	_pm;
	UIManager*		_um;
	itemManager*	_im;
	bulletManager*	_bm;
	enemyManager*	_em;
	int _scoreSum;
	int _highScore;
	int _goCount; // 카메라 안막혔는데 멍때릴경우 이게 계속 올라가며 일정시간 이상이면 재촉하는 그림이 나온다.
	int _goFrameX; // 재촉하는거 프레임용
	int _idleTime; // 이게 쌓여야 재촉을 함
	float _wind; // um의 바람값을 받아서 bm,im에 공급

public:
	playScene();
	~playScene();

	HRESULT init(int data);	//초기화 전용 함수
	HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void interfaceRender(); // 미니맵은 가장 마지막에 그려져야 하므로 여기서 가장 마지막에 그리기로 함
	void saveRecord();
};

