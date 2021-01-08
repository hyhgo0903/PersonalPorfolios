#include "stdafx.h"
#include "itemManager.h"

itemManager::itemManager()
{
}

itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	createBaseball(300, CAMY + 500);
	return S_OK;
}

void itemManager::release()
{
	_vItem.clear();
}

void itemManager::update()
{
	
	{
		if (KEYMANAGER->isOnceKeyDown('1'))
		{//사용법 느낌쓰
			_vItem.clear();
			createBaseball(300, CAMY + 500);
			//init(float x, float y, float bottom);
		}

		if (KEYMANAGER->isOnceKeyDown('2'))
		{
			_vItem.clear();
			createBomb(500, CAMY + 500);
		}
	}
	/*
	{
		if (KEYMANAGER->isOnceKeyDown('Q'))
		{
			for (int i = 0; i < _vItem.size(); i++)
			{
				if (!_vItem[i]->getPickup() && !_vItem[i]->getMoving())
				{
					int cx = (_vItem[i]->getRect().right + _vItem[i]->getRect().left) / 2;
					int cy = (_vItem[i]->getRect().bottom + _vItem[i]->getRect().top) / 2;
					_vItem[i]->setHold(cx, cy-100);//플레이어 x, y 기준으로 값 넣어주면 계속 들고 다니는 느낌쓰 낼 수 있을 듯.
					return;//이걸로 바닥에 있는 거 던질 수 있도록 함.
				}

				if (_vItem[i]->getPickup() && !_vItem[i]->getMoving())
				{
					itemAttack = true;
				}
			}
		}
		
	if (itemAttack)
	{
		for (int i = 0; i < _vItem.size(); i++)
		{
			_vItem[i]->attackMove(0);
			if (_vItem[i]->getDelete())
			{
				EFFECTMANAGER->play("폭발", ((_vItem[i]->getRect().right + _vItem[i]->getRect().left) / 2), _vItem[i]->getRect().top);
				_vItem.erase(_vItem.begin() + i);
			}
		}
	}
	
	}
	*/
	
	if (itemAttack)
	{
		for (int i = 0; i < _vItem.size(); i++)
		{
			_vItem[i]->attackMove(_direction);
			if (_vItem[i]->getDelete())
			{
				EFFECTMANAGER->play("폭발", ((_vItem[i]->getRect().right + _vItem[i]->getRect().left) / 2), _vItem[i]->getRect().top);
				_vItem.erase(_vItem.begin() + i);
			}
		}
	}
	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->update();
	}

	for (int i = 0; i < _vItem.size(); i++)
	{//아이템이 화면 밖으로 나가면 없어지도록.
		if (_vItem[i]->getRect().right < CAMERAMANAGER->getCameraX() ||
			_vItem[i]->getRect().left > CAMERAMANAGER->getCameraX() + WINSIZEX)
		{
			_vItem.erase(_vItem.begin() + i);
			break;
		}
		
	}
}

void itemManager::render()
{ // 아이템들은 제트오더에서 한번에 그릴거임
	
}


void itemManager::createBaseball(float x, float y)
{
	baseball* vbaseball;
	vbaseball = new baseball;
	vbaseball->init(x, y);
	itemAttack = false;
	_vItem.push_back(vbaseball);
}

void itemManager::createBomb(float x, float y)
{
	bomb* vbomb;
	vbomb = new bomb;
	vbomb->init(x, y);
	itemAttack = false;
	_vItem.push_back(vbomb);
}

void itemManager::throwing()
{
	itemAttack = true;
}

void itemManager::throwing(bool direction)
{
	itemAttack = true;
	_direction = direction;
}
