#pragma once
#include "gameNode.h"
// 바람관리, 기본적인 인터페이스 틀

class playerManager;

struct tagSnow
{
	float x, y; // x,y좌표
	float xSpd; // x스피드 스무스하게 보정되도록
	int frame, count; // 애니메이션 프레임용
};

class UIManager : public gameNode
{
private:
	int _windCount;
	float _wind;
	tagSnow _snow[SNOWMAX];

public:

	UIManager() {};
	~UIManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void windChange();
	void snowSetting();
	void snowMove();
	float getWind() { return _wind; } // 바람값을 배포하기 위해
};

