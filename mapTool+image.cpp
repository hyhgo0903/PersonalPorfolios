#include "stdafx.h"
#include "mapTool.h"

void mapTool::imageInit()
{
	//이미지를 덮어씌울 렉트 선언 영역
	_saveBt = RectMake(WINSIZEX - 210 + CAMX, 620 + CAMY, 64, 32);
	_saveBt2 = RectMake(WINSIZEX - 140 + CAMX, 620 + CAMY, 64, 32);
	_saveBt3 = RectMake(WINSIZEX - 70 + CAMX, 620 + CAMY, 64, 32);

	_loadBt = RectMake(WINSIZEX - 210 + CAMX, 660 + CAMY, 64, 32);
	_loadBt2 = RectMake(WINSIZEX - 140 + CAMX, 660 + CAMY, 64, 32);
	_loadBt3 = RectMake(WINSIZEX - 70 + CAMX, 660 + CAMY, 64, 32);

	_move = RectMake(WINSIZEX - 210 + CAMX, 580 + CAMY, 64, 32);
	_unMove = RectMake(WINSIZEX - 140 + CAMX, 580 + CAMY, 64, 32);
	_undo = RectMake(WINSIZEX - 70 + CAMX, 580 + CAMY, 64, 32);

	_fill = RectMake(WINSIZEX - 210 + CAMX, 540 + CAMY, 64, 32);
	_open = RectMake(WINSIZEX - 140 + CAMX, 540 + CAMY, 64, 32);
	_close = RectMake(WINSIZEX - 140 + CAMX, 540 + CAMY, 64, 32);

	_small = RectMake(WINSIZEX - 70 + CAMX, 540 + CAMY, 64, 32);
	_medium = RectMake(WINSIZEX - 70 + CAMX, 540 + CAMY, 64, 32);
	_max = RectMake(WINSIZEX - 70 + CAMX, 540 + CAMY, 64, 32);

	_leftBt = RectMake(WINSIZEX - 75 + CAMX, 385 + CAMY, 64, 32);
	_rightBt = RectMake(WINSIZEX - 35 + CAMX, 385 + CAMY, 64, 32);

	_objDel = RectMake(WINSIZEX - 140 + CAMX, 500 + CAMY, 64, 32);
	_menuRc = RectMake(CAMX + WINSIZEX - 522, CAMY, 522, 394);

	_delAll = RectMake(WINSIZEX - 70 + CAMX, 500 + CAMY, 64, 32);

	//예는 menuRc안에 있어서 예외처리 필요없음
	_tree1 = RectMake(CAMX + WINSIZEX - 512, CAMY, 107, 113);
	_tree2 = RectMake(CAMX + WINSIZEX - 402, CAMY, 89, 115);
	_tree3 = RectMake(CAMX + WINSIZEX - 312, CAMY, 84, 139);
	_tree4 = RectMake(CAMX + WINSIZEX - 222, CAMY, 94, 128);
	_tree5 = RectMake(CAMX + WINSIZEX - 122, CAMY, 76, 83);

	_icZergling = RectMake(CAMX + WINSIZEX - 512, CAMY, 80, 90);
}

void mapTool::imageRender()
{
	//아이소타일
	for (int i = 0; i < TILEX * TILEY; ++i)
	{ // 화면 밖의 맵은 그리지 않도록 함. 렉 방지용. 메인씬에도 이거 쓰고 시연떄도 이거 줄여서 보여줘도 될듯
		if (_rs == SMALL)
		{
			if (_isoTile[i].nX > 9) continue;
			if (_isoTile[i].nY > 9) continue;
		}
		else if (_rs == MEDIUM)
		{
			if (_isoTile[i].nX > 19) continue;
			if (_isoTile[i].nY > 19) continue;
		}
		else

			if (_isoTile[i].centerX < CAMX - 32 || _isoTile[i].centerX > CAMX + WINSIZEX + 32 ||
				_isoTile[i].centerY < CAMY - 16 || _isoTile[i].centerY > CAMY + WINSIZEY + 16) continue;

		if (_isoTile[i].inRect)
		{//여기는 영역표시와 함께 이미지가 노출되는곳
			if (_isoTile[i].name == TREE1)
			{
				IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 100);
				IMAGEMANAGER->findImage("tree")->render(getMemDC(), _isoTile[i].drawX - 32, _isoTile[i].drawY - 90);
			}
			else if (_isoTile[i].name == TREE2)
			{
				IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 100);
				IMAGEMANAGER->findImage("tree2")->render(getMemDC(), _isoTile[i].drawX - 10, _isoTile[i].drawY - 90);
			}
			else if (_isoTile[i].name == TREE3)
			{
				IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 100);
				IMAGEMANAGER->findImage("tree3")->render(getMemDC(), _isoTile[i].drawX - 12, _isoTile[i].drawY - 118);
			}
			else if (_isoTile[i].name == TREE4)
			{
				IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 100);
				IMAGEMANAGER->findImage("tree4")->render(getMemDC(), _isoTile[i].drawX - 15, _isoTile[i].drawY - 105);
			}
			else if (_isoTile[i].name == TREE5)
			{
				IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 100);
				IMAGEMANAGER->findImage("tree5")->render(getMemDC(), _isoTile[i].drawX - 3, _isoTile[i].drawY - 58);
			}
			else if (_isoTile[i].name == ZERGLING)
			{
				IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 100);
				IMAGEMANAGER->findImage("저글링이동퍼플")->frameRender(getMemDC(), _isoTile[i].drawX + 10, _isoTile[i].drawY - 5, 5, 0);
			}
			else IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 100);
		}//여기는 마우스와 타일이 닿지 않았을때
		else if (_isoTile[i].name == NONE)
		{
			IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
		}
		else if (_isoTile[i].name == TREE1)
		{
			IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
			IMAGEMANAGER->findImage("tree")->render(getMemDC(), _isoTile[i].drawX - 32, _isoTile[i].drawY - 90);
		}
		else if (_isoTile[i].name == TREE2)
		{
			IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
			IMAGEMANAGER->findImage("tree2")->render(getMemDC(), _isoTile[i].drawX - 10, _isoTile[i].drawY - 90);
		}
		else if (_isoTile[i].name == TREE3)
		{
			IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
			IMAGEMANAGER->findImage("tree3")->render(getMemDC(), _isoTile[i].drawX - 12, _isoTile[i].drawY - 118);
		}
		else if (_isoTile[i].name == TREE4)
		{
			IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
			IMAGEMANAGER->findImage("tree4")->render(getMemDC(), _isoTile[i].drawX - 15, _isoTile[i].drawY - 105);
		}
		else if (_isoTile[i].name == TREE5)
		{
			IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
			IMAGEMANAGER->findImage("tree5")->render(getMemDC(), _isoTile[i].drawX - 3, _isoTile[i].drawY - 58);
		}
		else if (_isoTile[i].name == ZERGLING)
		{
			IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
			IMAGEMANAGER->findImage("저글링이동퍼플")->frameRender(getMemDC(), _isoTile[i].drawX + 10, _isoTile[i].drawY - 5, 5, 0);
		}

		//언무브 타일 표시
		if (_isoTile[i].MUM == UNMOVE) IMAGEMANAGER->findImage("un")->render(getMemDC(), _isoTile[i].drawX + 23, _isoTile[i].drawY + 7);
	}

	if (_brushOn)
	{
		//샘플타일 메뉴
		IMAGEMANAGER->findImage("tileMenu")->render(getMemDC(), CAMX + WINSIZEX - 522, CAMY);
		IMAGEMANAGER->findImage("leftBt")->render(getMemDC(), _leftBt.left, _leftBt.top);
		IMAGEMANAGER->findImage("rightBt")->render(getMemDC(), _rightBt.left, _rightBt.top);
		//샘플타일
		//첫번째 메뉴(타일)
		if (_menuNum == ONE)
		{
			HBRUSH _brush;
			_brush = CreateSolidBrush(RGB(100, 100, 100));
			for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
			{
				if (PtInRect(&_sample[i].rc, _cameraPtMouse)) FillRect(getMemDC(), &_sample[i].rc, _brush);
			}
			IMAGEMANAGER->findImage("mapTiles")->render(getMemDC(), CAMX + WINSIZEX - 512, CAMY);
		}
		else if (_menuNum == TWO)
		{
			HBRUSH _brush;
			_brush = CreateSolidBrush(RGB(100, 100, 100));
			if (PtInRect(&_tree1, _cameraPtMouse)) FillRect(getMemDC(), &_tree1, _brush);
			IMAGEMANAGER->findImage("tree")->render(getMemDC(), _tree1.left, _tree1.top);

			if (PtInRect(&_tree2, _cameraPtMouse)) FillRect(getMemDC(), &_tree2, _brush);
			IMAGEMANAGER->findImage("tree2")->render(getMemDC(), _tree2.left, _tree2.top);

			if (PtInRect(&_tree3, _cameraPtMouse)) FillRect(getMemDC(), &_tree3, _brush);
			IMAGEMANAGER->findImage("tree3")->render(getMemDC(), _tree3.left, _tree3.top);

			if (PtInRect(&_tree4, _cameraPtMouse)) FillRect(getMemDC(), &_tree4, _brush);
			IMAGEMANAGER->findImage("tree4")->render(getMemDC(), _tree4.left, _tree4.top);

			if (PtInRect(&_tree5, _cameraPtMouse)) FillRect(getMemDC(), &_tree5, _brush);
			IMAGEMANAGER->findImage("tree5")->render(getMemDC(), _tree5.left, _tree5.top);
		}
		else if (_menuNum == THREE)
		{
			IMAGEMANAGER->findImage("icon_zergling")->render(getMemDC(), _icZergling.left, _icZergling.top);
		}
	}
	//세이브와 로드
	IMAGEMANAGER->findImage("save1")->render(getMemDC(), _saveBt.left, _saveBt.top);
	IMAGEMANAGER->findImage("save2")->render(getMemDC(), _saveBt2.left, _saveBt2.top);
	IMAGEMANAGER->findImage("save3")->render(getMemDC(), _saveBt3.left, _saveBt3.top);
	IMAGEMANAGER->findImage("load1")->render(getMemDC(), _loadBt.left, _loadBt.top);
	IMAGEMANAGER->findImage("load2")->render(getMemDC(), _loadBt2.left, _loadBt2.top);
	IMAGEMANAGER->findImage("load3")->render(getMemDC(), _loadBt3.left, _loadBt3.top);
	IMAGEMANAGER->findImage("undo")->render(getMemDC(), _undo.left, _undo.top);
	IMAGEMANAGER->findImage("fill")->render(getMemDC(), _fill.left, _fill.top);
	IMAGEMANAGER->findImage("delAll")->render(getMemDC(), _delAll.left, _delAll.top);

	if (!_objDelOn) IMAGEMANAGER->findImage("objDel")->alphaRender(getMemDC(), _objDel.left, _objDel.top, 80);
	else IMAGEMANAGER->findImage("objDel")->render(getMemDC(), _objDel.left, _objDel.top);

	if (_rs == SMALL) IMAGEMANAGER->findImage("small")->render(getMemDC(), _small.left, _small.top);
	else if (_rs == MEDIUM) IMAGEMANAGER->findImage("medium")->render(getMemDC(), _medium.left, _medium.top);
	else IMAGEMANAGER->findImage("max")->render(getMemDC(), _max.left, _max.top);

	if (!_brushOn) IMAGEMANAGER->findImage("open")->render(getMemDC(), _open.left, _open.top);
	else IMAGEMANAGER->findImage("close")->render(getMemDC(), _close.left, _close.top);
	//무브와 언무드
	if (!_moveUnMove)
	{
		IMAGEMANAGER->findImage("move")->render(getMemDC(), _move.left, _move.top);
		IMAGEMANAGER->findImage("unmove")->alphaRender(getMemDC(), _unMove.left, _unMove.top, 80);
	}
	else
	{
		IMAGEMANAGER->findImage("move")->alphaRender(getMemDC(), _move.left, _move.top, 80);
		IMAGEMANAGER->findImage("unmove")->render(getMemDC(), _unMove.left, _unMove.top);
	}
}