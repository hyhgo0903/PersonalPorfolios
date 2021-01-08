#pragma once
#include "gameNode.h"


class item :public gameNode
{
protected:
	RECT _rc;//공중렉트
	float _x; float _y;
	image* _image;

	RECT _rcg;//지상렉트
	float _xg, _yg;
	float _gravity;

	RECT _shadow;//그림자.
	int _distance;//공중렉트, 지상렉트 위치차이.
	float _time;//이미지, 상황 변환용 변수.
	
	float _angle; //이동시 각 이용해서 변하게.

	bool _pickup; //들고있나요?->손에 쥐고 있을 때 쓸 거임.
	bool _moving; //움직이나요?->던지는 거 처리에 쓸 거임.
	bool _delete; //매니저에서 지우라는 신호로 쓸 거임.

public:
	item();
	~item();

	virtual HRESULT init(float x, float y);
	//아이템 생성할 때 이걸로 쓸게요. x, y 공중렉트 중점. bottom = 지상렉트.bottom
	virtual HRESULT init(float x, float y, float bottom);
	virtual void release();
	virtual void update();
	virtual void render();

	void shadowRender(RECT rc);
	void fillColorEllipse(int R, int G, int B, RECT rc);

	RECT getRect() { return _rc; }

	inline bool getDelete() { return _delete; }
	inline bool getPickup() { return _pickup; }
	inline bool getMoving() { return _moving; }

	//아래는 둘 다 매니저에서 사용할 함수임.
	//던지면 발생하도록함. 방향을 지정해주면(true : 오른쪽, false : 왼쪽) x, y로 움직이도록 함.
	virtual void attackMove(bool direction);
	//아이템을 들고 있는지 판단할 함수. true:들고 있음. false:들고 있지 않음. x, y : 들고다닐 때 위치 조정.
	virtual void setHold(float x, float y);

	
};

