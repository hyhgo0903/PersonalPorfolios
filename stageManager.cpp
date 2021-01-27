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
	setStage(_stage);
	return S_OK;
}

void stageManager::release()
{
}

void stageManager::update()
{
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
}

void stageManager::render()
{
	//아이소타일
	for (int i = 0; i < TILEX * TILEY; ++i)
	{ 
		if (_isoTile[i].centerX < CAMX - 32 || _isoTile[i].centerX > CAMX + WINSIZEX + 32 ||
			_isoTile[i].centerY < CAMY - 16 || _isoTile[i].centerY > CAMY + WINSIZEY + 16) continue;

		if (_isoTile[i].name == NONE)
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
		}
	}
}

void stageManager::setStage(STAGE stage)
{
	HANDLE file;
	DWORD read;

	switch (stage)
	{
	case STAGE1:
		file = CreateFile("stage1.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		memset(_sMove, 0, sizeof(STAGEMOVE) * TILEX * TILEY);
		memset(_tileObj, 0, sizeof(tileObj) * TILEX * TILEY);
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].MUM == UNMOVE) _sMove[i] = S_UNMOVE;
			if (_isoTile[i].name == TREE1) _tileObj[i] = S_TREE1;
			if (_isoTile[i].name == TREE2) _tileObj[i] = S_TREE2;
			if (_isoTile[i].name == TREE3) _tileObj[i] = S_TREE3;
			if (_isoTile[i].name == TREE4) _tileObj[i] = S_TREE4;
			if (_isoTile[i].name == TREE5) _tileObj[i] = S_TREE5;
			if (_isoTile[i].name == ZERGLING) _tileObj[i] = S_ZERGLING;
		}
		CloseHandle(file);
		break;
	case STAGE2:
		file = CreateFile("stage2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		memset(_sMove, 0, sizeof(STAGEMOVE) * TILEX * TILEY);
		memset(_tileObj, 0, sizeof(tileObj) * TILEX * TILEY);
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].MUM == UNMOVE) _sMove[i] = S_UNMOVE;
			if (_isoTile[i].name == TREE1) _tileObj[i] = S_TREE1;
			if (_isoTile[i].name == TREE2) _tileObj[i] = S_TREE2;
			if (_isoTile[i].name == TREE3) _tileObj[i] = S_TREE3;
			if (_isoTile[i].name == TREE4) _tileObj[i] = S_TREE4;
			if (_isoTile[i].name == TREE5) _tileObj[i] = S_TREE5;
			if (_isoTile[i].name == ZERGLING) _tileObj[i] = S_ZERGLING;
		}
		CloseHandle(file);
		break;
	case STAGE3:
		file = CreateFile("stage3.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		memset(_sMove, 0, sizeof(STAGEMOVE) * TILEX * TILEY);
		memset(_tileObj, 0, sizeof(tileObj) * TILEX * TILEY);
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].MUM == UNMOVE) _sMove[i] = S_UNMOVE;
			if (_isoTile[i].name == TREE1) _tileObj[i] = S_TREE1;
			if (_isoTile[i].name == TREE2) _tileObj[i] = S_TREE2;
			if (_isoTile[i].name == TREE3) _tileObj[i] = S_TREE3;
			if (_isoTile[i].name == TREE4) _tileObj[i] = S_TREE4;
			if (_isoTile[i].name == TREE5) _tileObj[i] = S_TREE5;
			if (_isoTile[i].name == ZERGLING) _tileObj[i] = S_ZERGLING;
		}
		CloseHandle(file);
		break;
	}
}
