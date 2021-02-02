#include "stdafx.h"
#include "stageManager.h"

stageManager::stageManager()
{
}

stageManager::~stageManager()
{
}

HRESULT stageManager::init()
{
	_stage = STAGE1;
	_battlePhase = false;
	_menuInPt = false;
	_onOff = true;
	_pickUnit = P_NONE;
	return S_OK;
}

void stageManager::release()
{
}

void stageManager::update()
{
	_cameraPtMouse.x = _ptMouse.x + CAMX;
	_cameraPtMouse.y = _ptMouse.y + CAMY;
	_pickingPt = picking(_cameraPtMouse.x, _cameraPtMouse.y);
	uiRect();
	ptInIso();
	ptInMenu();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_menuInPt)
		{
			homeBt();
			onOffBt();
			startBt();
			retryBt();
			ptInCreateMenu();
		}
		if (_pickUnit != P_NONE) createUnit();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_pickUnit != P_NONE) createUnit();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_stage = STAGE1;
		setStage(_stage);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_stage = STAGE2;
		setStage(_stage);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_stage = STAGE3;
		setStage(_stage);
	}
	//if (KEYMANAGER->isStayKeyDown(VK_RETURN))
	//{ // 지금은 엔터키로해놨지만 나중에 배치페이즈 끝내는 버튼(게임시작)을 누른 경우로 바꿀거임
	//	_battlePhase = true;
	//	_um->setActive();
	//}
}

void stageManager::render()
{
	//아이소타일
	for (int i = 0; i < TILEX * TILEY; ++i)
	{ 
		if (_isoTile[i].centerX < CAMX - 32 || _isoTile[i].centerX > CAMX + WINSIZEX + 32 ||
			_isoTile[i].centerY < CAMY - 16 || _isoTile[i].centerY > CAMY + WINSIZEY + 16) continue;

		if (_isoTile[i].inRect)	IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 100);
		else IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);


		//타일 위에 유닛을 그려주는 기능
		if (_isoTile[i].name == ZERGLING)	IMAGEMANAGER->findImage("저글링이동블루")->frameRender(getMemDC(), _isoTile[i].drawX + 11, _isoTile[i].drawY - 5, 4, 0);
		else if (_isoTile[i].name == MARINE)	IMAGEMANAGER->findImage("마린기본파랑")->frameRender(getMemDC(), _isoTile[i].drawX + 15, _isoTile[i].drawY - 5, 0, 4);
		else if (_isoTile[i].name == CIVILIAN)	IMAGEMANAGER->findImage("시민블루")->frameRender(getMemDC(), _isoTile[i].drawX + 23, _isoTile[i].drawY - 5, 4, 7);
		else if (_isoTile[i].name == TEMPLAR)	IMAGEMANAGER->findImage("템플러대기블루")->frameRender(getMemDC(), _isoTile[i].drawX + 18, _isoTile[i].drawY - 10, 4, 7);
		else if (_isoTile[i].name == BISHOP)	IMAGEMANAGER->findImage("블루비숍대기")->frameRender(getMemDC(), _isoTile[i].drawX + 25, _isoTile[i].drawY - 2, 4, 0);
		else if (_isoTile[i].name == DIABLO) {}	//아직 이미지가 없음
		else if (_isoTile[i].name == SKELETON) {}	//아직 이미지가 없음
		else if (_isoTile[i].name == GHOST)	IMAGEMANAGER->findImage("ghost_move_blue")->frameRender(getMemDC(), _isoTile[i].drawX + 7, _isoTile[i].drawY - 10, 4, 0);
	}
	//마우스에 선택유닛 보여주는 기능
	if (_pickUnit == P_ZERGLING)	IMAGEMANAGER->findImage("저글링이동블루")->alphaFrameRender(getMemDC(), _cameraPtMouse.x - 18, _cameraPtMouse.y - 18, 4, 0, 100);
}

void stageManager::objectRender()
{
	//오브젝트만! 그려준다
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_isoTile[i].centerX < CAMX - 32 || _isoTile[i].centerX > CAMX + WINSIZEX + 32 ||
			_isoTile[i].centerY < CAMY - 16 || _isoTile[i].centerY > CAMY + WINSIZEY + 16) continue;

		else if (_isoTile[i].name == TREE1)	IMAGEMANAGER->findImage("tree")->render(getMemDC(), _isoTile[i].drawX - 32, _isoTile[i].drawY - 90);
		else if (_isoTile[i].name == TREE2)	IMAGEMANAGER->findImage("tree2")->render(getMemDC(), _isoTile[i].drawX - 10, _isoTile[i].drawY - 90);
		else if (_isoTile[i].name == TREE3)	IMAGEMANAGER->findImage("tree3")->render(getMemDC(), _isoTile[i].drawX - 12, _isoTile[i].drawY - 118);
		else if (_isoTile[i].name == TREE4)	IMAGEMANAGER->findImage("tree4")->render(getMemDC(), _isoTile[i].drawX - 15, _isoTile[i].drawY - 105);
		else if (_isoTile[i].name == TREE5)	IMAGEMANAGER->findImage("tree5")->render(getMemDC(), _isoTile[i].drawX - 3, _isoTile[i].drawY - 58);
	}
}

void stageManager::uiRender()
{
	IMAGEMANAGER->findImage("ui_clear")->render(getMemDC(), CAMX + WINSIZEX - 128, CAMY);
	IMAGEMANAGER->findImage("ui_start")->render(getMemDC(), _startBt.left, _startBt.top);
	IMAGEMANAGER->findImage("ui_home")->render(getMemDC(), _homeBt.left, _homeBt.top);
	IMAGEMANAGER->findImage("ui_retry")->render(getMemDC(), _retryBt.left, _retryBt.top);

	if(_onOff) IMAGEMANAGER->findImage("ui_on")->render(getMemDC(), _onBt.left, _onBt.top);
	else IMAGEMANAGER->findImage("ui_off")->render(getMemDC(), _offBt.left, _offBt.top);

	//유닛 선택 메뉴
	if (_onOff)
	{
		IMAGEMANAGER->findImage("ui_menu")->render(getMemDC(), CAMX + WINSIZEX - 930, CAMY + WINSIZEY - 132);
		IMAGEMANAGER->findImage("icon_zergling")->render(getMemDC(), _zerglingBt.left, _zerglingBt.top);
		IMAGEMANAGER->findImage("icon_marine")->render(getMemDC(), CAMX + 360, CAMY + WINSIZEY - 95);
		IMAGEMANAGER->findImage("icon_civilian")->render(getMemDC(), CAMX + 440, CAMY + WINSIZEY - 95);
		IMAGEMANAGER->findImage("icon_templar")->render(getMemDC(), CAMX + 520, CAMY + WINSIZEY - 95);
		IMAGEMANAGER->findImage("icon_bishop")->render(getMemDC(), CAMX + 600, CAMY + WINSIZEY - 95);
		IMAGEMANAGER->findImage("icon_ghost")->render(getMemDC(), CAMX + 680, CAMY + WINSIZEY - 95);
		//소지금
		char str[256];
		sprintf_s(str, "%d", _isoTile[0].gold);
		TextOut(getMemDC(), CAMX + WINSIZEX - 800, CAMY + WINSIZEY - 125, str, strlen(str));
	}
}

void stageManager::uiRect()
{
	_homeBt = RectMake(CAMX, CAMY + 500, 64, 32);
	_onBt = RectMake(CAMX, CAMY + 468, 64, 32);
	_offBt = RectMake(CAMX, CAMY + 468, 64, 32);
	_startBt = RectMake(CAMX + WINSIZEX - 64, CAMY, 64, 32);
	_retryBt = RectMake(CAMX, CAMY + 532, 64, 32);

	//유닛 생성 렉트
	_zerglingBt = RectMake(CAMX + 280, CAMY + WINSIZEY - 95, 80, 90);
}

void stageManager::homeBt()
{
	if (PtInRect(&_homeBt, _cameraPtMouse))
	{
		SCENEMANAGER->changeScene("타이틀씬");
	}
}

void stageManager::onOffBt()
{	
	if (PtInRect(&_offBt, _cameraPtMouse) && !_onOff)	_onOff = true;
	else if (PtInRect(&_onBt, _cameraPtMouse) && _onOff)	_onOff = false;
}

void stageManager::startBt()
{
	if (PtInRect(&_startBt, _cameraPtMouse))
	{
		_battlePhase = true;
		_um->setActive();
		_onOff = false;
	}
}

void stageManager::retryBt()
{//아직 구현중... 방법 생각중
	if (PtInRect(&_retryBt, _cameraPtMouse))
	{
		_onOff = true;
	}
}

void stageManager::ptInIso()
{
	//마우스포인트가 아이소타일안에 들어왔는지 확인해줌
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (i == _pickingPt.y * TILEX + _pickingPt.x)
		{
			_isoTile[i].inRect = true;
		}
		else _isoTile[i].inRect = false;
	}
}

void stageManager::ptInCreateMenu()
{
	if (PtInRect(&_zerglingBt, _cameraPtMouse))
	{
		_pickUnit = P_ZERGLING;
	}
}

void stageManager::ptInMenu()
{
	if (PtInRect(&_homeBt, _cameraPtMouse))	_menuInPt = true;
	else if (PtInRect(&_offBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_onBt, _cameraPtMouse))	_menuInPt = true;
	else if (PtInRect(&_startBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_retryBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_zerglingBt, _cameraPtMouse)) _menuInPt = true;
	else _menuInPt = false;
}

void stageManager::createUnit()
{
	//언무브 타일에는 안깔립니당
	if (_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE)
	{
		if (_pickUnit == P_ZERGLING)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = ZERGLING;
			InvalidateRect(_hWnd, NULL, false);
		}
	}
}

inline POINT stageManager::picking(long x, long y)
{ // 이게 피킹
	int xx; int yy;
	if (2 * y < (x - 960))	return { -1,0 }; // y=1/2x보다 위에있는지 (맵밖 벗어남)
	if (2 * y < -(x - 960))	return { -1,0 }; // y=-1/2x보다 위에있는지 (맵밖 벗어남)
	//-1이면 예외처리됨(키매니저 L버튼 참고)

	// 왜 y=1/2x가 아니라 2y=x로 썼냐면 나눗셈연산이 느리기때문에 이렇게 쓴거임.
	// 320은 TILEWIDTH * TILEX / 2 (=맵전체 가로크기의 절반값)와 같은데 부하를 줄이기 위해 계산하고 넣은것임

	 // 64는 타일 높이(TILEHEIGHT)에 양변 2곱한값이며 이만큼씩 이격된(밑으로간) 직선이라 보면 됨
	xx = (2 * y + (x - 960)) / 64; // y절편을 이용한 방식으로 바꾸었음
	// xx = ((y + 1/2*(x - 960)) / 32
	// (x좌표) = ((y + 1/2 *(x - 맵x절반)) / 타일높이
	//           ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//           ㄴ>이 부분이 y절편(h)
	if (xx > 29) return { -1,0 }; // 맵밖 벗어난거면 예외처리

	yy = (2 * y - (x - 960)) / 64; // 기울기만 음수고 나머진 상동
	// yy = ((y - 1/2*(x - 960)) / 32
	// (y좌표) = ((y - 1/2 *(x - 맵x절반)) / 타일높이
	//           ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//           ㄴ>이 부분이 y절편(h)
	if (yy > 29) return { -1,0 };

	return { xx , yy };
}

void stageManager::setStage(STAGE stage)
{ // 적 유닛 생성도 요기서하기로 함
	HANDLE file;
	DWORD read;

	switch (stage)
	{
	case STAGE1:
		file = CreateFile("stage1.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);

		_gold = _isoTile[0].gold;
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].name == ZERGLING)	_um->createZergling(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			if (_isoTile[i].name == MARINE)		_um->createMarine(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			if (_isoTile[i].name == CIVILIAN)	_um->createCivilian(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			if (_isoTile[i].name == TEMPLAR)	_um->createTemplar(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			if (_isoTile[i].name == BISHOP)		_um->createBishop(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//if (_isoTile[i].name == DIABLO)
			//if (_isoTile[i].name == SKELETON)
			if (_isoTile[i].name == GHOST)		_um->createGhost(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
		}

		break;
	case STAGE2:
		file = CreateFile("stage2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);

		_gold = _isoTile[0].gold;
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].name == ZERGLING)	_um->createZergling(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			if (_isoTile[i].name == MARINE)		_um->createMarine(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			if (_isoTile[i].name == CIVILIAN)	_um->createCivilian(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			if (_isoTile[i].name == TEMPLAR)	_um->createTemplar(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			if (_isoTile[i].name == BISHOP)		_um->createBishop(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//if (_isoTile[i].name == DIABLO)
			//if (_isoTile[i].name == SKELETON)
			if (_isoTile[i].name == GHOST)		_um->createGhost(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
		}

		break;
	case STAGE3:
		file = CreateFile("stage3.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);

		_gold = _isoTile[0].gold;
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].name == ZERGLING)	_um->createZergling(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			if (_isoTile[i].name == MARINE)		_um->createMarine(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			if (_isoTile[i].name == CIVILIAN)	_um->createCivilian(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			if (_isoTile[i].name == TEMPLAR)	_um->createTemplar(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			if (_isoTile[i].name == BISHOP)		_um->createBishop(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//if (_isoTile[i].name == DIABLO)
			//if (_isoTile[i].name == SKELETON)
			if (_isoTile[i].name == GHOST)		_um->createGhost(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
		}
		break;
	}
}
