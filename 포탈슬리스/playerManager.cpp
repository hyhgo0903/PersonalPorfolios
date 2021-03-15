#include "stdafx.h"
#include "playerManager.h"
#include "itemManager.h"
#include "bulletManager.h"


HRESULT playerManager::init(int data)
{
	_difficulty = data / 10;
	_selectedTank = data % 10;
	
	_changeEffect = new effect;
	_changeEffect->init(IMAGEMANAGER->findImage("교체"), 40, 40, 1, 0.5f);
	EFFECTMANAGER->addEffect("change", "image/effectchange.bmp", 800, 40, 40, 40, 1.0f, 0.2f, 20);	

	

	switch (_selectedTank)
	{
	case 0:_tank.type = CANNON;		break;
	case 1:_tank.type = MISSILE;	break;
	case 2:_tank.type = MULTI;		break;
	}

	_isGameOver = false;
	_tank.x = 50;
	_tank.y = 50;
	_tank.rc = RectMakeCenter(_tank.x, _tank.y, TANKWIDTH, TANKHEIGHT);
	_alphaValue = 255;

	_tank.state = RIGHTIDLE;
	if (_difficulty == 0) { _tank.currentHP = _tank.maxHP = 500; }
	else if (_difficulty == 1) { _tank.currentHP = _tank.maxHP = 100; }
	else if (_difficulty == 2) { _tank.currentHP = _tank.maxHP = 50; }
	stateChange();

	_tank.angle = PI / 4;

	for (int i = 0; i < 4; i++)
	{		
		_usingItem[i] = false;
		_itemDuration[i] = 0;
		_effectFrameX[i] = 0;
	}	 

	_tank.currentDelay = _tank.maxDelay = _tank.maxPower = _tank.currentPower = 100;
	_tank.gravity = _tank.jumpPower = 0.f;
	_tank.angle = PI / 4;
	_tank.frameX = _tank.aniCount = 0;

	_tank.isJump = true;
	_autoChanged = _isBlink = _isInvincible = false;
	_specialCount = _blinkCount = 0;

	return S_OK;
}

void playerManager::release()
{
}

void playerManager::update()
{
	CAMERAMANAGER->focusOnRect(_tank.rc, 2);	// 화면에 맞춰주는 함수
	keyInput();			// 키입력
	tankMove();			// 픽셀충돌 및 중력등으로 탱크이동
	delayReduce();
	animationUpdate();

	for (int i = 0; i < 4; ++i) // 아이템 지속시간 돌고 프레임도 돌고 내 머리도 돌고
	{
		if (_usingItem[i])
		{
			if (_itemDuration[i] < ITEMDURATION) ++_itemDuration[i]; // 지속시간 채우기
			else _usingItem[i] = false;								// 찼으면 끄기
			if (_itemDuration[i] % 6 == 0)							// 애니메이션은 0.1초마다 갱신하는걸로
			{
				++_effectFrameX[i];
				if ((i == 0 && _effectFrameX[i] > 5) || (i == 1 && _effectFrameX[i] > 3) ||
					(i == 2 && _effectFrameX[i] > 4) || (i == 3 && _effectFrameX[i] > 8)) _effectFrameX[i] = 0;
				// 이펙트마다 있는 프레임 끝점 넘으면 초기화
			}
		}
	}
	if (_usingItem[3]) // 회복중이면 회복을 합니당
	{
		if (_difficulty == 0) _tank.currentHP += 1.5f;
		_tank.currentHP += 0.5f;
		if (_tank.currentHP >= _tank.maxHP)
		{
			_tank.currentHP = _tank.maxHP;
			_usingItem[3] = false;
		}
	} // 딜계수 계산은 여기서
	if		(_difficulty == 0)	{ _damageCoefficient = 2;	} // 난이도 별로 딜보정
	else if (_difficulty == 1)	{ _damageCoefficient = 1;	}
	else if (_difficulty == 2)	{ _damageCoefficient = 0.5f; }
	if (_usingItem[1]) _damageCoefficient *= 2; // 파워업아이템 사용시 딜2배
	if (_im->getStateSlot(0)) _damageCoefficient *= 1.5; // 캐논상태템 보유시 딜1.5배
	if (_usingItem[2] || _isBlink) _isInvincible = true; // 깜빡이거나 쉴드사용중이면 무적
	else _isInvincible = false; // 둘다 아니면 무적아님
	if (_isBlink && _blinkCount % 10 < 5) _alphaValue= 100;
	if (_isBlink && _blinkCount % 10 > 4) _alphaValue = 200;
	if (_isBlink && _blinkCount < 120) _blinkCount++;
	if (_blinkCount >= 120)
	{
		_blinkCount = 0;
		_isBlink = false;
		_alphaValue = 255;
	}
	EFFECTMANAGER->update();
	_changeEffect->update();
	test();
	if (_tank.currentHP <= 0 && _difficulty != 0)
	{ // 시연용 난이도 빼면 게임오버씬 소환
		_isGameOver = true;
	}
	if (_tank.currentHP < 0) _tank.currentHP = 0;
}

void playerManager::render()
{
	if (_usingItem[0])	FINDIMG("바람이펙트")->frameRender(getMemDC(), _tank.rc.left-2, _tank.rc.top-25, _effectFrameX[0], 0);
	if (_usingItem[1])	FINDIMG("별이펙트")->frameRender(getMemDC(), _tank.rc.left-16, _tank.rc.top-12, _effectFrameX[1], 0);
	if (_usingItem[2])	FINDIMG("쉴드이펙트")->frameRender(getMemDC(), _tank.rc.left-21, _tank.rc.top-20, _effectFrameX[2], 0);
	if (_usingItem[3])	FINDIMG("힐이펙트")->frameRender(getMemDC(), _tank.rc.left - 14, _tank.rc.top-12, _effectFrameX[3], 0);

	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _tank.rc);
	stateRender();	interfaceRender();
	for (int i = 0; i < 4; i++) // 이용중이면 표시해줌
	{
		if (_usingItem[i])
		{ // 마지막에 깜빡거리는 효과를 주려고 지속 카운트 상태별로 출력하지 않음
			if (_itemDuration[i] > ITEMDURATION - 120 && _itemDuration[i] % 20 > 9)	{}
			else FINDIMG("사용템버프표시")->alphaFrameRender(getMemDC(), GETCAM+63*i, 0, i, 0, 150);
		}
	}
	EFFECTMANAGER->render();
	_changeEffect->render();
}

// 탱크 이동(픽셀충돌, 중력영향)
void playerManager::tankMove()
{
	// RECT바텀 기준으로 탐지
	_tank.probeY = _tank.rc.bottom;
	for (int i = _tank.probeY - 4; i < _tank.probeY + 8; ++i)
	{ // 바텀-4~바텀+8까지 검사
		COLORREF color = GetPixel(FINDIMG("맵픽셀")->getMemDC(), _tank.x, i);
		int r = GetRValue(color); int g = GetGValue(color); int b = GetBValue(color);
		if (!(r == 255 && g == 0 && b == 255) && _tank.y > 0)
		{ // 특정 색상값이 아님 -> 착지한 상태
			if (_tank.jumpPower <= 0)
			{
				_tank.isJump = false; _tank.jumpPower = 0; // 점프끄기				
				_tank.y = i - TANKHEIGHT / 2; break;	// 탱크밑변 맞춰줌
			}
		}
		if (_tank.probeY + 7 == i) // 끝까지 갔는데 안착지
		{
			_tank.jumpPower -= GRAVITY; // 중력및 낙하 적용
			if (_tank.jumpPower < -2) _tank.isJump = true;
		}
	}
	_tank.y -= _tank.jumpPower;
	_tank.rc = RectMakeCenter(_tank.x, _tank.y, TANKWIDTH, TANKHEIGHT);
}

void playerManager::delayReduce()
{
	if (_tank.currentDelay > 0)
	{	_tank.currentDelay -= 1.75f;	}
	if (_im->getStateSlot(2) && _tank.currentDelay > 0) // 추가로 딜레이 감소
	{	_tank.currentDelay -= 0.75f;	}
	if (_usingItem[0] && _tank.currentDelay > 0) // 더블파이어 상태면 추가로 딜레이 감소
	{	_tank.currentDelay -= 0.5f;	}
	if (_tank.currentDelay < 0) _tank.currentDelay = 0;
}

void playerManager::test() // 테스트용 치트키 - 릴리즈떈 지울것
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4)) _tank.currentHP = _tank.maxHP * 0.2f;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5)) _tank.currentHP = _tank.maxHP;
}
