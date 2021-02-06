#include "stdafx.h"
#include "zergling.h"

zergling::zergling()
{
}

zergling::~zergling()
{	
}

HRESULT zergling::init(BELONG belong, float x, float y)
{ // 뭐 놓치지 않게 이거 복붙해서 각각 바꿔놓는걸 추천
	_belong = belong;
	_ID = 1;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 60; // 대충 1초에 한대 치게끔
	_damage = 7;
	_maxHP = 35;
	_attackIndex = 2; // 2번 인덱스가 될때 공격판정
	_width = 20;
	_height = 20; // 일단은 대충 설정해놓은거임(이미지크기)
	_healCount = 60;
	commonInit(); // 앞에변수 참조해서 만드는 변수도 있으므로 뒤에다 만들어야함
	if (_belong == PLAYER)PLAYSND("저글링생성");
	return S_OK;
}

void zergling::release()
{
	SAFE_DELETE(_image);
}

void zergling::update()
{
	commonUpdate();
	_rangeRc = RectMakeCenter(_x, _y, _width + 6, _height + 6);


	// 이하는 저글링특성이니까 참고안해도 괜찮음
	if (_HP / _maxHP <= 0.5f)
	{ // 피가 50%이하면 공속2배 + 힐(최대 18만큼)
		--_healCount;
	}
	if (_healCount < 60 && _healCount > 0)
	{ // 피가 50%이하면 공속2배 + 1회한정힐(최대 12만큼)
		_maxDelay = 30;
		_HP += 0.2f;
		--_healCount;
		if (_maxHP < _HP) _HP = _maxHP;
	}
}

void zergling::render()
{
	if (_healCount < 60 && _healCount > 0 && _state != DEAD) FINDIMG("저글링힐")->frameRender(getMemDC(), _rc.left - 28, _rc.top - 15, _healCount / 6, 0);
	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		_image->frameRender(getMemDC(), _rc.left-9, _rc.top-9, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 9, _frameDirection, 0);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 9, _frameDirection, _frame);
		break;
	case DEAD: // 프레임인덱스 다르게 도니까 주의
		_image->frameRender(getMemDC(), _rc.left - 22, _rc.top - 24, _frame, 0);
		break;
	}
}

void zergling::reRender()
{
	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 9, _rc.top - 9, _frameDirection, _frame, 150);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		_image->alphaFrameRender(getMemDC(), _rc.left - 9, _rc.top - 9, _frameDirection, 0, 150);
		break;
	case ATTACK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 9, _rc.top - 9, _frameDirection, _frame, 150);
		break;
	}
}

void zergling::setState(STATE state)
{ // 이거에 준해서 만들어주세요
	if (_state == state) return; // 같은걸로 셋한거면 처리 안해줌
	_frame = 0;
	_frameCount = 0;
	_state = state;
	if (_belong == PLAYER)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("저글링이동블루");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("저글링공격블루");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			PLAYSND("저글링공격");
			_image = FINDIMG("저글링공격블루");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			PLAYSND("저글링사망");
			_image = FINDIMG("저글링죽음");
			_maxFrame = _image->getMaxFrameX();
			break; // 얘는 x임 가로로 재생하기떄문
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("저글링이동퍼플");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("저글링공격퍼플");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			PLAYSND("저글링공격");
			_image = FINDIMG("저글링공격퍼플");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			PLAYSND("저글링사망");
			_image = FINDIMG("저글링죽음");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}
	
}
