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

	createIsoMap(TILEX, TILEY);
	_tempTile.fX = 0;
	_tempTile.fY = 0;
	_pickingPt = { 0,0 };
	_moveUnMove = false;
	_brushOn = false;
	_rs = MAX;
	_menuNum = ONE;
	_objName = NONE;
	_objDelOn = false;
	_menuInPt = false;
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
}


void mapTool::update()
{
	_pickingPt = picking(_cameraPtMouse.x, _cameraPtMouse.y);
	cameraControl();
	imageInit();
	menuInPt();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
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
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createTile();
		ptInObj();
		if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createObj();
	}
	ptInIso();
	if (KEYMANAGER->isOnceKeyDown(VK_F4)) SCENEMANAGER->changeScene("메인씬");
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

	sprintf_s(str, "ptMouse X : %d , Y : %d", CAMX + _cameraPtMouse.x, CAMY + _cameraPtMouse.y);
	TextOut(getMemDC(), CAMX+ 150, CAMY+ 70, str, strlen(str));
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
	if (xx > 29) return { -1,0 }; // 맵밖 벗어난거면 예외처리

	yy = (2 * y - (x - 960)) / 64; // 기울기만 음수고 나머진 상동
	if (yy > 29) return { -1,0 };

	return { xx , yy };
}