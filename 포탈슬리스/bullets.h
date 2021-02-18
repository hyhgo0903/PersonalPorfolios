#pragma once
#include "gameNode.h"

#define BULLETDURATION 1000
// _duration : 카운트겸 버그나서 안지워지면 지속시간 끝나서 지워줌

// 기본적인 값만 여기. 개별적인건 상속하고 지정할예정
class bullets :	public gameNode
{
protected:
	int _ID;				// 총알의 종류
	RECT _rc;			// 충돌용 사각형
	float _x, _y;		// x,y좌표
	int _width, _height;// 총알 ID에 따라 부여
	float _xSpd, _ySpd;	// x,y속도
	bool _isFire;		// 
	int _duration;		// 너무 오래있으면 알아서 사라지게하려고
	int _frameX;		// 프레임 인덱스
	int _frameCount;	// 프레임카운트용
	float _damage;
	float _wind;		// UI에서 갖고온걸 저장하도록...

public:
	bullets() {};
	~bullets() {};

	void move();
	bool& getIsFire() { return _isFire; }
	RECT getRect() { return _rc; }

	float getDamage() { return _damage; } // 데미지만큼 체력깎는 함수에 넣어준다
	void setWind(float wind) { _wind = 0.15f * wind; } // 바람값을 계속 바꿔준다

	int& getDuration() { return _duration; } // duration을 갖고오고 설정도 하기 위해 참조자로..
	float getID() { return _ID; } // 유도탄 종류인지 판별하려고 추가

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

