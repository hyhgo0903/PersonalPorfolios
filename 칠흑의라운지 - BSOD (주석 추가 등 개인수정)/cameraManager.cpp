#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	cameraLocation.x = cameraLocation.y = minimapHeight = minimapWidth = rangeX1 = rangeY1 = 0;
	rangeX2 = MAPSIZEX;	rangeY2 = MAPSIZEY;
	cameraLocked = false;

	return S_OK;
}

void cameraManager::release()
{
}


// (필요시 쓸 것) 카메라 x를 바꿔줌(설정자)
void cameraManager::setCameraX(long x)
{
	if (cameraLocked) return;
	cameraLocation.x = x; 
}
// (필요시 쓸 것) 카메라 y를 바꿔줌(설정자)
void cameraManager::setCameraY(long y)
{
	if (cameraLocked) return;
	cameraLocation.y = y; 
}

// 카메라 적용 범위를 지정 (배경이미지에 맞춰서) setCameraRange(x좌표, y좌표)
// ..로 만들었었는데 대신 stdafx.h 디파인문으로 입력받게 해놔서
// setCameraRange 함수 세개 다 무시해도 됩니다. 
void cameraManager::setCameraRange(int x, int y)
{
	rangeX1 = 0; rangeX2 = x; rangeY1 = 0;  rangeY2 = y;
	//gameNode::setBackBuffer(x, y);
}

// 카메라 적용 범위를 지정 (배경이미지에 맞춰서) setCameraRange(x시작좌표, y시작좌표, x끝좌표, y끝좌표)
void cameraManager::setCameraRange(int x1, int y1, int x2, int y2)
{
	rangeX1 = x1; rangeX2 = x2; rangeY1 = y1;  rangeY2 = y2;
}

// 카메라 적용 범위를 지정 (배경이미지에 맞춰서) setCameraRange(이미지포인터)
void cameraManager::setCameraRange(image * image)
{
	rangeX1 = 0; rangeX2 = image->getWidth(); rangeY1 = 0;  rangeY2 = image->getHeight();
}

// focusOnRect(RECT, x화면의 n분의1 지점까지 와야 스크롤할지, y화면의 n분의1 지점까지 와야 스크롤할지)
void cameraManager::focusOnRect(RECT & rc, int x, int y)
{
	if (cameraLocked) return; // 잠겼으면 연산하지 않습니다.
	if (x < 2) x = 2; // 적절하지 않은 값 넣었으면 알아서 2로 바꿔줌
	if (y < 2) y = 2; // 적절하지 않은 값 넣었으면 알아서 2로 바꿔줌
	// rc의 x중점이 카메라+윈사이즈/x보다 작은경우 왼쪽으로 카메라 이동
	if ((rc.left + rc.right) / 2 <= cameraLocation.x + WINSIZEX / x)
	{ // 수치 10은 적당히 세팅해도 됩니다.
		cameraLocation.x -= 10;
		if (cameraLocation.x < (rc.left + rc.right) / 2 - WINSIZEX / x)
		{
			cameraLocation.x = (rc.left + rc.right) / 2 - WINSIZEX / x;
		}
	}
	// rc의 x중점이 카메라+(x-1)*윈사이즈/x보다 큰경우 오른쪽으로 카메라 이동
	if ((rc.left + rc.right) / 2 >= cameraLocation.x + WINSIZEX - WINSIZEX / x)
	{
		cameraLocation.x += 10;
		if (cameraLocation.x > (rc.left + rc.right) / 2 - WINSIZEX + WINSIZEX / x)
		{
			cameraLocation.x = (rc.left + rc.right) / 2 - WINSIZEX + WINSIZEX / x;
		}
	}
	// rc의 y중점이 카메라+윈사이즈/y보다 작은경우 위쪽으로 카메라 이동
	if ((rc.top + rc.bottom) / 2 <= cameraLocation.y + WINSIZEY / y)
	{
		cameraLocation.y -= 10;
		if (cameraLocation.y < (rc.top + rc.bottom) / 2 - WINSIZEY / y)
		{
			cameraLocation.y = (rc.top + rc.bottom) / 2 - WINSIZEY / y;
		}
	}
	// rc의 y중점이 카메라+(y-1)*윈사이즈/y보다 큰경우 아랫쪽으로 카메라 이동
	if ((rc.top + rc.bottom) / 2 >= cameraLocation.y + WINSIZEY - WINSIZEY / y)
	{
		cameraLocation.y += 10;
		if (cameraLocation.y > (rc.top + rc.bottom) / 2 - WINSIZEY + WINSIZEY / y)
		{
			cameraLocation.y = (rc.top + rc.bottom) / 2 - WINSIZEY + WINSIZEY / y;
		}
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
	Rectangle(hdc, minimapX, minimapY, minimapX + minimapWidth, minimapY + minimapHeight);
	minimapBaseOnTotalMap = standardMap;
}

// 기존의 미니맵에 오브젝트를 추가 minimapObject(hdc, RECT)
int cameraManager::minimapObject(HDC hdc, RECT & rc)
{
	if (minimapHeight == 0 || minimapWidth == 0) return 0; // 틀이 안 만들어졌다면 연산안함
	if (minimapBaseOnTotalMap)// 미니맵이 전체 맵 기준이면
	{
		if (rc.left < -5 || rc.right > MAPSIZEX + 5 ||
			rc.top < -5 || rc.bottom > MAPSIZEY + 5) return 0; // 맵밖 벗어나면 안 그려줌
		//보이는 맵 밖이므로 연산 안함
		Rectangle(hdc, minimapX + rc.left*minimapWidth / MAPSIZEX,
			minimapY + rc.top*minimapHeight / MAPSIZEY,
			minimapX + rc.right*minimapWidth / MAPSIZEX,
			minimapY + rc.bottom*minimapHeight / MAPSIZEY);
	}
	else  // 미니맵이 윈도우창 기준이면
	{
		if (rc.left < cameraLocation.x - 5 || rc.right > cameraLocation.x + WINSIZEX + 5 ||
			rc.top < cameraLocation.y - 5 || rc.bottom > cameraLocation.y + WINSIZEY + 5) return 0; // 맵밖 벗어나면 안 그려줌
		//보이는 맵 밖이므로 연산 안함
		Rectangle(hdc, minimapX + (rc.left - cameraLocation.x)*minimapWidth / WINSIZEX,
			minimapY + (rc.top - cameraLocation.y)*minimapHeight / WINSIZEY,
			minimapX + (rc.right - cameraLocation.x)*minimapWidth / WINSIZEX,
			minimapY + (rc.bottom - cameraLocation.y)*minimapHeight / WINSIZEY);
	}
}

// vibrate(규모)
void cameraManager::vibrate(int magnitude)
{
	cameraLocation.x += rand() % (2 * magnitude + 1) - magnitude; // -mag~+mag까지
	cameraLocation.y += rand() % (2 * magnitude + 1) - magnitude; // 랜덤하게 이동
	if (cameraLocation.x < 0) cameraLocation.x = 0;
	if (cameraLocation.x > rangeX2 - WINSIZEX) cameraLocation.x = rangeX2 - WINSIZEX;
	if (cameraLocation.y < 0) cameraLocation.y = 0;
	if (cameraLocation.y > rangeY2 - WINSIZEY) cameraLocation.y = rangeY2 - WINSIZEY; // 예외처리
}
