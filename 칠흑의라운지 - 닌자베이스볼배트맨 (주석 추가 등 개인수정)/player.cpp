#include "stdafx.h"
#include "player.h"
#include "STATE.h"
#include "Idle.h"
#include "Jump.h"
#include "walk.h"
#include "run.h"
#include "hit.h"
#include "combo1.h"
#include "combo11.h"
#include "combo12.h"
#include "combo13.h"
#include "combo21.h"
#include "combo22.h"
#include "combo23.h"
#include "jumpAttack.h"
#include "tackle.h"
#include "slide.h"
#include "dead.h"
#include "cidleAnimation.h"
#include "windmill.h"
#include "grab.h"
#include "grabswing.h"
#include "enemyManager.h"
// 각각의 상태를 상호참조했습니다

HRESULT player::init()
{
	playerImage = IMAGEMANAGER->findImage("플레이어대기");
	_count = _index = 0;
	_flyX = _groundX = 100.f;
	_flyY = _groundY = CAMY + 500.f;
	_directionChanged = _directionChangeCount = _dirMemory = _dirMemoryCount = 0;
	_flyRc = RectMakeCenter(_flyX, _flyY, 100, 100);
	_groundRc = RectMakeCenter(_groundX, _groundY, 100, 100);
	_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 150, 50);
	_currentHP = _maxHP = 100.f;
    _jumpPower = 15;
	_left = false;
	setState(IDLE);
	_attack = new attack;
	_attack->init(8);
    _isGrab = false;
	//setState(IDLE);
	_em = new enemyManager;
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_statePattern->updateState();
	stateUpdate();
	_flyRc = RectMakeCenter(_flyX, _flyY, 100, 200);
	_groundRc = RectMakeCenter(_groundX, _groundY, 100, 200);
	minusDirectionChanged();
	_attack->update(50);
}

void player::render()
{
	_attack->render();
}

void player::minusDirectionChanged()
{
	if (_directionChanged > 0) // 방향전환이 일어났다면
	{
		if (_directionChanged > 2)
		{
			_directionChanged = 2; // 방향전환 2번 넘으면 2번으로 해주고 카운트를 측정 시작
			_directionChangeCount = 0;
		}
		++_directionChangeCount; 
		if (_directionChangeCount > 30) // 30(0.5초) 이상 지났다면 카운트를 0으로 돌리고 방향전환을 감소시킵니다
		{
			_directionChangeCount = 0; 	--_directionChanged; 
		}
	} //방향전환 두 번 일어난 경우 특수키 사용조건으로 했습니다
	if (_dirMemory > 0) // 방향이 기억되어 있다면 30(0.5초)카운트내로 초기화 시켜줍니다
	{
		++_dirMemoryCount;
		if (_dirMemoryCount > 30)
		{ 
			_dirMemoryCount = 0; _dirMemory = 0;
		}
	}
}

void player::playerRender()
{
	//임의로 그림자를 그렸습니다.
	HPEN pen = CreatePen(0, 2, RGB(30, 30, 30));
	HPEN oldpen = (HPEN)SelectObject(getMemDC(), pen);
	HBRUSH brush = CreateSolidBrush(RGB(30, 30, 30));
	HBRUSH oldbrush = (HBRUSH)SelectObject(getMemDC(), brush);
	Ellipse(getMemDC(), _shadow);
	SelectObject(getMemDC(), oldbrush);
	DeleteObject(brush);
	SelectObject(getMemDC(), oldpen);
	DeleteObject(pen);
	//상태에 따른 이미지를 호출해서 그리도록 해줬습니다
	stateRender();
	//충돌범위 확인등을 위해 플레이어의 렉트를 토글하여 보여줄 수 있도록 했습니다
	if(KEYMANAGER->isToggleKey(VK_TAB))
	{ 
		Rectangle(getMemDC(), _groundRc);
		Rectangle(getMemDC(), _flyRc);
		Rectangle(getMemDC(), _shadow);		
	}
}

void player::reRender()
{
	//이미지 중점용변수입니다

	float imageCenterX = (((_flyRc.left + _flyRc.right) / 2) - (playerImage->getFrameWidth() / 2));
	float imageCenterY = (((_flyRc.bottom + _flyRc.top) / 2) - (playerImage->getFrameHeight() / 2));


	switch (_enumState)
	{
	case DEAD:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50); // 상태에 따라 그림자렉트를 만들게 해줬고, 각각의 상태에서 참조하는 좌표와 크기를 다르게 해줬습니다.
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX - 28, imageCenterY - 16, _index, 0, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX + 28, imageCenterY - 16, _index, 1, 150);
		break;
	case IDLE:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX - 28, imageCenterY - 16, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX + 28, imageCenterY - 16, 150);
		break;
	case CIDLEANIMATION:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX, imageCenterY - 16, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX, imageCenterY - 16, 150);
		break;
	case JUMP:
		_shadowWidth = 200 - ((_groundRc.bottom - _flyRc.bottom) / 2); // 점프 및 점프공격 상태일 땐 점프하는 위치만큼 그림자 렉트를 줄여서 만들게 했습니다.
		if (_shadowWidth < 0) _shadowWidth = 0;
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, _shadowWidth, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX + 23, imageCenterY - 18, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX - 23, imageCenterY - 18, 150);
		break;
	case WALK:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 125, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX - 21, imageCenterY - 18, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX + 21, imageCenterY - 18, 150);
		break;
	case RUN:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 150, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX, imageCenterY - 16, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX, imageCenterY - 16, 150);
		break;
	case HIT:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX - 15, imageCenterY - 15, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX + 15, imageCenterY - 15, 150);
		break;
	case COMBO1:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 150, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX + 65, imageCenterY, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX - 65, imageCenterY, 150);
		break;
	case COMBO11:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 150, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX + 15, imageCenterY - 10, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX - 15, imageCenterY - 10, 150);
		break;
	case COMBO12:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX + 55, imageCenterY - 52, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX - 55, imageCenterY - 52, 150);
		break;
	case COMBO13:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX + 70, imageCenterY - 30, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX - 70, imageCenterY - 30, 150);
		break;
	case COMBO21:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX + 35, imageCenterY - 30, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX - 35, imageCenterY - 30, 150);
		break;
	case COMBO22:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX - 20, imageCenterY - 10, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX + 20, imageCenterY - 10, 150);
		break;
	case COMBO23:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX + 75, imageCenterY - 5, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX - 75, imageCenterY - 5, 150);
		break;
	case SLIDE:
		_shadow = RectMakeCenter(_flyX, _flyRc.bottom, 200, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX - 40, imageCenterY + 15, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX + 40, imageCenterY + 15, 150);
		break;
	case TACKLE:
		_shadow = RectMakeCenter(_flyX, _flyRc.bottom, 150, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX, imageCenterY - 10, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX, imageCenterY - 10, 150);
		break;
	case JUMPATTACK:
		_shadowWidth = 200 - ((_groundRc.bottom - _flyRc.bottom) / 2);
		if (_shadowWidth < 0) _shadowWidth = 0;
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, _shadowWidth, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX + 60, imageCenterY - 10, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX - 60, imageCenterY - 10, 150);
		break;
	case GRAB:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 150, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX + 23, imageCenterY - 15, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX - 23, imageCenterY - 15, 150);
		break;
	case GRABSWING:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX + 60, imageCenterY - 25, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX - 60, imageCenterY - 25, 150);
		break;
	case WINDMILL:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 125, 50);
		if (!_left) playerImage->alphaFrameRender(getMemDC(), imageCenterX, imageCenterY - 35, 150);
		else playerImage->alphaFrameRender(getMemDC(), imageCenterX, imageCenterY - 35, 150);
		break;

	}
}

//상태설정

void player::setState(State state)
{
	if (_statePattern)_statePattern->ExitState();
	// setState 함수 실행시 기존 상태를 우선 탈출하도록 설정했습니다
	_enumState = state;
	switch (state)
	{ // 각 상태에 따른 객체를 생성했습니다
	case IDLE:		    _statePattern = new Idle;	break;
	case CIDLEANIMATION:_statePattern = new cidleAnimation; break;
	case JUMP:			_statePattern = new Jump;	break;
	case WALK:			_statePattern = new walk;	break;
	case RUN:			_statePattern = new run;	break;
    case HIT:           _statePattern = new hit;    break;
	case COMBO1:		_statePattern = new combo1; break;
	case COMBO11:		_statePattern = new combo11; break;
	case COMBO12:		_statePattern = new combo12; break;
	case COMBO13:		_statePattern = new combo13; break;
    case COMBO21:		_statePattern = new combo21; break;
    case COMBO22:		_statePattern = new combo22; break;
    case COMBO23:		_statePattern = new combo23; break;
    case JUMPATTACK:	_statePattern = new jumpAttack; break;
    case SLIDE:			_statePattern = new slide; break;
    case TACKLE:		_statePattern = new tackle; break;
    case WINDMILL:      _statePattern = new windmill; break;
    case GRAB:          _statePattern = new grab; break;
    case GRABSWING:     _statePattern = new grabswing; break;
	case DEAD:     _statePattern = new dead; break;
	}
	_statePattern->LinkMemberAdress(this);
	// 각각의 상태에서 다른 상태로 옮길때 사용할 참조용 링크입니다
	_statePattern->EnterState();
	// 위의 일련의 과정이 끝난 후 해당 상태에 돌입하게 했습니다

}

//상태에 따라 이미지를 찾고 재생해주는 함수입니다
void player::stateUpdate()
{
	_count++;
	if (_count % 5 == 0)
	{
		switch (_enumState)
		{
		case IDLE:
			playerImage = IMAGEMANAGER->findImage("플레이어대기"); // 공격을 제외한 이미지는 방향에 따라 재생을 도와주는 인덱스 변수가 증가 혹은 감소하고,
			if (!_left) { playerImage->setFrameY(0); }
			else { playerImage->setFrameY(1); }
			playerImage->setFrameX(0);
			break;
		case CIDLEANIMATION:
			playerImage = IMAGEMANAGER->findImage("플레이어대기모션");
			{
				if (_index >= 4) _index = 0;
				playerImage->setFrameY(0);
				playerImage->setFrameX(_index);
				_index++;
			}
			break;
		case JUMP:
			playerImage = IMAGEMANAGER->findImage("플레이어점프");
			if (!_left) { playerImage->setFrameY(0); }
			else { playerImage->setFrameY(1); }
			playerImage->setFrameX(0);
			break;
		case WALK:
			playerImage = IMAGEMANAGER->findImage("플레이어이동");
			if (!_left)
			{
				if (_index >= 5) _index = 0;
				playerImage->setFrameY(0);
				playerImage->setFrameX(_index);
				_index++;
			}
			else
			{
				if (_index <= 0) _index = 5;
				playerImage->setFrameY(1);
				playerImage->setFrameX(_index);
				_index--;
			}
			break;
		case RUN:
			playerImage = IMAGEMANAGER->findImage("플레이어대시");
			if (!_left)
			{
				if (_index >= 3) _index = 0;
				playerImage->setFrameY(0);
				playerImage->setFrameX(_index);
				_index++;
			}
			else
			{
				if (_index <= 0) _index = 3;
				playerImage->setFrameY(1);
				playerImage->setFrameX(_index);
				_index--;
			}
			break;
        case HIT:
            playerImage = IMAGEMANAGER->findImage("플레이어히트");
            if (!_left) { playerImage->setFrameY(0); }
            else { playerImage->setFrameY(1); }
            playerImage->setFrameX(_index);
            _index++;
            break;
		case COMBO1:
			playerImage = IMAGEMANAGER->findImage("플레이어공격"); // 공격은 증가로만 조절하게 했습니다.
			if (!_left)
			{
				if (_index >= 6) setState(IDLE);
				playerImage->setFrameY(0);
				playerImage->setFrameX(_index);
				_index++;
			}
			else
			{
				if (_index >= 6) setState(IDLE);
				playerImage->setFrameY(1);
				playerImage->setFrameX(_index);
				_index++;
			}
			break;
		case COMBO11:
			playerImage = IMAGEMANAGER->findImage("플레이어공격1-1");
			if (!_left)
			{
				if (_index >= 4) setState(IDLE);
				playerImage->setFrameY(0);
				playerImage->setFrameX(_index);
				_index++;
			}
			else
			{
				if (_index >= 4) setState(IDLE);
				playerImage->setFrameY(1);
				playerImage->setFrameX(_index);
				_index++;
			}
			break;
		case COMBO12:
			playerImage = IMAGEMANAGER->findImage("플레이어공격1-2");
			if (!_left)
			{
				if (_index >= 4) setState(IDLE);
				playerImage->setFrameY(0);
				playerImage->setFrameX(_index);
				_index++;
			}
			else
			{
				if (_index >= 4) setState(IDLE);
				playerImage->setFrameY(1);
				playerImage->setFrameX(_index);
				_index++;
			}
			break;
		case COMBO13:
			playerImage = IMAGEMANAGER->findImage("플레이어공격1-3");
			if (!_left)
			{
				if (_index >= 4) setState(IDLE);
				playerImage->setFrameY(0);
				playerImage->setFrameX(_index);
				_index++;
			}
			else
			{
				if (_index >= 4) setState(IDLE);
				playerImage->setFrameY(1);
				playerImage->setFrameX(_index);
				_index++;
			}
			break;
        case COMBO21:
            playerImage = IMAGEMANAGER->findImage("플레이어공격2-1");
            if (!_left)
            {
                if (_index >= 4) setState(IDLE);
                playerImage->setFrameY(0);
                playerImage->setFrameX(_index);
                _index++;
            }
            else
            {
                if (_index >= 4) setState(IDLE);
                playerImage->setFrameY(1);
                playerImage->setFrameX(_index);
                _index++;
            }
            break;
        case COMBO22:
            playerImage = IMAGEMANAGER->findImage("플레이어공격2-2");
            if (!_left)
            {
                if (_index >= 4) setState(IDLE);
                playerImage->setFrameY(0);
                playerImage->setFrameX(_index);
                _index++;
            }
            else
            {
                if (_index >= 4) setState(IDLE);
                playerImage->setFrameY(1);
                playerImage->setFrameX(_index);
                _index++;
            }
            break;
        case COMBO23:
            playerImage = IMAGEMANAGER->findImage("플레이어공격2-3");
            if (!_left)
            {
                if (_index >= 6) setState(IDLE);
                playerImage->setFrameY(0);
                playerImage->setFrameX(_index);
                _index++;
            }
            else
            {
                if (_index >= 6) setState(IDLE);
                playerImage->setFrameY(1);
                playerImage->setFrameX(_index);
                _index++;
            }
            break;
        case SLIDE:
            playerImage = IMAGEMANAGER->findImage("플레이어슬라이딩");
            if (!_left)
            {
                _index = 0;
                playerImage->setFrameY(0);
                playerImage->setFrameX(_index);
            }
            else
            {
                _index = 0;
                playerImage->setFrameY(1);
                playerImage->setFrameX(_index);
            }
            break;
        case TACKLE:
            playerImage = IMAGEMANAGER->findImage("플레이어태클");
            if (!_left)
            {
                _index = 0;
                playerImage->setFrameY(0);
                playerImage->setFrameX(_index);
            }
            else
            {
                _index = 0;
                playerImage->setFrameY(1);
                playerImage->setFrameX(_index);
            }
            break;
        case JUMPATTACK:
            playerImage = IMAGEMANAGER->findImage("플레이어점프공격");
            if (!_left)
            {
                if (_index >= 6) setState(JUMP);
                playerImage->setFrameY(0);
                playerImage->setFrameX(_index);
                _index++;
            }
            else
            {
                if (_index >= 6) setState(JUMP);
                playerImage->setFrameY(1);
                playerImage->setFrameX(_index);
                _index++;
            }
            break;
		case GRAB:
			playerImage = IMAGEMANAGER->findImage("플레이어잡기");
			if (!_left)
			{
				if (_index >= 1) _index = 0;
				playerImage->setFrameY(0);
				playerImage->setFrameX(_index);
				_index++;
			}
			else
			{
				if (_index >= 1) _index = 0;
				playerImage->setFrameY(1);
				playerImage->setFrameX(_index);
				_index++;
			}
			break;
		case GRABSWING:
			playerImage = IMAGEMANAGER->findImage("플레이어잡기공격");
			if (!_left)
			{
				if (_index >= 10) setState(IDLE);
				playerImage->setFrameY(0);
				playerImage->setFrameX(_index);
				_index++;
			}
			else
			{
				if (_index >= 10) setState(IDLE);
				playerImage->setFrameY(1);
				playerImage->setFrameX(_index);
				_index++;
			}
			break;
        case WINDMILL:
            playerImage = IMAGEMANAGER->findImage("윈드밀");
            if (!_left)
            {
                if (_index >= 6) setState(IDLE);
                playerImage->setFrameY(0);
                playerImage->setFrameX(_index);
                _index++;
            }
            else
            {
                if (_index >= 6) setState(IDLE);
                playerImage->setFrameY(1);
                playerImage->setFrameX(_index);
                _index++;
            }
            break;
		case DEAD:
			playerImage = FINDIMG("플레이어죽음");
			if (!_left)
			{
				_index++;
				if (_index > 4) _index = 4;
			}
			else
			{
				_index--;
				if (_index < 0) _index=0;
			}
			break;
		}
		_count = 0;
	}
	
}



// 상태에 따라 이미지 위치를 보정해주고 렌더해주는 함수입니다
void player::stateRender() 
{

	//이미지 중점용변수입니다

	float imageCenterX = (((_flyRc.left + _flyRc.right) / 2) - (playerImage->getFrameWidth() / 2));
	float imageCenterY = (((_flyRc.bottom + _flyRc.top) / 2) - (playerImage->getFrameHeight() / 2));


	switch (_enumState)
	{
	case DEAD:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50); // 상태에 따라 그림자렉트를 만들게 해줬고, 각각의 상태에서 참조하는 좌표와 크기를 다르게 해줬습니다.
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX - 28, imageCenterY - 16, _index, 0); 
		else playerImage->frameRender(getMemDC(), imageCenterX + 28, imageCenterY - 16, _index, 1); 
		break;
	case IDLE:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX - 28, imageCenterY - 16);
		else playerImage->frameRender(getMemDC(), imageCenterX + 28, imageCenterY - 16);
		break;
	case CIDLEANIMATION:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX, imageCenterY - 16);
		else playerImage->frameRender(getMemDC(), imageCenterX, imageCenterY - 16);
		break;
	case JUMP:
		_shadowWidth = 200 - ((_groundRc.bottom - _flyRc.bottom) / 2); // 점프 및 점프공격 상태일 땐 점프하는 위치만큼 그림자 렉트를 줄여서 만들게 했습니다.
		if (_shadowWidth < 0) _shadowWidth = 0;
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, _shadowWidth, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX + 23, imageCenterY - 18);
		else playerImage->frameRender(getMemDC(), imageCenterX - 23, imageCenterY - 18);
		break;
	case WALK:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 125, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX - 21, imageCenterY - 18);
		else playerImage->frameRender(getMemDC(), imageCenterX + 21, imageCenterY - 18);
		break;
	case RUN:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 150, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX, imageCenterY - 16);
		else playerImage->frameRender(getMemDC(), imageCenterX, imageCenterY - 16);
		break;
    case HIT:
        _shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
        if (!_left) playerImage->frameRender(getMemDC(), imageCenterX - 15, imageCenterY - 15);
        else playerImage->frameRender(getMemDC(), imageCenterX + 15, imageCenterY - 15);
        break;
	case COMBO1:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 150, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX + 65, imageCenterY);
		else playerImage->frameRender(getMemDC(), imageCenterX - 65, imageCenterY);
		break;
	case COMBO11:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 150, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX + 15, imageCenterY - 10);
		else playerImage->frameRender(getMemDC(), imageCenterX - 15, imageCenterY - 10);
		break;
	case COMBO12:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX + 55, imageCenterY - 52);
		else playerImage->frameRender(getMemDC(), imageCenterX - 55, imageCenterY - 52);
		break;
	case COMBO13:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX + 70, imageCenterY - 30);
		else playerImage->frameRender(getMemDC(), imageCenterX - 70, imageCenterY - 30);
		break;
    case COMBO21:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX + 35, imageCenterY - 30);
		else playerImage->frameRender(getMemDC(), imageCenterX - 35, imageCenterY - 30);
        break;
    case COMBO22:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX - 20, imageCenterY - 10);
		else playerImage->frameRender(getMemDC(), imageCenterX + 20, imageCenterY - 10);
        break;
    case COMBO23:
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX + 75, imageCenterY - 5);
		else playerImage->frameRender(getMemDC(), imageCenterX - 75, imageCenterY - 5);
        break;
    case SLIDE:
		_shadow = RectMakeCenter(_flyX, _flyRc.bottom, 200, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX - 40, imageCenterY + 15);
		else playerImage->frameRender(getMemDC(), imageCenterX + 40, imageCenterY + 15);
        break;
    case TACKLE:
		_shadow = RectMakeCenter(_flyX, _flyRc.bottom, 150, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX, imageCenterY - 10);
		else playerImage->frameRender(getMemDC(), imageCenterX, imageCenterY - 10);
        break;
    case JUMPATTACK:
		_shadowWidth = 200 - ((_groundRc.bottom - _flyRc.bottom) / 2);
		if (_shadowWidth < 0) _shadowWidth = 0;
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, _shadowWidth, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX + 60, imageCenterY - 10);
		else playerImage->frameRender(getMemDC(), imageCenterX - 60, imageCenterY - 10);
        break;
	case GRAB:
        _shadow = RectMakeCenter(_groundX, _groundRc.bottom, 150, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX + 23, imageCenterY - 15);
		else playerImage->frameRender(getMemDC(), imageCenterX - 23, imageCenterY - 15);
		break;
	case GRABSWING:
        _shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200, 50);
		if (!_left) playerImage->frameRender(getMemDC(), imageCenterX + 60, imageCenterY - 25);
		else playerImage->frameRender(getMemDC(), imageCenterX - 60, imageCenterY - 25);
		break;
    case WINDMILL:
        _shadow = RectMakeCenter(_groundX, _groundRc.bottom, 125, 50);
        if (!_left) playerImage->frameRender(getMemDC(), imageCenterX, imageCenterY - 35);
        else playerImage->frameRender(getMemDC(), imageCenterX, imageCenterY - 35);
        break;

	}
}
