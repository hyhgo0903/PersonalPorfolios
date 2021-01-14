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
#include "cidleAnimation.h"
#include "windmill.h"
#include "grab.h"
#include "grabswing.h"
#include "enemyManager.h"
// 왜 헤더가 아니냐면 상호참조(상속받고) 날수 있기 때문이라고 함
// 추가할떈 잊지말고 여기에다 추가

HRESULT player::init()
{
	playerImage = IMAGEMANAGER->findImage("플레이어대기");
	_count = _index = 0;
	_flyX = _groundX = 100.f;
	_flyY = _groundY = CAMY + 300.f;
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
    _isHit = false;
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
	/*
	switch (_enumState)
	{
	case IDLE: IMAGEMANAGER->findImage("플레이어대기")->frameRender(getMemDC(), _flyRc.left, _flyRc.top);	break;
	case JUMP: sprintf_s(_str, "JUMP");		break;
	case WALK: sprintf_s(_str, "WALK");		break;
	case RUN: sprintf_s(_str, "RUN");		break;
	}
	TextOut(getMemDC(), 0, 60, _str, strlen(_str));
	if (_left > 0) sprintf_s(_str, "LEFT");
	else if (_left == 0) sprintf_s(_str, "RIGHT");
	TextOut(getMemDC(), 60, 60, _str, strlen(_str));
	if (_directionChanged >= 2)
	{ // 방향이 0.5초내 두번 바뀌었다 == 좌우(or우좌)입력을 한 상태임
		sprintf_s(_str, "이때 버튼을 누르면 특수기로 나가도록 설정");
		TextOut(getMemDC(), 0, 80, _str, strlen(_str));
	}
	*/ // 참고용
	_attack->render();
}

void player::minusDirectionChanged()
{
	if (_directionChanged > 0) // 방향전환이 일어났다면
	{
		if (_directionChanged >= 2) _directionChanged = 2; // 방향전환 2번 넘으면 2번으로 해주고
		++_directionChangeCount; // 카운트센다
		if (_directionChangeCount > 45) // 30(0.5초) 이상 지났다면
		{
			_directionChangeCount = 0; // 카운트 0으로 돌리고
			--_directionChanged; // 방향전환 줄여줌
		}
	} // 참고 : 방향전환 두 번 일어난 경우 특수키 사용조건으로 함

	if (_dirMemory > 0) // 뭔가 기억되어 있다면
	{
		++_dirMemoryCount;
		if (_dirMemoryCount > 30)
		{ // 30(0.5초)카운트내로 초기화 시켜줌
			_dirMemoryCount = 0;
			_dirMemory = 0;
		}
	}
}

void player::playerRender()
{
	HPEN pen = CreatePen(0, 2, RGB(30, 30, 30));
	HPEN oldpen = (HPEN)SelectObject(getMemDC(), pen);
	HBRUSH brush = CreateSolidBrush(RGB(30, 30, 30));
	HBRUSH oldbrush = (HBRUSH)SelectObject(getMemDC(), brush);
	Ellipse(getMemDC(), _shadow);
	SelectObject(getMemDC(), oldbrush);
	DeleteObject(brush);
	SelectObject(getMemDC(), oldpen);
	DeleteObject(pen);
	stateRender();
	if(KEYMANAGER->isToggleKey(VK_TAB))
	{ 
		Rectangle(getMemDC(), _groundRc);
		Rectangle(getMemDC(), _flyRc);
	}
}

//상태설정

void player::setState(State state)
{
	if (_statePattern)_statePattern->ExitState();
	// 기존 상태의 exitState()함수를 호출
	_enumState = state;
	switch (state)
	{ // 스테이트를 바꾸고 그에맞게 상태객체를 만드는 모습이야
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
	}
	_statePattern->LinkMemberAdress(this);
	// 참조할때마다 플레이그라운드에서 링크시켰던거 있잖아?
	// 여기선 바로 이게 그 역할을 하는거야
	// 예를들어 idle에서 _pl->setState(~~)를 하는데
	// _pl을 이 클래스(this)로 연결하도록 하는거야
	// (아니면 그냥 빈껍데기)
	_statePattern->EnterState();

}

//상태에 따라 이미지를 찾고 재생해주는 함수
void player::stateUpdate()
{
	_count++;
	if (_count % 5 == 0)
	{
		switch (_enumState)
		{
		case IDLE:
			playerImage = IMAGEMANAGER->findImage("플레이어대기");
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
			playerImage = IMAGEMANAGER->findImage("플레이어공격");
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
            playerImage = IMAGEMANAGER->findImage("플레이어슬라이딩"); // 슬라이딩과 태클은 일정 거리 이동하면 상태패턴쪽에서 대기상태로 바뀌게 만들었어용.
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
		}
		_count = 0;
	}
	
}



// 상태에 따라 이미지 위치를 보정해주고 렌더해주는 함수 
void player::stateRender() 
{

	//이미지 중점용

	float imageCenterX = (((_flyRc.left + _flyRc.right) / 2) - (playerImage->getFrameWidth() / 2));
	float imageCenterY = (((_flyRc.bottom + _flyRc.top) / 2) - (playerImage->getFrameHeight() / 2));


	switch (_enumState)
	{
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
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200 - ((_groundRc.bottom - _flyRc.bottom)/2), 50);
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
		_shadow = RectMakeCenter(_groundX, _groundRc.bottom, 200 - ((_groundRc.bottom - _flyRc.bottom) / 2), 50);
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
