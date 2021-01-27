#pragma once
#include "gameNode.h"

enum S_BELONG
{
	S_PLAYER,
	S_ENEMY
};

class skillNEffect :	public gameNode
{ // 유닛마냥 복잡하진 않으므로 일단 뼈대는 대충 마련함
protected:
	int _ID;
	S_BELONG _belong;
	float _x; float _y;
	RECT _rc;
	int _frame;
	int _maxFrame;
	int _frameCount;
	int _duration; // 지속시간
	bool _erase;

	image* _image;

public:
	skillNEffect();
	~skillNEffect();

	virtual HRESULT init(S_BELONG belong, float x, float y);	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	inline void commonRelease() { SAFE_DELETE(_image); }
	void commonInit();
	void commonUpdate();

	int getID() { return _ID; }
	S_BELONG getBelong() { return _belong; }
	float& getX() { return _x; }
	float& getY() { return _y; }
	RECT getRect() { return _rc; }
	int getDuration() { return _duration; }
	bool getErase() { return _erase; }
};

