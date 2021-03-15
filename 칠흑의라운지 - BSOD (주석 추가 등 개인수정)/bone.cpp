#include "stdafx.h"
#include "bone.h"

bone::bone()
{
}

bone::~bone()
{
}

HRESULT bone::init(BELONG belong, float x, float y)
{
	_belong = ENEMY;
	_ID = 7;
	_x = x; _y = y;
	_speed = 4.0f;
	_maxDelay = 120; // 대충 1초에 한대 치게끔
	_damage = 20;
	_maxHP = 30;
	_attackIndex = 2; // 2번 인덱스가 될때 공격판정
	_width = 21;
	_height = 22; // 일단은 대충 설정해놓은거임(이미지크기) 
	_count = 0;
	_used = false;

	commonInit(); // 앞에변수 참조해서 만드는 변수도 있으므로 뒤에다 만들어야함

	return S_OK;
}

void bone::release()
{
}

void bone::update()
{
}

void bone::render()
{
	switch (_state)
	{
	case WALK:
		_image->frameRender(getMemDC(), _rc.left - 5, _rc.top - 5, _frame, _frameDirection);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		_image->frameRender(getMemDC(), _rc.left - 7, _rc.top - 10, 0, _frameDirection);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left - 7, _rc.top - 10, _frame, _frameDirection);
		break;
	case DEAD: // 프레임인덱스 다르게 도니까 주의
		_image->frameRender(getMemDC(), _rc.left - 18, _rc.top - 8, _frame, 0);
		break;
	}
}

void bone::reRender()
{
}

void bone::setState(STATE state)
{
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("해골병사 서기");
			_maxFrame = _image->getMaxFrameX();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("해골병사 걷기");
			_maxFrame = _image->getMaxFrameX();
			break;
		case ATTACK:
			_image = FINDIMG("해골병사 공격");
			_maxFrame = _image->getMaxFrameX();
			break;
		case DEAD:
			_damage = 0; // 어차피 안쓸테니 죽었을때 카운트로 재활용한다(..)
			_image = FINDIMG("해골병사 종료");
			_maxFrame = _image->getMaxFrameX();
			break; // 얘는 x임 가로로 재생하기떄문
		}
	}
}
