#include "stdafx.h"
#include "attack.h"

HRESULT attack::init(int attackMax)
{
	_attackMax = attackMax;
	_count = 10; // 초기에 카운트 부여
	return S_OK;
}

void attack::release()
{
}

void attack::update(int count)
{
	

	for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end();)
	{
		_count--; // 카운트가 감소하면 공격 렉트를 삭제하고 이후 초기화되게 했습니다
		if (_count <= 0)
		{
			_viAttack = _vAttack.erase(_viAttack);
            _count = 10;
		}
		else ++_viAttack;
	}



}

void attack::render()
{
	if(KEYMANAGER->isToggleKey(VK_TAB))
	{ 
		for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end(); ++_viAttack)
		{
			Rectangle(getMemDC(), _viAttack->rc);
		} 
	}
	
}

void attack::Attack(float x, float y)
{
	if (_attackMax < _vAttack.size()) return;
	tagAttack attack;
	ZeroMemory(&attack, sizeof tagAttack);
	attack.x = attack.attackX = x;
	attack.y = attack.attackY = y;

	attack.rc = RectMake(attack.x, attack.y, 150, 100); 
	_attackRect = RectMake(attack.x, attack.y, 150, 100); // 현정_콜리전위해 추가한것1

	_vAttack.push_back(attack);
}

void attack::removeAttack(int arrNum)
{
	_vAttack.erase(_vAttack.begin() + arrNum);
}
