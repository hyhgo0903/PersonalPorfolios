#include "stdafx.h"
#include "marine.h"

HRESULT marine::init(BELONG belong, float x, float y)
{
	_belong = belong;
	_ID = 2;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 60; // 대충 1초에 한대 치게끔
	_damage = 5;
	_maxHP = 40;
	_attackIndex = 2; // 2번 인덱스가 될때 공격판정
	_width = FINDIMG("마린기본파랑")->getFrameWidth();
	_height = FINDIMG("마린기본파랑")->getFrameHeight(); // 일단은 대충 설정해놓은거임(이미지크기)

	commonInit(); // 앞에변수 참조해서 만드는 변수도 있으므로 뒤에다 만들어야함
	return S_OK;
}

void marine::release()
{
	SAFE_DELETE(_image);
}

void marine::update()
{
	commonUpdate();
	_rangeRc = RectMakeCenter(_x, _y, _width + 200, _height + 200);
}

void marine::render()
{
	int left = _x - _image->getFrameWidth() / 2;
	int top = _y - _image->getFrameHeight() / 2;
	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		_image->frameRender(getMemDC(), left, top, _frame, _frameDirection);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		_image->frameRender(getMemDC(), left, top, 0, _frameDirection);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), left, top, _frame, _frameDirection);
		break;
	case DEAD: // 프레임인덱스 다르게 도니까 주의
		_image->frameRender(getMemDC(), left, top, _frame, 0);
		break;
	}
}

void marine::setState(STATE state)
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
			_image = FINDIMG("마린이동파랑");
			_maxFrame = _image->getMaxFrameX();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("마린공격파랑");
			_maxFrame = _image->getMaxFrameX();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			_image = FINDIMG("마린공격파랑");
			_maxFrame = _image->getMaxFrameX();
			break;
		case DEAD:
			_damage = 0; // 어차피 안쓸테니 죽었을때 카운트로 재활용한다(..)
			_image = FINDIMG("마린죽음파랑");
			_maxFrame = _image->getMaxFrameX();
			break; // 얘는 x임 가로로 재생하기떄문
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("마린이동빨강");
			_maxFrame = _image->getMaxFrameX();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("마린공격빨강");
			_maxFrame = _image->getMaxFrameX();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			_image = FINDIMG("마린공격빨강");
			_maxFrame = _image->getMaxFrameX();
			break;
		case DEAD:
			_damage = 0; // 어차피 안쓸테니 죽었을때 카운트로 재활용한다(..)
			_image = FINDIMG("마린죽음빨강");
			_maxFrame = _image->getMaxFrameX();
			break; // 얘는 x임 가로로 재생하기떄문
		}
	}

}
