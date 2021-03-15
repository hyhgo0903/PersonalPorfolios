#include "stdafx.h"
#include "bishop.h"

HRESULT bishop::init(BELONG belong, float x, float y)
{
	_belong = belong;
	_ID = 5;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 240; // 대충 4초에 한번 스킬시전
	_damage = 0;
	_maxHP = 40;
	_attackIndex = 2; // 2번 인덱스가 될때 스킬판정
	_width = 12;
	_height = 20; // 일단은 대충 설정해놓은거임(이미지크기)
	commonInit(); // 앞에변수 참조해서 만드는 변수도 있으므로 뒤에다 만들어야함
	if (_belong == PLAYER) PLAYSND("비숍생성");
	return S_OK;
}

void bishop::release()
{
}

void bishop::update()
{
	commonUpdate();
	_rangeRc = RectMakeCenter(_x, _y, _width + 250, _height + 250);


}

void bishop::render()
{
	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameDirection, 0);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameDirection / 2, 0);
		break;
	case DEAD: // 프레임인덱스 다르게 도니까 주의
		_image->frameRender(getMemDC(), _rc.left - 24, _rc.top - 4, _frame / 2, 0);
		break;
	}
}

void bishop::reRender()
{
	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		_image->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _frameDirection, _frame,150);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		_image->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _frameDirection, 0, 150);
		break;
	case ATTACK:
		_image->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _frameDirection / 2, 0, 150);
		break;
	}
}

void bishop::setState(STATE state)
{
	if (_state == state) return; // 같은걸로 셋한거면 처리 안해줌
	_frame = 0;
	_frameCount = 0;
	_state = state;
	if (_belong == PLAYER)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("레드비숍이동");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("레드비숍대기");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			PLAYSND("비숍공격");
			_image = FINDIMG("레드비숍힐");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_damage = 0; // 어차피 안쓸테니 죽었을때 카운트로 재활용한다(..)
			_image = FINDIMG("레드비숍죽음");
			_maxFrame = _image->getMaxFrameX();
			break; // 얘는 x임 가로로 재생하기떄문
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("블루비숍이동");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("블루비숍대기");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			PLAYSND("비숍공격");
			_image = FINDIMG("블루비숍힐");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			PLAYSND("비숍죽음");
			_image = FINDIMG("블루비숍죽음");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}
}