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
		}

		if (KEYMANAGER->isOnceKeyDown('2'))
		{
			_vItem.clear();
			createBomb(500, CAMY + 500);
		}
		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			_vItem.clear();
			createPizza(500, CAMY + 600);
			for(int i =0; i<4;i++) createFood(600, CAMY + 600);
		}
		if (KEYMANAGER->isOnceKeyDown('4'))
		{
			_vItem.clear();
			createBat(500, CAMY + 600);
		}
	}
	
	
	{
		for (int i = 0; i < _vItem.size(); i++)
		{
			if (_vItem[i]->isFood())
			{
				if (_vItem[i]->getDelete())
				{
					_vItem.erase(_vItem.begin() + i);
					return;
				}
			}
			if (_vItem[i]->getMoving())
			{
				_vItem[i]->attackMove(_direction);
				if (_vItem[i]->getDelete())
				{
					if (_vItem[i]->getID() == 2)
					{
						EFFECTMANAGER->play("폭발", ((_vItem[i]->getRect().right + _vItem[i]->getRect().left) / 2), _vItem[i]->getRect().top);
						EFFECTMANAGER->play("폭발", _vItem[i]->getRect().right, _vItem[i]->getRect().top - 50);
						EFFECTMANAGER->play("폭발", _vItem[i]->getRect().left, _vItem[i]->getRect().top - 50);
						_vItem.erase(_vItem.begin() + i);
					}
					
				}
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

void itemManager::createBaseball(float x, float y, float bottom)
{
	baseball* vbaseball;
	vbaseball = new baseball;
	vbaseball->init(x, y, bottom);
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

void itemManager::createBomb(float x, float y, float bottom)
{
	bomb* vbomb;
	vbomb = new bomb;
	vbomb->init(x, y, bottom);
	itemAttack = false;
	_vItem.push_back(vbomb);
}

void itemManager::createPizza(float x, float y)
{
	pizza* vPizza;
	vPizza = new pizza;
	vPizza->init(x - 50, y);
	_vItem.push_back(vPizza);
}

void itemManager::createPizza(float x, float y, float bottom)
{
	pizza* vPizza;
	vPizza = new pizza;
	vPizza->init(x - 50, y, bottom);
	_vItem.push_back(vPizza);

}

void itemManager::createFood(float x, float y)
{
	switch (RND->getInt(5))
	{
	case 0:
		pudding* vPudding;
		vPudding = new pudding;
		vPudding->init(x, y);
		_vItem.push_back(vPudding);
		break;
	case 1:
		hamberger* vHamberger;
		vHamberger = new hamberger;
		vHamberger->init(x + 50, y);
		_vItem.push_back(vHamberger);
		break;
	case 2:
		cereal* vCereal;
		vCereal = new cereal;
		vCereal->init(x + 100, y);
		_vItem.push_back(vCereal);
		break;
	case 3:
		fries* vFries;
		vFries = new fries;
		vFries->init(x + 150, y);
		_vItem.push_back(vFries);
		break;
	case 4:
		juice* vjuice;
		vjuice = new juice;
		vjuice->init(x, y);
		_vItem.push_back(vjuice);
		break;
	default:
		break;
	}


	

	

	

	
}

void itemManager::createFood(float x, float y, float bottom)
{
	pudding* vPudding;
	vPudding = new pudding;
	vPudding->init(x, y, bottom);

	_vItem.push_back(vPudding);

	hamberger* vHamberger;
	vHamberger = new hamberger;
	vHamberger->init(x + 50, y, bottom);
	_vItem.push_back(vHamberger);

	cereal* vCereal;
	vCereal = new cereal;
	vCereal->init(x + 100, y, bottom);
	_vItem.push_back(vCereal);

	juice* vjuice;
	vjuice = new juice;
	vjuice->init(x, y, bottom);
	_vItem.push_back(vjuice);
}

void itemManager::createBat(float x, float y)
{
	bat* vBat;
	vBat = new bat;
	vBat->init(x, y);
	_vItem.push_back(vBat);
}

void itemManager::createBat(float x, float y, float bottom)
{
	bat* vBat;
	vBat = new bat;
	vBat->init(x, y, bottom);
	_vItem.push_back(vBat);
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
