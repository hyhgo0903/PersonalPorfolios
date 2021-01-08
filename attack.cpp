#include "stdafx.h"
#include "attack.h"

HRESULT attack::init(int attackMax, int count)
{
	_attackMax = attackMax;
	_count = count;
	return S_OK;
}

void attack::release()
{
}

void attack::update(int count)
{
	

	for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end();)
	{
		_count--;
		if (_count <= 0)
		{
			_viAttack = _vAttack.erase(_viAttack);
			_count = count;
		}
		else ++_viAttack;
	}



}

void attack::render()
{
	
		for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end(); ++_viAttack)
		{
			Rectangle(getMemDC(), _viAttack->rc);
		} 
	
}

void attack::Attack(float x, float y)
{
	if (_attackMax < _vAttack.size()) return;
	tagAttack attack;
	ZeroMemory(&attack, sizeof tagAttack);
	attack.x = attack.attackX = x;
	attack.y = attack.attackY = y;

	attack.rc = RectMakeCenter(attack.x, attack.y, 100, 20);

	_vAttack.push_back(attack);
}

void attack::removeAttack(int arrNum)
{
	_vAttack.erase(_vAttack.begin() + arrNum);
}
