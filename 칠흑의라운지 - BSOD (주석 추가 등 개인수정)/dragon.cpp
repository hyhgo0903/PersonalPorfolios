#include "stdafx.h"
#include "dragon.h"

HRESULT dragon::init(BELONG belong, float x, float y)
{ // 뭐 놓치지 않게 이거 복붙해서 각각 바꿔놓는걸 추천
	_belong = belong;
	_ID = 9;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 60; // 대충 1초에 한대 치게끔
	_damage = 5;
	_maxHP = 45;
	_attackIndex = 2; // 2번 인덱스가 될때 공격판정
	_width = 20;
	_height = 20; // 일단은 대충 설정해놓은거임(이미지크기)

	commonInit(); // 앞에변수 참조해서 만드는 변수도 있으므로 뒤에다 만들어야함
	if (_belong == PLAYER)PLAYSND("드래곤생성");
	return S_OK;
}

void dragon::release()
{
	SAFE_DELETE(_image);
}

void dragon::update()
{
	commonUpdate();
	_rangeRc = RectMakeCenter(_x, _y, _width + 200, _height + 200);

}

void dragon::render()
{
	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		_image->frameRender(getMemDC(), _rc.left - 10, _rc.top - 10, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		_image->frameRender(getMemDC(), _rc.left - 10, _rc.top - 10, _frameDirection, 0);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left - 10, _rc.top - 10, _frameDirection, _frame);
		break;
	case DEAD: // 프레임인덱스 다르게 도니까 주의
		_image->frameRender(getMemDC(), _rc.left - 10, _rc.top - 10, _frame, 0);
		break;
	}
}

void dragon::reRender()
{
	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 10, _rc.top - 10, _frameDirection, _frame, 150);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		_image->alphaFrameRender(getMemDC(), _rc.left - 10, _rc.top - 10, _frameDirection, 0, 150);
		break;
	case ATTACK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 10, _rc.top - 10, _frameDirection, _frame, 150);
		break;
	}
}

void dragon::setState(STATE state)
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
			_image = FINDIMG("블루드래곤이동");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("블루드래곤대기");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			_image = FINDIMG("블루드래곤공격");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("블루드래곤죽음");
			_maxFrame = _image->getMaxFrameX();
			break; // 얘는 x임 가로로 재생하기떄문
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("레드드래곤이동");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("레드드래곤대기");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			_image = FINDIMG("레드드래곤공격");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("레드드래곤죽음");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}

}
