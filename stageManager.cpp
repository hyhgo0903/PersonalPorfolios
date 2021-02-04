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
	_battlePhase = _isVictory = _isDefeat = false;
	_menuInPt = false;
	_onOff = true;
	_pickUnit = P_NONE;
	_alpha = 0;
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
	stageChange();

	if (_alpha > 0) --_alpha;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_menuInPt)
		{
			homeBt();
			onOffBt();
			startBt();
			retryBt();
			ptInCreateMenu();
			clearBt();
		}
		if (_pickUnit != P_NONE && _onOff && _ptMouse.x > 240 || _ptMouse.y < 580) createUnit();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		//if (_pickUnit != P_NONE && _onOff) createUnit();
	}
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
	}
	//마우스에 선택유닛 보여주는 기능
	if (_pickUnit == P_ZERGLING && _onOff)	IMAGEMANAGER->findImage("저글링이동블루")->alphaFrameRender(getMemDC(), _cameraPtMouse.x - 18, _cameraPtMouse.y - 18, 4, 0, 100);
	if (_pickUnit == P_MARINE && _onOff)	IMAGEMANAGER->findImage("마린기본파랑")->alphaFrameRender(getMemDC(), _cameraPtMouse.x - 16, _cameraPtMouse.y - 18, 0, 4, 100);
	if (_pickUnit == P_CIVILIAN && _onOff)	IMAGEMANAGER->findImage("시민파랑")->alphaFrameRender(getMemDC(), _cameraPtMouse.x - 10, _cameraPtMouse.y - 18, 4, 7, 100);
	if (_pickUnit == P_TEMPLAR && _onOff)	IMAGEMANAGER->findImage("템플러대기블루")->alphaFrameRender(getMemDC(), _cameraPtMouse.x - 18, _cameraPtMouse.y - 18, 4, 7, 100);
	if (_pickUnit == P_BISHOP && _onOff)	IMAGEMANAGER->findImage("블루비숍대기")->alphaFrameRender(getMemDC(), _cameraPtMouse.x - 18, _cameraPtMouse.y - 18, 4, 0, 100);
	if (_pickUnit == P_GHOST && _onOff)	IMAGEMANAGER->findImage("ghost_move_blue")->alphaFrameRender(getMemDC(), _cameraPtMouse.x - 18, _cameraPtMouse.y - 18, 4, 0, 100);
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
		else if (_isoTile[i].name == WALL1)    IMAGEMANAGER->findImage("wall1")->render(getMemDC(), _isoTile[i].drawX + 8, _isoTile[i].drawY - 18);
		else if (_isoTile[i].name == WALL2)    IMAGEMANAGER->findImage("wall2")->render(getMemDC(), _isoTile[i].drawX + 24, _isoTile[i].drawY - 18);
		else if (_isoTile[i].name == WALL3)    IMAGEMANAGER->findImage("wall1")->render(getMemDC(), _isoTile[i].drawX + 32, _isoTile[i].drawY - 28);
		else if (_isoTile[i].name == WALL4)    IMAGEMANAGER->findImage("wall2")->render(getMemDC(), _isoTile[i].drawX + 4, _isoTile[i].drawY - 28);
		else if (_isoTile[i].name == LAVA_OBJ1)	IMAGEMANAGER->findImage("lava_obj1")->render(getMemDC(), _isoTile[i].drawX + 4, _isoTile[i].drawY - 72);
		else if (_isoTile[i].name == LAVA_OBJ3)	IMAGEMANAGER->findImage("lava_obj3")->render(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY - 25);
		else if (_isoTile[i].name == LAVA_OBJ2_L)	IMAGEMANAGER->findImage("lava_obj2_l")->render(getMemDC(), _isoTile[i].drawX + 4, _isoTile[i].drawY - 60);
		else if (_isoTile[i].name == LAVA_OBJ2_R)	IMAGEMANAGER->findImage("lava_obj2_r")->render(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY - 60);
		else if (_isoTile[i].name == PLAYERFLAG)IMAGEMANAGER->findImage("플레이어깃발")->render(getMemDC(), _isoTile[i].centerX - 32, _isoTile[i].centerY - 118);
		else if (_isoTile[i].name == ENEMYFLAG)	IMAGEMANAGER->findImage("에너미깃발")->render(getMemDC(), _isoTile[i].centerX - 32, _isoTile[i].centerY - 118);

	}
}

void stageManager::uiRender()
{
	IMAGEMANAGER->findImage("ui_clear")->render(getMemDC(), _clearBt.left, _clearBt.top);
	IMAGEMANAGER->findImage("ui_start")->render(getMemDC(), _startBt.left, _startBt.top);
	IMAGEMANAGER->findImage("ui_home")->render(getMemDC(), _homeBt.left, _homeBt.top);
	IMAGEMANAGER->findImage("ui_retry")->render(getMemDC(), _retryBt.left, _retryBt.top);
	//스테이지 표시
	if(_stage == STAGE1)	IMAGEMANAGER->findImage("ui_stage1")->render(getMemDC(), CAMX, CAMY);
	else if (_stage == STAGE2)	IMAGEMANAGER->findImage("ui_stage2")->render(getMemDC(), CAMX, CAMY);
	else if (_stage == STAGE3)	IMAGEMANAGER->findImage("ui_BossStage")->render(getMemDC(), CAMX, CAMY);

	if(_onOff) IMAGEMANAGER->findImage("ui_on")->render(getMemDC(), _onBt.left, _onBt.top);
	else IMAGEMANAGER->findImage("ui_off")->render(getMemDC(), _offBt.left, _offBt.top);

	//유닛 선택 메뉴
	if (_onOff)
	{
		IMAGEMANAGER->findImage("ui_menu")->render(getMemDC(), CAMX + WINSIZEX - 930, CAMY + WINSIZEY - 132);
		IMAGEMANAGER->findImage("icon_zergling")->render(getMemDC(), _zerglingBt.left, _zerglingBt.top);
		IMAGEMANAGER->findImage("icon_marine")->render(getMemDC(), _marineBt.left, _marineBt.top);
		IMAGEMANAGER->findImage("icon_civilian")->render(getMemDC(), _civilianBt.left, _civilianBt.top);
		IMAGEMANAGER->findImage("icon_templar")->render(getMemDC(), _templarBt.left, _templarBt.top);
		IMAGEMANAGER->findImage("icon_bishop")->render(getMemDC(), _bishopBt.left, _bishopBt.top);
		IMAGEMANAGER->findImage("icon_ghost")->render(getMemDC(), _ghostBt.left, _ghostBt.top);
		//소지금
		FINDIMG("달러")->render(getMemDC(), CAMX + WINSIZEX - 825, CAMY + WINSIZEY - 128);
		if (_gold > 999) FINDIMG("숫자")->frameRender(getMemDC(), CAMX + WINSIZEX - 800, CAMY + WINSIZEY - 126, _gold / 1000%10, 0);
		if (_gold > 99) FINDIMG("숫자")->frameRender(getMemDC(), CAMX + WINSIZEX - 785, CAMY + WINSIZEY - 126, _gold / 100%10, 0);
		if (_gold > 9) FINDIMG("숫자")->frameRender(getMemDC(), CAMX + WINSIZEX - 770, CAMY + WINSIZEY - 126, _gold / 10%10, 0);
		FINDIMG("숫자")->frameRender(getMemDC(), CAMX + WINSIZEX - 755, CAMY + WINSIZEY - 126, _gold % 10, 0);
	}
	
	if (_alpha > 0)
	{
		for (int i = 0; i < _path.size(); ++i)
		{
			FINDIMG("가이드타일")->alphaRender(getMemDC(), _isoTile[_path[i]].drawX, _isoTile[_path[i]].drawY, _alpha);
		}
	}
	if (!_battlePhase)
	{		
		FINDIMG("배치가능")->alphaRender(getMemDC(), _isoTile[_playerTile].centerX - 400, _isoTile[_playerTile].centerY - 400, 30);
	}
}

void stageManager::uiRect()
{
	_homeBt = RectMake(CAMX, CAMY + 500, 64, 32);
	_onBt = RectMake(CAMX, CAMY + 468, 64, 32);
	_offBt = RectMake(CAMX, CAMY + 468, 64, 32);
	_startBt = RectMake(CAMX + WINSIZEX - 64, CAMY, 64, 32);
	_retryBt = RectMake(CAMX, CAMY + 532, 64, 32);
	_clearBt = RectMake(CAMX + WINSIZEX - 128, CAMY, 64, 32);

	//유닛 생성 렉트
	_zerglingBt = RectMake(CAMX + 280, CAMY + WINSIZEY - 95, 80, 90);
	_marineBt = RectMake(CAMX + 360, CAMY + WINSIZEY - 95, 80, 90);
	_civilianBt = RectMake(CAMX + 440, CAMY + WINSIZEY - 95, 80, 90);
	_templarBt = RectMake(CAMX + 520, CAMY + WINSIZEY - 95, 80, 90);
	_bishopBt = RectMake(CAMX + 600, CAMY + WINSIZEY - 95, 80, 90);
	_ghostBt = RectMake(CAMX + 680, CAMY + WINSIZEY - 95, 80, 90);
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
{
	if (PtInRect(&_retryBt, _cameraPtMouse) && _battlePhase)
	{
		_onOff = true;
		for (int i = 0; i < _um->getVUnit().size(); ++i)	_um->getVUnit()[i]->getErase() = true;
		_gold = _isoTile[0].gold;
		setStage(_stage);
	}
}

void stageManager::clearBt()
{
	if (PtInRect(&_clearBt, _cameraPtMouse) && !_battlePhase)
	{
		setStage(_stage);
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
	if (PtInRect(&_zerglingBt, _cameraPtMouse))		_pickUnit = P_ZERGLING;
	if (PtInRect(&_marineBt, _cameraPtMouse))		_pickUnit = P_MARINE;
	if (PtInRect(&_civilianBt, _cameraPtMouse))		_pickUnit = P_CIVILIAN;
	if (PtInRect(&_templarBt, _cameraPtMouse))		_pickUnit = P_TEMPLAR;
	if (PtInRect(&_bishopBt, _cameraPtMouse))		_pickUnit = P_BISHOP;
	if (PtInRect(&_ghostBt, _cameraPtMouse))		_pickUnit = P_GHOST;
}

void stageManager::ptInMenu()
{
	if (PtInRect(&_homeBt, _cameraPtMouse))	_menuInPt = true;
	else if (PtInRect(&_offBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_onBt, _cameraPtMouse))	_menuInPt = true;
	else if (PtInRect(&_startBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_retryBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_zerglingBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_marineBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_civilianBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_templarBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_bishopBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_ghostBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_clearBt, _cameraPtMouse)) _menuInPt = true;
	else _menuInPt = false;
}

void stageManager::createUnit()
{
	if (_battlePhase) return;
	//언무브 타일에는 안깔립니당
	
	if (_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE 
		&& !_menuInPt && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == NONE)
	{
		if (getDistance(_isoTile[_playerTile].centerX, _isoTile[_playerTile].centerY,
			_cameraPtMouse.x, _cameraPtMouse.y) > 400)
		{
			PLAYSND("배치실패");
			return;
		}
		_tempGold = _gold;
		if (_pickUnit == P_ZERGLING )
		{
			_gold -= 100; //유닛 가격
			if (_gold > 0)
			{
				_um->createZergling(PLAYER, _isoTile[_pickingPt.y * TILEX + _pickingPt.x].centerX - 2, _isoTile[_pickingPt.y * TILEX + _pickingPt.x].centerY - 5);
			}
		}
		else if (_pickUnit == P_MARINE && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == NONE)
		{
			_gold -= 150; //유닛 가격
			if (_gold > 0)
			{
				_um->createMarine(PLAYER, _isoTile[_pickingPt.y * TILEX + _pickingPt.x].centerX - 2, _isoTile[_pickingPt.y * TILEX + _pickingPt.x].centerY - 5);
			}
		}
		else if (_pickUnit == P_CIVILIAN && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == NONE)
		{
			_gold -= 70; //유닛 가격
			if (_gold > 0)
			{
				_um->createCivilian(PLAYER, _isoTile[_pickingPt.y * TILEX + _pickingPt.x].centerX - 2, _isoTile[_pickingPt.y * TILEX + _pickingPt.x].centerY - 5);
			}
		}
		else if (_pickUnit == P_TEMPLAR && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == NONE)
		{
			_gold -= 200; //유닛 가격
			if (_gold > 0)
			{
				_um->createTemplar(PLAYER, _isoTile[_pickingPt.y * TILEX + _pickingPt.x].centerX - 2, _isoTile[_pickingPt.y * TILEX + _pickingPt.x].centerY - 9);
			}
		}
		else if (_pickUnit == P_BISHOP && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == NONE)
		{
			_gold -= 200; //유닛 가격
			if (_gold > 0)
			{
				_um->createBishop(PLAYER, _isoTile[_pickingPt.y * TILEX + _pickingPt.x].centerX + 5, _isoTile[_pickingPt.y * TILEX + _pickingPt.x].centerY - 5);
			}
		}
		else if (_pickUnit == P_GHOST && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == NONE)
		{
			_gold -= 150; //유닛 가격
			if (_gold > 0)
			{
				_um->createGhost(PLAYER, _isoTile[_pickingPt.y * TILEX + _pickingPt.x].centerX - 2, _isoTile[_pickingPt.y * TILEX + _pickingPt.x].centerY - 2);
			}
		}
		if (_gold < 0) // 가격이 0이하로 떨어지면 만든거 취소
		{
			_gold = _tempGold;
			PLAYSND("골드부족");
		}
		else if (_pickUnit != P_NONE)
		{ // 생성 되었으니 경로할당함
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = PLAYEROCCUPIED; // NONE으로 검사했으니 통일해도 될듯
			_um->getVUnit()[_um->getVUnit().size() - 1]->getTileNum() = _pickingPt.y * TILEX + _pickingPt.x;
			_um->getVUnit()[_um->getVUnit().size() - 1]->setVPath(aStarPath(_pickingPt.y*TILEX + _pickingPt.x,
				_enemyTile));
			_alpha = 150;
		}
		InvalidateRect(_hWnd, NULL, false);
	}
}

inline POINT stageManager::picking(long x, long y)
{ // 설명은 맵툴에 있음
	int xx; int yy;
	if (2 * y < (x - 960))	return { -1,0 };
	if (2 * y < -(x - 960))	return { -1,0 };
	xx = (2 * y + (x - 960)) / 64;
	if (xx > 29) return { -1,0 };
	yy = (2 * y - (x - 960)) / 64;
	if (yy > 29) return { -1,0 };

	return { xx , yy };
}

void stageManager::setStage(STAGE stage)
{ // 적 유닛 생성도 요기서하기로 함
	_stage = stage;
	HANDLE file;
	DWORD read;

	switch (_stage)
	{
	case STAGE1:
		file = CreateFile("stage1.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);
		break;
	case STAGE2:
		file = CreateFile("stage2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);
		break;
	case STAGE3:
		file = CreateFile("stage3.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);
		break;
	}
	_um->getVUnit().clear();
	_gold = _tempGold = _isoTile[0].gold;
	_battlePhase = false;
	_onOff = true;

	for (int i = 0; i < TILEX * TILEY; ++i)
	{ // 서순 지켜야하므로 따로 뺌
		if (_isoTile[i].name == PLAYERFLAG)
		{
			_playerTile = i;
			_um->createFlag(PLAYER, _isoTile[i].centerX, _isoTile[i].centerY);
		}
		else if (_isoTile[i].name == ENEMYFLAG)
		{
			_enemyTile = i;
			_um->createFlag(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
		}
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_isoTile[i].name == ZERGLING)
		{
			_um->createZergling(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			_um->getVUnit()[_um->getVUnit().size() - 1]->getTileNum() = i;
			_um->getVUnit()[_um->getVUnit().size() - 1]->setVPath(aStarPath(i, _playerTile));
		}
		else if (_isoTile[i].name == MARINE)
		{
			_um->createMarine(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			_um->getVUnit()[_um->getVUnit().size() - 1]->getTileNum() = i;
			_um->getVUnit()[_um->getVUnit().size() - 1]->setVPath(aStarPath(i, _playerTile));
		}
		else if (_isoTile[i].name == CIVILIAN)
		{
			_um->createCivilian(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			_um->getVUnit()[_um->getVUnit().size() - 1]->getTileNum() = i;
			_um->getVUnit()[_um->getVUnit().size() - 1]->setVPath(aStarPath(i, _playerTile));
		}
		else if (_isoTile[i].name == TEMPLAR)
		{
			_um->createTemplar(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			_um->getVUnit()[_um->getVUnit().size() - 1]->getTileNum() = i;
			_um->getVUnit()[_um->getVUnit().size() - 1]->setVPath(aStarPath(i, _playerTile));
		}
		else if (_isoTile[i].name == BISHOP)
		{
			_um->createBishop(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			_um->getVUnit()[_um->getVUnit().size() - 1]->getTileNum() = i;
			_um->getVUnit()[_um->getVUnit().size() - 1]->setVPath(aStarPath(i, _playerTile));
		}
		else if (_isoTile[i].name == DIABLO)
		{
			_um->createDiablo(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			_um->getVUnit()[_um->getVUnit().size() - 1]->getTileNum() = i;
			_um->getVUnit()[_um->getVUnit().size() - 1]->setVPath(aStarPath(i, _playerTile));
		}
		else if (_isoTile[i].name == SKELETON)
		{
			_um->createSkeleton(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			_um->getVUnit()[_um->getVUnit().size() - 1]->getTileNum() = i;
			_um->getVUnit()[_um->getVUnit().size() - 1]->setVPath(aStarPath(i, _playerTile));
		}
		else if (_isoTile[i].name == GHOST)
		{
			_um->createGhost(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			_um->getVUnit()[_um->getVUnit().size() - 1]->getTileNum() = i;
			_um->getVUnit()[_um->getVUnit().size() - 1]->setVPath(aStarPath(i, _playerTile));
		}
	}
}

void stageManager::stageChange()
{
	if (!_battlePhase) return;
	bool _playerFlagOn = false;
	bool _enemyFlagOn = false;
	for (int i = 0; i < _um->getVUnit().size(); ++i)
	{ 
		if (_um->getVUnit()[i]->getID() == 20 &&
			_um->getVUnit()[i]->getBelong() == PLAYER)
		{// 우리깃발이 있으면
			_playerFlagOn = true;
		}
		if (_um->getVUnit()[i]->getID() == 20 &&
			_um->getVUnit()[i]->getBelong() == ENEMY)
		{// 상대깃발이 있으면
			_enemyFlagOn = true;
		}
	}
	if (!_playerFlagOn) // 우리 깃발 터졌다고..
	{ // 디피트 온으로 바꿀 예정
		switch (_stage)
		{
		case STAGE1: setStage(STAGE1);	break;
		case STAGE2: setStage(STAGE2);	break;
		case STAGE3: setStage(STAGE3);	break;
		}
	}
	if (!_enemyFlagOn) // 상대 깃발 터뜨림
	{ // 빅토리 온으로 바꿀 예정
		switch (_stage)
		{
		case STAGE1: setStage(STAGE2);	break;
		case STAGE2: setStage(STAGE3);	break;
		case STAGE3: SCENEMANAGER->changeScene("엔딩씬"); break;
		}
	}	
}