#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	float _x, _y; // 중점
	float _width; // 너비아니
	float _height;// 높이

	float _currentHPWidth;	// 현재체력의 너비아니

	image* _progressBarFront;		//앞에 나올 게이지 이미지
	image* _progressBarBack;	//뒤에 그려질 게이지 이미지

	bool _needToBeResized; // 크기 조정할것인지

public:
	progressBar() {};
	~progressBar() {};

	HRESULT init(int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	void setPoint(float x, float y) { _x = x; _y = y; }
	void setPoint(POINT point) { _x = point.x; _y = point.y; }
	// 하나로 하면 좋지 않을까 싶어서 SetPoint 함수 마련
	// 여기의 _x,_y로 RectMakeCenter(걍 RectMake아닌 것에 주의!)
};

