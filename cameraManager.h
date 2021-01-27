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

	float minimapX;	float minimapY;
	float minimapHeight;
	float minimapWidth;

	bool cameraLocked; // 카메라 고정됐는지

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();

	// 카메라 x와 카메라 y(접근자).. CAMX, CAMY로 디파인해서 씀
	long getCameraX() { return cameraLocation.x; }
	long getCameraY() { return cameraLocation.y; }

	// 카메라 x와 y를 바꿔줌(설정자)
	void setCameraX(long x);
	void setCameraY(long y);

	// 카메라 적용 범위를 지정 (배경이미지에 맞춰서) setCameraRange(x좌표, y좌표)
	// ..로 만들었었는데 대신 stdafx.h 디파인문으로 입력받게 해놔서
	// setCameraRange 함수 세개 다 무시해도 됩니다. 
	void setCameraRange(int x, int y); // 0,0에서 x,y

	// 백버퍼크기도 이에 맞춰주고싶은데 못하는중... (수요일에 배운다하심)

	// 카메라 적용 범위를 지정 (배경이미지에 맞춰서) setCameraRange(x시작좌표, y시작좌표, x끝좌표, y끝좌표)
	void setCameraRange(int x1, int y1, int x2, int y2); // x1,y1에서 x2,y2

	// 카메라 적용 범위를 지정 (배경이미지에 맞춰서) setCameraRange(이미지포인터)
	void setCameraRange(image * image);

	// focusOnRect(RECT, x화면의 n분의1 지점까지 와야 스크롤할지, y화면의 n분의1 지점까지 와야 스크롤할지)
	void focusOnRect(RECT &rc, int x = 2, int y = 2);

	// 미니맵 자체를 그리는 함수 minimap(hdc, 생성할 x좌표, y좌표, 폭, 높이, 전체맵기준으로 할지 여부 아니면 윈도우창기준)
	void minimap(HDC hdc, int x, int y, int width, int height, bool standardMap = false);

	// 기존의 미니맵에 보여줄 오브젝트를 추가 minimapObject(hdc, RECT)
	int minimapObject(HDC hdc, RECT & rc);

	// vibrate(규모) 규모 설정 안해도 됨(기본값10)
	void vibrate(int magnitude = 10);

	// 카메라 락 관련 함수
	bool getCameraLock() { return cameraLocked; }
	void cameraLock() { cameraLocked = true; } // 카메라 잠금 동작입니다.
	void cameraLockOff() { cameraLocked = false; }
};

