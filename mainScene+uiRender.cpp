#include "stdafx.h"
#include "mainScene.h"



void mainScene::uiRender()
{
	CAMERAMANAGER->minimap(getMemDC(), 0, 580, 240, 120, true);
	Rectangle(getMemDC(), _camMap);
	LineMake(getMemDC(), CAMX+120, CAMY+580, CAMX+0, CAMY+640);
	LineMake(getMemDC(), CAMX+120, CAMY+580, CAMX+240, CAMY+640);
	LineMake(getMemDC(), CAMX+120, CAMY+700, CAMX+0, CAMY+640);
	LineMake(getMemDC(), CAMX+120, CAMY+700, CAMX+240, CAMY+640);
	for (int i = 0; i < _um->getVUnit().size(); ++i)
	{
		if (_um->getVUnit()[i]->getState() == DEAD) continue;
		RECT temp = _um->getVUnit()[i]->getRect();		
		if (_um->getVUnit()[i]->getBelong() == PLAYER)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
			CAMERAMANAGER->minimapObject(getMemDC(), temp); 
			SelectObject(getMemDC(), oldBrush);	DeleteObject(brush);
			SelectObject(getMemDC(), oldPen);	DeleteObject(pen);
		}
		else
		{
			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
			CAMERAMANAGER->minimapObject(getMemDC(), temp);
			SelectObject(getMemDC(), oldBrush);	DeleteObject(brush);
			SelectObject(getMemDC(), oldPen);	DeleteObject(pen);
		}		
	}
}