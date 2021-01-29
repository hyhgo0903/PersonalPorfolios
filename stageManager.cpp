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
	return S_OK;
}

void stageManager::release()
{
}

void stageManager::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1) || _um->getVUnit().size() == 0)
	{ // 벡터 0은 단순히 저글링 블러드를 보기 위해서임.. 나중에 지울거
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
	if (KEYMANAGER->isStayKeyDown(VK_RETURN))
	{ // 지금은 엔터키로해놨지만 나중에 배치페이즈 끝내는 버튼(게임시작)을 누른 경우로 바꿀거임
		_battlePhase = true;
		_um->setActive();
	}
}

void stageManager::render()
{
	//아이소타일
	for (int i = 0; i < TILEX * TILEY; ++i)
	{ 
		if (_isoTile[i].centerX < CAMX - 32 || _isoTile[i].centerX > CAMX + WINSIZEX + 32 ||
			_isoTile[i].centerY < CAMY - 16 || _isoTile[i].centerY > CAMY + WINSIZEY + 16) continue;

		IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);

	}
}

void stageManager::objectRender()
{
	//오브젝트만! 그려준다
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_isoTile[i].centerX < CAMX - 32 || _isoTile[i].centerX > CAMX + WINSIZEX + 32 ||
			_isoTile[i].centerY < CAMY - 16 || _isoTile[i].centerY > CAMY + WINSIZEY + 16) continue;

		else if (_isoTile[i].name == TREE1)
		{
			IMAGEMANAGER->findImage("tree")->render(getMemDC(), _isoTile[i].drawX - 32, _isoTile[i].drawY - 90);
		}
		else if (_isoTile[i].name == TREE2)
		{
			IMAGEMANAGER->findImage("tree2")->render(getMemDC(), _isoTile[i].drawX - 10, _isoTile[i].drawY - 90);
		}
		else if (_isoTile[i].name == TREE3)
		{
			IMAGEMANAGER->findImage("tree3")->render(getMemDC(), _isoTile[i].drawX - 12, _isoTile[i].drawY - 118);
		}
		else if (_isoTile[i].name == TREE4)
		{
			IMAGEMANAGER->findImage("tree4")->render(getMemDC(), _isoTile[i].drawX - 15, _isoTile[i].drawY - 105);
		}
		else if (_isoTile[i].name == TREE5)
		{
			IMAGEMANAGER->findImage("tree5")->render(getMemDC(), _isoTile[i].drawX - 3, _isoTile[i].drawY - 58);
		}
	}
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
			if (_isoTile[i].name == ZERGLING)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createZergling(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
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
			if (_isoTile[i].name == ZERGLING)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createZergling(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
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
			if (_isoTile[i].name == ZERGLING)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createZergling(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
		}
		break;
	}
}
