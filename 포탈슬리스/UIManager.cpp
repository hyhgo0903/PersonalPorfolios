#include "stdafx.h"
#include "UIManager.h"


HRESULT UIManager::init()
{
	_windCount = 0;
	_wind = 0.0f;
	snowSetting();


	return S_OK;
}

void UIManager::release()
{
}

void UIManager::update()
{
	snowMove();
	if (_windCount < 600) _windCount++; // 10초마다 바뀜
	else
	{
		_windCount = 0;
		windChange();
	}
}

void UIManager::render()
{
	//인터페이스를 여기 모두 그리는건 아님. 굳이 참조해서 여기다 다 그릴 필요성은 없기때문
	for (int i = 0; i < SNOWMAX; i++)
	{
		FINDIMG("눈")->frameRender(getMemDC(), _snow[i].x, _snow[i].y, _snow[i].frame, 0);
	}
	FINDIMG("인터페이스")->render(getMemDC(), GETCAM, 399);
	if (KEYMANAGER->isToggleKey('Q')) FINDIMG("온")->render(getMemDC(),
		GETCAM + 720, 491);
	else FINDIMG("오프")->render(getMemDC(),	GETCAM + 720, 494);

	if (_wind > 0)
	{
		FINDIMG("바람")->render(getMemDC(),	GETCAM +92, 514,0,0, 45.*_wind, 9);
	}
	else if (_wind<0)
	{
		FINDIMG("바람")->render(getMemDC(),	GETCAM + 91 - (45. *_wind*-1.), 514,0,0, (45. *_wind*-1.)+1, 9);
	}

}

void UIManager::windChange()
{
	_wind = (rand() % 21 - 10) / 10.0f; // -1.0~+1.0
}

void UIManager::snowSetting()
{
	for (int i = 0; i < SNOWMAX; i++)
	{
		_snow[i].x = rand() % (3 * WINSIZEX) - WINSIZEX;
		_snow[i].y = -(rand() % WINSIZEY);
		_snow[i].frame = rand()%4;
		_snow[i].count = 0;
		_snow[i].xSpd = 0;
	}
}

void UIManager::snowMove()
{
	for (int i = 0; i < SNOWMAX; i++)
	{
		if (_snow[i].count > 5)
		{
			_snow[i].count = 0;
			_snow[i].frame++;
			if (_snow[i].frame >= 6) _snow[i].frame = 0;
		}
		else _snow[i].count++;		

		if (_snow[i].xSpd < _wind)
		{
			_snow[i].xSpd += 0.01f;
			if (_snow[i].xSpd > _wind) _snow[i].xSpd = _wind;
		}
		else if (_snow[i].xSpd > _wind)
		{
			_snow[i].xSpd -= 0.01f;
			if (_snow[i].xSpd < _wind) _snow[i].xSpd = _wind;
		}
		_snow[i].x += 4*_snow[i].xSpd;
		_snow[i].y += 4;
		if (_snow[i].y > WINSIZEY)
		{
			_snow[i].x = GETCAM + rand() % (3 * WINSIZEX) - WINSIZEX;
			_snow[i].y = -10;
		}
	}
}
