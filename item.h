#pragma once
#include "gameNode.h"


class item :public gameNode
{
protected:
	RECT _rc;
	float _x; float _y;
	image* _image;

	bool _pickup; //들고있나요?->손에 쥐고 있을 때 쓸 거임.
	bool _moving; //움직이나요?->던지는 거 처리에 쓸 거임.
public:
	item();
	~item();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void fillColorEllipse(int R, int G, int B, RECT rc);
	RECT getRect() { return _rc; }

	//아래는 둘 다 매니저에서 사용할 함수임.
	//던지면 발생하도록함. 방향을 지정해주면(true : 오른쪽, false : 왼쪽) x, y로 움직이도록 함.
	virtual void attackMove(bool direction);
	//아이템을 들고 있는지 판단할 함수. true:들고 있음. false:들고 있지 않음. x, y : 들고다닐 때 위치 조정.
	virtual void setHold(bool holding, float x, float y);
	
};

