#include "stdafx.h"
#include "player.h"
#include "STATE.h"
#include "Idle.h"
#include "Jump.h"
#include "walk.h"
#include "run.h"
#include "combo1.h"
#include "enemyManager.h"
// 왜 헤더가 아니냐면 상호참조(상속받고) 날수 있기 때문이라고 함
// 추가할떈 잊지말고 여기에다 추가

player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{
	_flyX = _groundX = 100.f;
	_flyY = _groundY = CAMY + 300.f;
	_directionChanged = _directionChangeCount = _dirMemory = _dirMemoryCount = 0;
	_flyRc = RectMakeCenter(_flyX, _flyY, 50, 50);
	_groundRc = RectMakeCenter(_groundX, _groundY, 20, 20);
	_currentHP = _maxHP = 100.f;
	_left = false;
	setState(IDLE);
	_attack = new attack;
	_attack->init(3, 50);
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
	_flyRc = RectMakeCenter(_flyX, _flyY, 50, 50);
	_groundRc = RectMakeCenter(_groundX, _groundY, 50, 50);	
	minusDirectionChanged();
	_attack->update(50);
}

void player::render()
{
	switch (_enumState)
	{
	case IDLE: sprintf_s(_str, "IDLE");		break;
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
	_attack->render();
}

void player::minusDirectionChanged()
{
	if (_directionChanged > 0) // 방향전환이 일어났다면
	{
		if (_directionChanged > 2) _directionChanged = 2; // 방향전환 2번 넘으면 2번으로 해주고
		++_directionChangeCount; // 카운트센다
		if (_directionChangeCount > 30) // 30(0.5초) 이상 지났다면
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
	Rectangle(getMemDC(), _groundRc);
	Rectangle(getMemDC(), _flyRc);
}

//상태설정

void player::setState(State state)
{
	if (_statePattern)_statePattern->ExitState();
	// 기존 상태의 exitState()함수를 호출
	_enumState = state;
	switch (state)
	{ // 스테이트를 바꾸고 그에맞게 상태객체를 만드는 모습이야
	case IDLE:	_statePattern = new Idle;	break;
	case JUMP:	_statePattern = new Jump;	break;
	case WALK:	_statePattern = new walk;	break;
	case RUN:	_statePattern = new run;	break;
	case COMBO1: _statePattern = new combo1; break;
	}
	_statePattern->LinkMemberAdress(this);
	// 참조할때마다 플레이그라운드에서 링크시켰던거 있잖아?
	// 여기선 바로 이게 그 역할을 하는거야
	// 예를들어 idle에서 _pl->setState(~~)를 하는데
	// _pl을 이 클래스(this)로 연결하도록 하는거야
	// (아니면 그냥 빈껍데기)
	_statePattern->EnterState();
}
