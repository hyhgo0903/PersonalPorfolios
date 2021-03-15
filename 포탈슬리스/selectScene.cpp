#include "stdafx.h"
#include "selectScene.h"

selectScene::selectScene()
{
}

selectScene::~selectScene()
{
}


HRESULT selectScene::init()
{
	CAMERAMANAGER->setCameraX(0);
	_manualPop = _selectPhase = _selected = false;
	_data = 0;
	_cursor[0] = 0; _cursor[1] = -1;
	return S_OK;
}

void selectScene::release()
{
}

void selectScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && !_manualPop && !_selectPhase && _cursor[0] < 2)
	{	++_cursor[0];	} // 메인페이즈에서 아래버튼을 누르면		
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && !_manualPop && !_selectPhase && _cursor[0] > 0)
	{	--_cursor[0];	} // 메인페이즈에서 위버튼 누르면
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _selectPhase)
	{ // 셀렉트 페이즈에서 좌우
		if (!_selected && _cursor[0] < 2) ++_cursor[0];
		if (_selected && _cursor[1] < 2) ++_cursor[1];
	} // 셀렉트 페이즈에서 오른쪽 버튼을 누르면		
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && _selectPhase)
	{
		if (!_selected && _cursor[0] > 0) --_cursor[0];
		if (_selected && _cursor[1] > 0) --_cursor[1];
	} // 셀렉트 페이즈에서에서 왼쪽버튼 누르면
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (!_manualPop && !_selectPhase && _cursor[0] == 0) _selectPhase = true;
		//선택페이즈로
		else if (!_manualPop && !_selectPhase && _cursor[0] == 1) _manualPop = true;
		// 매뉴얼키기
		else if (_manualPop) _manualPop = false; // 매뉴얼 끄기
		else if (!_manualPop && !_selectPhase && _cursor[0] == 2) PostQuitMessage(0); // 종료

		// 난이도 선택은 10의 자리로 저장(쉬움0,보통10,하드20)
		else if (_selectPhase && _cursor[0]==0 && !_selected)
		{_selected = true;	_data = 0; _cursor[1] = 0;}
		else if (_selectPhase && _cursor[0] == 1 && !_selected)
		{_selected = true;	_data = 10; _cursor[1] = 0;}
		else if (_selectPhase && _cursor[0] == 2 && !_selected)
		{_selected = true;	_data = 20; _cursor[1] = 0;}
		else if (_selectPhase && _cursor[1] == 0 && _selected)
		{ // 초기탱크는 1의 자리로 저장(+0,+1,+2) 씬체인지
			SCENEMANAGER->changeScene("플레이씬", _data);
		} // 예를들어 하드난이도, 캐논탱을 고르면 _data는 20+0으로 저장
		else if (_selectPhase && _cursor[1] == 1 && _selected)
		{
			SCENEMANAGER->changeScene("플레이씬", _data+1);
		}
		else if (_selectPhase && _cursor[1] == 2 && _selected)
		{
			SCENEMANAGER->changeScene("플레이씬", _data+2);
		}
	}


}

void selectScene::render()
{
	if (!_selectPhase)
	{
		FINDIMG("메인씬")->render(getMemDC());
		switch (_cursor[0])
		{
		case 0: FINDIMG("초기선택박스")->render(getMemDC(), 575, 186);	break;
		case 1: FINDIMG("초기선택박스")->render(getMemDC(), 575, 275);	break;
		case 2: FINDIMG("초기선택박스")->render(getMemDC(), 575, 364);	break;
		}
	}
	if (_manualPop)	FINDIMG("매뉴얼")->render(getMemDC());
	if (_selectPhase)
	{
		FINDIMG("셀렉트씬")->render(getMemDC());
		switch (_cursor[0])
		{
		case 0:FINDIMG("난이도선택박스")->render(getMemDC(), 8, 80);	break;
		case 1:FINDIMG("난이도선택박스")->render(getMemDC(), 275, 80);	break;
		case 2:FINDIMG("난이도선택박스")->render(getMemDC(), 535, 80);	break;
		}
		switch (_cursor[1])
		{
		case -1:break;
		case 0:FINDIMG("탱크선택박스")->render(getMemDC(), 7, 336);	break;
		case 1:FINDIMG("탱크선택박스")->render(getMemDC(), 280, 336);	break;
		case 2:FINDIMG("탱크선택박스")->render(getMemDC(), 547, 336);	break;
		}
	}
}