#pragma once
#include "gameNode.h"
#include "progressBar.h"


class enemy : public gameNode
{
protected:
	int _ID;			// 적의 종류
	int _duration;		// 등장시간<-카운트로써 페이즈구분, 공격인터벌 등에 쓰입니다.
	RECT _rc;			// 충돌용 사각형
	float _x, _y;		// 위치 좌표 x, y 중점임
	int _width, _height; // 렉트 그리기용 너비 높이
	int _alphaValue;	// 이게 줄어들어야 어피어가 꺼진다. 255아니면 충돌안함
	bool _appear;		// 등장했는지?
	bool _arrived;		// 초기 위치로 도착했는지? -- 도착해야 공격을 시작하며 공격받지 않음(반투명)
	int _frameX;
	int _frameCount;
	float _currentHP, _maxHP; // 체력
	progressBar* _hpBar; // 체력바
	int _fireReady;		// 준비가 되면 파이어하고 이걸 하나씩 줄여줌

public:
	enemy() {};
	~enemy() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void commomInit();
	void commonUpdate();
	void commonRender();
	inline void dealDamage(float x) { _currentHP -= x; }
	inline RECT getRect() { return _rc; }
	inline bool getAppear() { return _appear; }
	inline int getAlpha() { return _alphaValue; }
	inline int& getFireReady() { return _fireReady; }
	inline int getID() { return _ID; }
};

