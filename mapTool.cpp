#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	createSampleTiles();
	_currentStage = 0;
	createIsoMap(TILEX, TILEY);
	_tempTile.fX = _tempTile.fY = 0;
	_savePopUp = _popUpCount = _modifyingCount = _modifyingNum = 0;
	_pickingPt = { 0,0 };
	_moveUnMove = _seePath = false;
	_brushOn = false;
	_rs = MAX;
	_menuNum = ONE;
	_objName = NONE;
	_objDelOn = false;
	_menuInPt = false;
	_push = false;
	_dragMode = false;
	_playerTile = _enemyTile = -1;


	return S_OK;
}

void mapTool::release()
{
}

//그려질 시작 x, 그려질 시작 y, TILEX 넣기, TILEY 넣기
void mapTool::createIsoMap(int tileX, int tileY)
{

	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			_isoTile[i * tileX + j].fX = 0;
			_isoTile[i * tileX + j].fY = 0;
			_isoTile[i * tileX + j].gold = 0;
			_isoTile[i * tileX + j].nX = j;
			_isoTile[i * tileX + j].nY = i;

			_isoTile[i * tileX + j].inRect = false;
			_isoTile[i * tileX + j].MUM = MOVE;
			_isoTile[i * tileX + j].name = NONE;

			_isoTile[i * tileX + j].centerX = TILESIZEX * (TILEX + (j - i))/2;
			_isoTile[i * tileX + j].centerY = TILESIZEY * (i + j + 1) / 2;

			_isoTile[i * tileX + j].drawX = _isoTile[i * tileX + j].centerX - TILESIZEX / 2;
			_isoTile[i * tileX + j].drawY = _isoTile[i * tileX + j].centerY - TILESIZEY / 2;
		}
	}
	_isoTile[0].gold = 1000;
}


void mapTool::update()
{
	_pickingPt = picking(_cameraPtMouse.x, _cameraPtMouse.y);
	cameraControl();
	imageInit();
	menuInPt();

	if (_popUpCount > 0) --_popUpCount;
	if (_popUpCount == 0 && _savePopUp != 0)
	{
		_seePath = false;
		_savePopUp = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_ptMouse.x > 240 || _ptMouse.y < 580) // 미니맵 밖 누를때만
		{
			if (PtInRect(&_undo, _cameraPtMouse)) tempLoad();
			tempSave();
			if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createTile();
			sampleInTemp();
			save();
			load();
			moveUnMove();
			if (PtInRect(&_fill, _cameraPtMouse) && _tempTile.fX >= 0 && _tempTile.fY >= 0) fill(_tempTile.fX, _tempTile.fY);
			openClose();
			renderSize();
			if (_brushOn) leftRightBt();
			ptInObj();
			if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createObj();
			if (PtInRect(&_objDel, _cameraPtMouse)) objDel();
			if (PtInRect(&_delAll, _cameraPtMouse)) objDelAll();
			if (PtInRect(&_homeBt, _cameraPtMouse)) homeBt();
			if (PtInRect(&_dragBt, _cameraPtMouse)) dragOnOff();

			tempDrag();

			if (_ptMouse.x > 132 && _ptMouse.x < 147 && _ptMouse.y>555 && _ptMouse.y < 574)
			{ // 천의자릿수 클릭
				_modifyingNum = 1;
				_modifyingCount = 300;
			}
			else if (_ptMouse.x > 147 && _ptMouse.x < 162 && _ptMouse.y>555 && _ptMouse.y < 574)
			{ // 백의자릿수 클릭
				_modifyingNum = 2;
				_modifyingCount = 300;
			}
			else if (_ptMouse.x > 162 && _ptMouse.x < 177 && _ptMouse.y>555 && _ptMouse.y < 574)
			{ // 십의자릿수 클릭
				_modifyingNum = 3;
				_modifyingCount = 300;
			}
			else if (_ptMouse.x > 177 && _ptMouse.x < 192 && _ptMouse.y>555 && _ptMouse.y < 574)
			{ // 일의자릿수 클릭
				_modifyingNum = 4;
				_modifyingCount = 300;
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_ptMouse.x > 240 || _ptMouse.y < 580) // 미니맵 밖 누를때만
		{
			if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createTile();
			ptInObj();
			if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createObj();
			_push = true;
			if(_dragMode && _push) dragPaint();
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_push = false;
	}

	ptInIso();

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		if (_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == PLAYERFLAG) _playerTile = -1;
		if (_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == ENEMYFLAG) _enemyTile = -1;
		_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = NONE;
		_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = MOVE;	//오브젝트설치시 자동으로 언무브가 깔려서 지울때도 무브로 바꿔주는거 추가함
		InvalidateRect(_hWnd, NULL, false);
	}


	numberInput();
}

void mapTool::render()
{
	imageRender();
	
	//아래는 편의상 만든 숫자보이게하는거
	char str[256];
	sprintf_s(str, "TempTile X : %d , Y : %d", _tempTile.fX, _tempTile.fY);
	TextOut(getMemDC(), CAMX, CAMY+70, str, strlen(str));

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		sprintf_s(str, "%d, %d", _isoTile[i].nX, _isoTile[i].nY);
		if (KEYMANAGER->isToggleKey(VK_F1)) TextOut(getMemDC(), CAMX+ _isoTile[i].drawX + TILEX, CAMY+_isoTile[i].drawY + (TILEY / 2), str, strlen(str));
	}

	sprintf_s(str, "ptMouse X : %d , Y : %d", _cameraPtMouse.x, _cameraPtMouse.y);
	TextOut(getMemDC(), CAMX+ 150, CAMY+ 70, str, strlen(str));

	//일단 구현은 됬는데 드래그 표시를 어떻게해야하나... 고민중
	if(_push && _dragMode) Rectangle(getMemDC(), _dragRc);
}



inline POINT mapTool::picking(long x, long y)
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

