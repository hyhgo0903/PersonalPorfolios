#include "stdafx.h"
#include "playerManager.h"
#include "itemManager.h"

// 키 입력은 여기에
void playerManager::keyInput()
{
	// 좌우 이동
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)
		&& _tank.rc.right <= MAPSIZEX && _tank.rc.right <= GETCAM + WINSIZEX) // 카메라 고정했을떄도 밖에 안나오게
	{
		COLORREF color = GetPixel(FINDIMG("맵픽셀")->getMemDC(), _tank.rc.right + 1, _tank.y);
		int r = GetRValue(color); int g = GetGValue(color); int b = GetBValue(color);
		if (r == 0 && g == 255 && b == 255) {} // 벽에 가로막힌경우 무시
		else
		{
			if (_tank.state == LEFTATTACK || _tank.state == LEFTRUN ||
				_tank.state == LEFTIDLE)
			{
				_tank.state = RIGHTRUN;
				_tank.angle = PI - _tank.angle;
				stateChange();
			}
			else if (_tank.state == RIGHTIDLE)
			{
				_tank.state = RIGHTRUN;
				stateChange();
			}
			if (_im->getStateSlot(1)) _tank.x += 4.5f; // 미탱 보유시
			else _tank.x += 3;
			_tank.rc = RectMakeCenter(_tank.x, _tank.y, TANKWIDTH, TANKHEIGHT);
		}

	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)
		&& !KEYMANAGER->isStayKeyDown(VK_RIGHT)
		&& _tank.rc.left > GETCAM)
	{
		COLORREF color = GetPixel(FINDIMG("맵픽셀")->getMemDC(), _tank.rc.left - 1, _tank.y);
		int r = GetRValue(color); int g = GetGValue(color); int b = GetBValue(color);
		if (r == 0 && g == 255 && b == 0) {}
		else
		{
			if (_tank.state == RIGHTATTACK || _tank.state == RIGHTRUN ||
				_tank.state == RIGHTIDLE)
			{
				_tank.state = LEFTRUN;
				_tank.angle = PI - _tank.angle;
				stateChange();
			}
			else if (_tank.state == LEFTIDLE)
			{
				_tank.state = LEFTRUN;
				stateChange();
			}
			if (_im->getStateSlot(1)) _tank.x -= 4.5f; // 미탱 보유시
			else _tank.x -= 3;
			if (_tank.x < GETCAM + TANKWIDTH / 2)
			{
				_tank.x = GETCAM + TANKWIDTH / 2;
			}
			_tank.rc = RectMakeCenter(_tank.x, _tank.y, TANKWIDTH, TANKHEIGHT);
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (_tank.state == LEFTRUN)		{	_tank.state = LEFTIDLE;		stateChange();	}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (_tank.state == RIGHTRUN)	{	_tank.state = RIGHTIDLE;	stateChange();	}
	}

	// 점프
	if (KEYMANAGER->isStayKeyDown(VK_UP) && !_tank.isJump)
	{
		_tank.isJump = true;
		if (_im->getStateSlot(1)) _tank.jumpPower = 6.5f; // 미탱 보유시
		else _tank.jumpPower = 6;
	}

	// 파워조절
	if (KEYMANAGER->isStayKeyDown('A')
		&& _tank.currentPower > 10) // 최소 파워값
	{
		_tank.currentPower -= 1;
	}
	if (KEYMANAGER->isStayKeyDown('D')
		&& _tank.currentPower < 100)
	{
		_tank.currentPower += 1;
		if (_tank.currentPower > 100) _tank.currentPower = 100;
	}

	// 발사는 오토파이어(Q)거나 스페이스 누른 상태면
	if (KEYMANAGER->isToggleKey('Q')
		&& _tank.currentDelay <= 0)
	{
		fire();
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE)
		&& _tank.currentDelay <= 0)
	{
		fire();
	}

	// 각도조절
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_tank.angle < 1.3963f) // 80도 보다 작을때
		{
			_tank.angle += 0.015f;
			if (_tank.angle > 1.3963f) _tank.angle = 1.3963f;
		}
		else if (_tank.angle > 1.7453f) // 100도 보다 클떄
		{
			_tank.angle -= 0.015f;
			if (_tank.angle < 1.7453f) _tank.angle = 1.7453f;
		}
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_tank.angle < PI / 2 && _tank.angle > 0.1745f)
		{//  10도
			_tank.angle -= 0.015f;
			if (_tank.angle < 0.17453f) _tank.angle = 0.17453f;
		}
		else if (_tank.angle > PI / 2 && _tank.angle < 2.967f)
		{//  170도
			_tank.angle += 0.015f;
			if (_tank.angle > 2.967f) _tank.angle = 2.967f;
		}
	}

	// 탱크교체
	if (KEYMANAGER->isOnceKeyDown(VK_F1) && _tank.type != CANNON && _im->getStateSlot(0))
	{
		EFFECTMANAGER->play("change", _tank.x, _tank.y);
		_tank.type = CANNON;
		if (_tank.state == RIGHTATTACK) _tank.state = RIGHTIDLE;
		else if (_tank.state == LEFTATTACK) _tank.state = LEFTIDLE;
		stateChange();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2) && _tank.type != MISSILE && _im->getStateSlot(1))
	{
		EFFECTMANAGER->play("change", _tank.x, _tank.y);
		_tank.type = MISSILE;
		if (_tank.state == RIGHTATTACK) _tank.state = RIGHTIDLE;
		else if (_tank.state == LEFTATTACK) _tank.state = LEFTIDLE;
		stateChange();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3) && _tank.type != MULTI && _im->getStateSlot(2))
	{
		EFFECTMANAGER->play("change", _tank.x, _tank.y);
		_tank.type = MULTI;
		if (_tank.state == RIGHTATTACK) _tank.state = RIGHTIDLE;
		else if (_tank.state == LEFTATTACK) _tank.state = LEFTIDLE;
		stateChange();
	}
	if (((KEYMANAGER->isOnceKeyDown(VK_F4) && _tank.type != SUPER) || !_autoChanged) && _im->getStateSlot(3))
	{ // 가능한상태에서(슬롯에 있을때) && 슈퍼가 아닐때 F4를 누르거나 오토체인지가 꺼져있다면
		_autoChanged = true;
		EFFECTMANAGER->play("change", _tank.x, _tank.y);
		_tank.type = SUPER;
		if (_tank.state == RIGHTATTACK) _tank.state = RIGHTIDLE;
		else if (_tank.state == LEFTATTACK) _tank.state = LEFTIDLE;
		stateChange();
	}

	// 템 사용
	if (KEYMANAGER->isOnceKeyDown('1') && _im->getUsingSlot(0) != EMPTY)
	{ // 슬롯이 이넘값이라 집어넣으면 깔끔하게 숫자로 처리됨
		_usingItem[_im->getUsingSlot(0)] = true;
		_itemDuration[_im->getUsingSlot(0)] = 0;
		_effectFrameX[_im->getUsingSlot(0)] = 0;
		_im->getUsingSlot(0) = EMPTY;
	}
	if (KEYMANAGER->isOnceKeyDown('2') && _im->getUsingSlot(1) != EMPTY)
	{
		_usingItem[_im->getUsingSlot(1)] = true;
		_itemDuration[_im->getUsingSlot(1)] = 0;
		_effectFrameX[_im->getUsingSlot(1)] = 0;
		_im->getUsingSlot(1) = EMPTY;
	}
	if (KEYMANAGER->isOnceKeyDown('3') && _im->getUsingSlot(2) != EMPTY)
	{
		_usingItem[_im->getUsingSlot(2)] = true;
		_itemDuration[_im->getUsingSlot(2)] = 0;
		_effectFrameX[_im->getUsingSlot(2)] = 0;
		_im->getUsingSlot(2) = EMPTY;
	}
	if (KEYMANAGER->isOnceKeyDown('4') && _im->getUsingSlot(3) != EMPTY)
	{
		_usingItem[_im->getUsingSlot(3)] = true;
		_itemDuration[_im->getUsingSlot(3)] = 0;
		_effectFrameX[_im->getUsingSlot(3)] = 0;
		_im->getUsingSlot(3) = EMPTY;
	}	
}