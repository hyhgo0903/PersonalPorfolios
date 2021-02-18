#include "stdafx.h"
#include "itemManager.h"
#include "playerManager.h"
// 아이템 드랍 헬기관리, 드랍된아이템 벡터로 관리 등등의 기능
itemManager::itemManager()
{
}

itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	_spdUpEffect = new effect;
	_spdUpEffect->init(IMAGEMANAGER->findImage("스피드업"), 45, 29, 1, 0.1f);
	EFFECTMANAGER->addEffect("spdup", "image/effectspeedup.bmp", 900, 29, 45, 29, 1.0f, 0.1f, 20);
	_powUpEffect = new effect;
	_powUpEffect->init(IMAGEMANAGER->findImage("파워업"), 49, 29, 1, 0.1f);
	EFFECTMANAGER->addEffect("powup", "image/effectpowerup.bmp", 980, 29, 49, 29, 1.0f, 0.1f, 20);
	_delDownEffect = new effect;
	_delDownEffect->init(IMAGEMANAGER->findImage("딜레이다운"), 45, 29, 1, 0.1f);
	EFFECTMANAGER->addEffect("deldown", "image/effectdelaydown.bmp", 900, 29, 45, 29, 1.0f, 0.1f, 20);
	_scoreUpEffect = new effect;
	_scoreUpEffect->init(IMAGEMANAGER->findImage("스코어업"), 45, 29, 1, 0.1f);
	EFFECTMANAGER->addEffect("scoreup", "image/effectscore.bmp", 900, 29, 45, 29, 1.0f, 0.1f, 20);

	_itemScore = 0;
	_wind = 0.f;
	_heliRegenCount = 0;
	_heliRC = {0,0,0,0};
	_heliAppear = _heliUp = false;
	for (int i = 0; i < MAPSIZEX/600; i++)
	{
		_heliArr[i] = false; 
	}
	for (int i = 0; i < 4; i++)
	{
		_usingSlot[i] = EMPTY; // 초기 아이템 상태
		_stateSlot[i] = false;
	}

	return S_OK;
}

void itemManager::release()
{
	_vDroppedItem.clear();
	SAFE_RELEASE(_spdUpEffect);
	SAFE_DELETE(_spdUpEffect);
	SAFE_RELEASE(_powUpEffect);
	SAFE_DELETE(_powUpEffect);
	SAFE_RELEASE(_delDownEffect);
	SAFE_DELETE(_delDownEffect);
	SAFE_RELEASE(_scoreUpEffect);
	SAFE_DELETE(_scoreUpEffect);
}

void itemManager::update()
{
	heliMove();
	test();
	for (int i = 0; i< MAPSIZEX / 600; i++)
	{
		if (GETCAM > 600 * i && !_heliArr[i])
		{ // 600거리마다 불값켜주고(앞으로 더 안나옴) 젠
			_heliArr[i] = true;
			generateUsingItem();
		}
	}
	if (GETCAM > MAPSIZEX - WINSIZEX - 5) // 맵끝 도달하면(보스전) 일정 시간마다 젠됨
	{
		if (_heliRegenCount < 480) _heliRegenCount++;
		else
		{
			_heliRegenCount = 0;
			_heliArr[0] = false;
		}
	}
	
	itemUpdate();
	if (_stateSlot[0] && _stateSlot[1] && _stateSlot[2]) _stateSlot[3] = true;	

	EFFECTMANAGER->update();
	_spdUpEffect->update();
	_powUpEffect->update();
	_delDownEffect->update();
}

void itemManager::render()
{
	if (_heliAppear)
	{
		FINDIMG("헬기")->render(getMemDC(), _heliRC.left, _heliRC.bottom - 52);
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			Rectangle(getMemDC(), _heliRC);
		}
	}
	
	for (_viDroppedItem = _vDroppedItem.begin(); _viDroppedItem != _vDroppedItem.end(); ++_viDroppedItem)
	{
		(*_viDroppedItem)->render();
	}
	slotRender();

	EFFECTMANAGER->render();
	_spdUpEffect->render();
	_powUpEffect->render();
	_delDownEffect->render();
}

void itemManager::generateUsingItem()
{ // 헬기위치 지정하고 등장하게 하는 함수
	if (_heliAppear) return;
	_heliAppear = true;
	_heliRC = RectMake(GETCAM + 300 + rand() % 200, 0,90,0);
}

void itemManager::heliMove()
{ // 위 함수랑 연동됨. 헬기등장하면 최하점가고 아이템떨구고 다시 올리는 함수
	if (!_heliAppear) return;
	_heliRC.left += -2 + rand() % 5; // 흔들리는 효과
	_heliRC.right = _heliRC.left + 90;
	if (_heliUp)
	{
		_heliRC.bottom -= 1; // 탑은 0으로 고정되었고 바텀만 내려감(미니맵에 그려주기 위해..)
		if (_heliRC.bottom <= 0)
		{
			_heliAppear = false;
			_heliUp = false;
		}
	}
	else
	{
		_heliRC.bottom += 1;
		if (_heliRC.bottom >= 52) // 최하점에 도달했으면
		{
			dropUsingItem();
			_heliUp = true;
		}
	}	
}

void itemManager::dropUsingItem()
{ // 사용템을 떨구라고 전해라
	droppedItem* item;
	item = new droppedItem;
	item->init(false,(_heliRC.left+_heliRC.right)/2,_heliRC.bottom);
	_vDroppedItem.push_back(item);
}

void itemManager::dropStateItem(float x, float y)
{ // 상태템을 떨구라고 전해라 x,y좌표에..
	droppedItem* item;
	item = new droppedItem;
	item->init(true, x, y);
	_vDroppedItem.push_back(item);
}

void itemManager::itemUpdate()
{
	for (int i = 0; i < _vDroppedItem.size(); ++i)
	{
		// 각종연산
		_vDroppedItem[i]->update();
		// 스피드를 바람값으로 맞춰주기
		_vDroppedItem[i]->getXSpd() = 2.f* _wind;
		// 충돌
		RECT temp;
		if (IntersectRect(&temp, &_pm->getRect(), &_vDroppedItem[i]->getRect()))
		{
			_vDroppedItem[i]->getDisappear() = true;
			switch (_vDroppedItem[i]->getItemType())
			{
			case -1: // 상자를 먹은거면 랜덤을 굴린다
				getItem(rand() % 4);
				break;
			case 0: if (!_stateSlot[0]) _getEffect(0);
				if (_stateSlot[0])
				{
					++_itemScore;
					EFFECTMANAGER->play("scoreup", _pm->getRect().left + 23, _pm->getRect().top + 23);
				}
				_stateSlot[0] = true;	break;
			case 1: if (!_stateSlot[1]) _getEffect(1);
				if (_stateSlot[1])
				{
					++_itemScore;
					EFFECTMANAGER->play("scoreup", _pm->getRect().left + 23, _pm->getRect().top + 23);
				}
				_stateSlot[1] = true;	break;
			case 2: if (!_stateSlot[2]) _getEffect(2);
				if (_stateSlot[2])
				{
					++_itemScore;
					EFFECTMANAGER->play("scoreup", _pm->getRect().left + 23, _pm->getRect().top + 23);
				}
				_stateSlot[2] = true;	break;
			}
		}
	}
	bool recheck;
	recheck = true;
	while (recheck)
	{
		recheck = false;
		for (int i = 0; i < _vDroppedItem.size(); ++i)
		{
			if (_vDroppedItem[i]->getDisappear())
			{ // 디스어피어 켜져있으면 삭제(화면밖 or 지속시간 끝)
				SAFE_RELEASE(_vDroppedItem[i]);
				SAFE_DELETE(_vDroppedItem[i]);
				_vDroppedItem.erase(_vDroppedItem.begin() + i);
				recheck = true;
				break;
			}
		}
	}	
}

void itemManager::getItem(int x)
{
	int emptySlot = 4;
	for (int i = 0; i < 4; i++)
	{
		if (_usingSlot[i] == EMPTY)
		{
			emptySlot = i;
			break;
		}
	} // 빈공간을 찾는 반복문
	if (emptySlot == 4)
	{
		++_itemScore;
		EFFECTMANAGER->play("scoreup", _pm->getRect().left + 23, _pm->getRect().top + 23);
		return; // 꽉찬거니까 안받음.
	}		 

	switch (x)
	{ // 빈칸의 이넘값을 바꿔줌
	case 0: _usingSlot[emptySlot] = DOUBLEFIRE;		break;
	case 1:	_usingSlot[emptySlot] = POWERUP;		break;
	case 2:	_usingSlot[emptySlot] = SHIELD;			break;
	case 3:	_usingSlot[emptySlot] = REPAIR;			break;
	}
}

void itemManager::slotRender()
{
	// 상태창 렌더링
	for (int i = 0; i < 4; i++)
	{
		if (_stateSlot[i])
		{
			FINDIMG("상태템슬롯")->frameRender(getMemDC(), GETCAM + 479 + 39 * i, 415, i, 0);
		}
	}
	// 사용템창 렌더링
	for (int i = 0; i < 4; i++)
	{
		if (_usingSlot[i] == EMPTY) continue;
		FINDIMG("사용템슬롯")->frameRender(getMemDC(), GETCAM+254 + 34 * i, 415 , _usingSlot[i], 0);
	} // 이넘을 숫자변수(framex)으로 썼음
}

void itemManager::test() // 테스트용 아이템 만들기 치트키
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
	{
		if (_heliAppear) return;
		_heliAppear = true;
		_heliRC = RectMake(GETCAM + 150, 0, 90, 0);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8)) dropStateItem(GETCAM + 150, 300);
}

void itemManager::_getEffect(int x)
{
	switch (x)
	{
	case 0:EFFECTMANAGER->play("powup", _pm->getRect().left+23, _pm->getRect().top + 23);		break;
	case 1:EFFECTMANAGER->play("spdup", _pm->getRect().left + 23, _pm->getRect().top + 23);		break;
	case 2:EFFECTMANAGER->play("deldown", _pm->getRect().left + 23, _pm->getRect().top + 23);	break;
	}
}
