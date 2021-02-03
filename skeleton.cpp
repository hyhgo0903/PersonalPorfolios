#include "stdafx.h"
#include "skeleton.h"
#include "unit.h"
#include "stdafx.h"
#include "ghost.h"


skeleton::skeleton()
{
}


skeleton::~skeleton()
{
}

HRESULT skeleton::init(BELONG belong, float x, float y)
{ // 뭐 놓치지 않게 이거 복붙해서 각각 바꿔놓는걸 추천
	_belong = ENEMY;
	_ID = 7;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 120; // 대충 1초에 한대 치게끔
	_damage = 6;
	_maxHP = 10;
	_attackIndex = 2; // 2번 인덱스가 될때 공격판정
	_width = 21;
	_height = 22; // 일단은 대충 설정해놓은거임(이미지크기)
	_count = 0;
	_used = false;

	commonInit(); // 앞에변수 참조해서 만드는 변수도 있으므로 뒤에다 만들어야함

	return S_OK;
}

void skeleton::release()
{
	SAFE_DELETE(_image);
}

void skeleton::update()
{
	commonUpdate();
	_focusRc = RectMakeCenter(_x, _y, _width + 30, _height + 30);
	_rangeRc = RectMakeCenter(_x, _y, _width + 20, _height + 20);
}

void skeleton::render()
{
	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, 0);
		break;
	case ATTACK:
		Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, _frame);
		break;
	case DEAD: // 프레임인덱스 다르게 도니까 주의
		Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 18, _rc.top - 8, _frame, 0);
		break;
	}

	// if (KEYMANAGER->isToggleKey(VK_F1)) Rectangle(getMemDC(), _rc);
}

void skeleton::reRender()
{
	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, _frame, 150);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		_image->alphaFrameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, 0, 150);
		break;
	case ATTACK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, _frame, 150);
		break;
	}
}

void skeleton::setState(STATE state)
{ // 이거에 준해서 만들어주세요
	if (_state == state) return; // 같은걸로 셋한거면 처리 안해줌
	_frame = 0;
	_frameCount = 0;
	_state = state;
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("해골병사 서기");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("해골병사 공격");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			_image = FINDIMG("해골병사 공격");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("해골병사 죽음");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}

}