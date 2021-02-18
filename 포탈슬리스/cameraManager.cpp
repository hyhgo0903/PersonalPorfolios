#include "stdafx.h"
#include "cameraManager.h"

// 개인적으로 만들어두었던 카메라 매니저에서
// y축 스크롤 기능을 뺀 상태로 가져옴


cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	cameraLocation.x = cameraLocation.y = minimapHeight= minimapWidth= rangeX1 = rangeY1 = 0;
	rangeX2 = MAPSIZEX;	rangeY2 = MAPSIZEY;
	cameraLock = false;

	return S_OK;
}

void cameraManager::release()
{
}

// 카메라 x(접근자)
long cameraManager::getCameraX(){return cameraLocation.x;}

// 카메라 y(접근자)
long cameraManager::getCameraY(){return cameraLocation.y;}

// (필요시 쓸 것) 카메라 x를 바꿔줌(설정자)
void cameraManager::setCameraX(long x) { cameraLocation.x = x; }
// (필요시 쓸 것) 카메라 y를 바꿔줌(설정자)
void cameraManager::setCameraY(long y) { cameraLocation.y = y; }

// focusOnRect(RECT, x화면의 n분의1 지점까지 와야 스크롤할지, y화면의 n분의1 지점까지 와야 스크롤할지)
void cameraManager::focusOnRect(RECT & rc, int x)
{
	if (x < 2) x = 2; // 적절하지 않은 값 넣었으면 알아서 2로 바꿔줌
	// rc의 x중점이 카메라+(x-1)*윈사이즈/x보다 큰경우 오른쪽으로 카메라 이동
	if ((rc.left + rc.right) / 2 >= cameraLocation.x + WINSIZEX - WINSIZEX / x && !cameraLock)
	{
		if ((rc.left + rc.right) / 2 - (cameraLocation.x + WINSIZEX - WINSIZEX / x) <10) cameraLocation.x = (rc.left + rc.right) / 2 - WINSIZEX + WINSIZEX / x;
		// 가까이 있는거면 딱 붙여줌
		else cameraLocation.x += 10; // 멀리 떨어진거면 스무스하게 이동
	}
	if (cameraLocation.x < rangeX1) cameraLocation.x = rangeX1;
	if (cameraLocation.y < rangeY1) cameraLocation.y = rangeY1;
	if (cameraLocation.x > rangeX2 - WINSIZEX) cameraLocation.x = rangeX2 - WINSIZEX;
	if (cameraLocation.y > rangeY2 - WINSIZEY) cameraLocation.y = rangeY2 - WINSIZEY; // 예외처리
}


// 미니맵 틀을 그리는 함수 minimap(hdc, 생성할 x좌표, y좌표, 폭, 높이)
void cameraManager::minimap(HDC hdc, int x, int y, int width, int height, bool standardMap)
{
	minimapX = cameraLocation.x + x;
	minimapY = cameraLocation.y + y;
	minimapWidth = width;
	minimapHeight = height;
	Rectangle(hdc, minimapX, minimapY, minimapX + minimapWidth, minimapY + minimapHeight-20);
	minimapRC = { (int)minimapX, (int)minimapY, (int)minimapX + (int)minimapWidth, (int)minimapY + (int)minimapHeight - 20 };
	minimapBaseOnTotalMap = standardMap;
}

// 기존의 미니맵에 오브젝트를 추가 minimapObject(hdc, RECT)
int cameraManager::minimapObject(HDC hdc, RECT & rc)
{
	if (minimapHeight == 0 || minimapWidth == 0) return 0; // 틀이 안 만들어졌다면 연산안함
	
	if (rc.left < cameraLocation.x || rc.right > cameraLocation.x + WINSIZEX ||
		rc.top < cameraLocation.y || rc.bottom > cameraLocation.y + WINSIZEY) return 0; // 맵밖 벗어나면 안 그려줌
	//보이는 맵 밖이므로 연산 안함
	Rectangle(hdc, minimapX + (rc.left - cameraLocation.x)*minimapWidth / WINSIZEX,
		minimapY + (rc.top - cameraLocation.y)*minimapHeight / WINSIZEY,
		minimapX + (rc.right - cameraLocation.x)*minimapWidth / WINSIZEX,
		minimapY + (rc.bottom - cameraLocation.y)*minimapHeight / WINSIZEY);
}

// vibrate(규모)
void cameraManager::vibrate(int magnitude)
{
	cameraLocation.x += rand() % (2 * magnitude + 1) - magnitude; // -mag~+mag까지 랜덤하게 이동
	if (cameraLocation.x < 0) cameraLocation.x = 0;
	if (cameraLocation.x > rangeX2-WINSIZEX) cameraLocation.x = rangeX2 - WINSIZEX;
}
