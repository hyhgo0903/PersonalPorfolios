#pragma once
#include "gameNode.h"

#define ITEMDURMAX 800 // 최대 지속시간

class droppedItem : public gameNode
{
private: //상속할거면 protected로
	bool _stateType; // 상태템인지?
	bool _landed;	// 착륙했는지?
	int _frameX;	// 상자면 프레임돌음
	int _itemType;	// 이넘 또 쓰다간 중복선언..
	// 0,1,2,3 : 사용템 DOUBLEFIRE, POWERUP, SHIELD, REPAIR
	// 0,1,2 : ITEMCANNON, ITEMMISSILE, ITEMMULTI
	bool _disappear;
	RECT _rc;
	float _x, _y, _xSpd, _ySpd; // x,y중점과 속도
	int _durCount; // 지속시간 (지나면 흐려지고 사라짐) 상자면 프레임카운트용으로도 활용
	int _alphaValue; // 흐려진다앗

public:
	droppedItem();
	~droppedItem();

	HRESULT init(bool stateType, float x, float y);
	void release();
	void update();
	void render();

	void move();

	//호잇!
	inline RECT getRect() { return _rc; } // 플레이어와 충돌(?)용
	bool& getDisappear() { return _disappear; } // 사라질거면 사라진다고 알려줌
	float& getXSpd() {	return _xSpd;} // 바람에 따라 바꿔줄 값
	int getItemType() { return _itemType; }
};