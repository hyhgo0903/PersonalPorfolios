#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	POINT cameraLocation;

	bool minimapBaseOnTotalMap;
	// 미니맵이 전체맵기준으로하면 true, 윈도우창 기준으로 하면 false(minimap함수에서 쓰임)

	int vibrationCount;
	int count;


	float rangeX1;	float rangeX2;
	float rangeY1;	float rangeY2;

	bool cameraLock;

	float minimapX;	float minimapY;
	float minimapHeight;
	float minimapWidth;

	RECT minimapRC;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();

	// 카메라 x를 불러옴 (접근자)
	long getCameraX();
	// 카메라 y를 불러옴 (접근자)
	long getCameraY();

	// (필요시 쓸 것) 카메라 x를 바꿔줌(설정자)
	void setCameraX(long x);

	// (필요시 쓸 것) 카메라 y를 바꿔줌(설정자)
	void setCameraY(long y);
	

	// focusOnRect(RECT, x화면의 n분의1 지점까지 와야 스크롤할지, y화면의 n분의1 지점까지 와야 스크롤할지)
	void focusOnRect(RECT &rc, int x = 2);
	
	// 미니맵 자체를 그리는 함수 minimap(hdc, 생성할 x좌표, y좌표, 폭, 높이, 전체맵기준으로 할지 여부 아니면 윈도우창기준)
	void minimap(HDC hdc, int x, int y, int width, int height, bool standardMap = false);

	// 기존의 미니맵에 보여줄 오브젝트를 추가 minimapObject(hdc, RECT)
	int minimapObject(HDC hdc, RECT & rc);

	// vibrate(규모) 규모 설정 안해도 됨(기본값10)
	void vibrate(int magnitude = 10);

	void cameraLockOn() { cameraLock = true; }
	void cameraLockOff() { cameraLock = false; }
	bool getCameraLock() { return cameraLock; }

	RECT getMinimapRC() { return minimapRC; }
};

