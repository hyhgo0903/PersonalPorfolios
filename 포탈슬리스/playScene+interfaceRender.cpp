#include "stdafx.h"
#include "playScene.h"

void playScene::interfaceRender()
{
	CAMERAMANAGER->minimap(getMemDC(), 645, 5, 150, 100, false);

	RECT temp;

	// 미니맵 추가 아군관련
	HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	HPEN pen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
	for (int i = 0; i < _bm->getVPBullet().size(); ++i)
	{
		temp = _bm->getVPBullet()[i]->getRect();
		CAMERAMANAGER->minimapObject(getMemDC(), temp);
	}
	temp = _pm->getRect();
	CAMERAMANAGER->minimapObject(getMemDC(), temp);
	SelectObject(getMemDC(), oldBrush);	DeleteObject(brush);
	SelectObject(getMemDC(), oldPen);	DeleteObject(pen);

	// 미니맵 추가 적군관련
	brush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	pen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
	oldPen = (HPEN)SelectObject(getMemDC(), pen);
	for (int i = 0; i < _em->getVFEnemy().size(); ++i)
	{
		temp = _em->getVFEnemy()[i]->getRect();
		if (_em->getVFEnemy()[i]->getID() == 2)
		{ // 보스는 충돌크기가 작으니 이미지에 맞게 그려주는것
			temp = RectMake(temp.left - 98, temp.top - 35, 220, 170);
		}
		CAMERAMANAGER->minimapObject(getMemDC(), temp);
	}
	for (int i = 0; i < _em->getVGEnemy().size(); ++i)
	{
		temp = _em->getVGEnemy()[i]->getRect();
		CAMERAMANAGER->minimapObject(getMemDC(), temp);
	}
	for (int i = 0; i < _bm->getVEBullet().size(); ++i)
	{
		temp = _bm->getVEBullet()[i]->getRect();
		CAMERAMANAGER->minimapObject(getMemDC(), temp);
	}
	SelectObject(getMemDC(), oldBrush);	DeleteObject(brush);
	SelectObject(getMemDC(), oldPen);	DeleteObject(pen);

	//미니맵 추가 아이템관련
	brush = CreateSolidBrush(RGB(255, 255, 0));
	oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	pen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
	oldPen = (HPEN)SelectObject(getMemDC(), pen);
	for (int i = 0; i < _im->getVDroppedItem().size(); ++i)
	{
		temp = _im->getVDroppedItem()[i]->getRect();
		CAMERAMANAGER->minimapObject(getMemDC(), temp);
	}
	temp = _im->getRect();
	CAMERAMANAGER->minimapObject(getMemDC(), temp);
	SelectObject(getMemDC(), oldBrush);	DeleteObject(brush);
	SelectObject(getMemDC(), oldPen);	DeleteObject(pen);


	LineMake(getMemDC(), GETCAM + 645, 5, GETCAM + 795, 5);
	LineMake(getMemDC(), GETCAM + 645, 5, GETCAM + 645, 85); // 미니맵을 파고들길래 마지막으로 미니맵좌상단만 덧그려줌
	// 가끔 캐릭터가 인터페이스 창 위에 있어서 덧그리기
	FINDIMG("인터페이스덧그리기")->render(getMemDC(), GETCAM, 399);

	_scoreSum = _bm->getScore() + 20 * _im->getScore(); // 아이템점수와 총알점수를 더합니다
	if (_scoreSum > 999) _scoreSum = 999;
	FINDIMG("숫자")->frameRender(getMemDC(), GETCAM +714, WINSIZEY - 100, _scoreSum / 100 % 10, 0);
	FINDIMG("숫자")->frameRender(getMemDC(), GETCAM +738, WINSIZEY - 100, _scoreSum / 10 % 10, 0);
	FINDIMG("숫자")->frameRender(getMemDC(), GETCAM +762, WINSIZEY - 100, _scoreSum % 10, 0);

	if (CAMERAMANAGER->getCameraLock() == false && _idleTime > 600)
	{
		FINDIMG("고")->frameRender(getMemDC(), GETCAM + 740, 200, _goFrameX, 0);
	}
}

