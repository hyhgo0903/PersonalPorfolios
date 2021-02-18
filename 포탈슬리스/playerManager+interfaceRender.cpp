#include "stdafx.h"
#include "playerManager.h"

// 플레이어 관련 값에 따라 인터페이스에 추가해준다
void playerManager::interfaceRender()
{
	if (_tank.currentHP / _tank.maxHP > 0.3f)
	{
		FINDIMG("초록바")->render(getMemDC(), GETCAM + 279, 452, 0, 0, 403.0f*_tank.currentHP / _tank.maxHP, 20);
	}
	else // 빨피는 파워 재활용
	{
		FINDIMG("빨강바")->render(getMemDC(), GETCAM + 279, 452, 0, 0, 403.0f*_tank.currentHP / _tank.maxHP, 20);
	}
	FINDIMG("빨강바")->render(getMemDC(), GETCAM + 279, 475, 0, 0, 403.0f*_tank.currentPower / _tank.maxPower, 20);
	FINDIMG("파랑바")->render(getMemDC(), GETCAM + 279, 497, 0, 0, 403.0f*_tank.currentDelay / _tank.maxDelay, 20);

	// 각도 바늘
	HPEN pen; HPEN oldPen;
	if (_tank.angle < PI / 2)
	{

		HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 150, 0));
		HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
		LineMake(getMemDC(), GETCAM + 92 + 10 * cosf(0.17453f),
			462 - 10 * sinf(0.17453f), GETCAM + 92 + 55 * cosf(0.17453f),
			462 - 55 * sinf(0.17453f));
		LineMake(getMemDC(), GETCAM + 92 + 10 * cosf(1.3963f),
			462 - 10 * sinf(1.3963f), GETCAM + 92 + 55 * cosf(1.3963f),
			462 - 55 * sinf(1.3963f));
		SelectObject(getMemDC(), oldPen);	DeleteObject(pen);
	}
	else
	{
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 150, 0));
		HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
		LineMake(getMemDC(), GETCAM + 92 + 10 * cosf(1.7453f),
			462 - 10 * sinf(1.7453f), GETCAM + 92 + 55 * cosf(1.7453f),
			462 - 55 * sinf(1.7453f));
		LineMake(getMemDC(), GETCAM + 92 + 10 * cosf(2.967f),
			462 - 10 * sinf(2.967f), GETCAM + 92 + 55 * cosf(2.967f),
			462 - 55 * sinf(2.967f));
		SelectObject(getMemDC(), oldPen);	DeleteObject(pen);
	}
	pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(getMemDC(), pen);
	LineMake(getMemDC(), GETCAM + 92 + 10 * cosf(_tank.angle),
		462 - 10 * sinf(_tank.angle), GETCAM + 92 + 55 * cosf(_tank.angle),
		462 - 55 * sinf(_tank.angle));
	SelectObject(getMemDC(), oldPen);	DeleteObject(pen);

	// 일반공격인지 특수공격인지
	if (_specialCount == 2)
	{
		FINDIMG("모드")->render(getMemDC(), GETCAM + 152, 496);
	}
	else	FINDIMG("모드")->render(getMemDC(), GETCAM + 4, 496);

	// 현재 무슨 탱크인지
	switch (_tank.type)
	{
	case CANNON:FINDIMG("현재탱크")->frameRender(getMemDC(), GETCAM + 200, 422, 2, 0);	break;
	case MISSILE:FINDIMG("현재탱크")->frameRender(getMemDC(), GETCAM + 200, 422, 0, 0);	break;
	case MULTI:FINDIMG("현재탱크")->frameRender(getMemDC(), GETCAM + 200, 422, 1, 0);	break;
	case SUPER:FINDIMG("현재탱크")->frameRender(getMemDC(), GETCAM + 200, 422, 3, 0);	break;
	}

	// 각도 안내
	char str[256];
	SetBkMode(getMemDC(), TRANSPARENT);
	int angle = _tank.angle * 180 / PI;
	if (angle == 9) angle = 10;
	else if (angle == 99) angle = 100;
	else if (angle == 169) angle = 170; // 좀 구질구질하지만 표시 멀쩡하게
	sprintf_s(str, "%d", angle);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), GETCAM + 82, 476, str, strlen(str));
	SetTextColor(getMemDC(), RGB(0, 150, 0));
	if (_tank.angle < PI / 2)
	{
		sprintf_s(str, "10");
		TextOut(getMemDC(), GETCAM + 52, 476, str, strlen(str));
		sprintf_s(str, "80");
		TextOut(getMemDC(), GETCAM + 117, 476, str, strlen(str));
	}
	else
	{
		sprintf_s(str, "170");
		TextOut(getMemDC(), GETCAM + 52, 476, str, strlen(str));
		sprintf_s(str, "100");
		TextOut(getMemDC(), GETCAM + 110, 476, str, strlen(str));
	}

}