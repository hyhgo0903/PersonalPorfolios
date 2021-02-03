#include "stdafx.h"
#include "skeleton.h"

skeleton::skeleton()
{
}

skeleton::~skeleton()
{
}

HRESULT skeleton::init(BELONG belong, float x, float y)
{
	_belong = ENEMY;
	_ID = 7;
	_x = x; _y = y;
	_speed = 2.0f;
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

void skeleton::release()
{
}

void skeleton::update()
{
	commonUpdate();
	_rangeRc = RectMakeCenter(_x + 40, _y + 90, _width + 20, _height + 20);
}

void skeleton::render()
{

	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		//Rectangle(getMemDC(), _summonRc);
		_image->frameRender(getMemDC(), _rc.left - 5, _rc.top - 5, _frameDirection, _frame);
		break;
	case ATTACK:
		//Rectangle(getMemDC(), _summonRc);
		_image->frameRender(getMemDC(), _rc.left - 7, _rc.top - 10, _frameDirection, _frame);
		break;
	case DEAD: // 프레임인덱스 다르게 도니까 주의
		//Rectangle(getMemDC(), _summonRc); 
		_image->frameRender(getMemDC(), _rc.left - 18, _rc.top - 8, _frame, 0);
		break;
	}

}

void skeleton::reRender()
{
}

void skeleton::setState(STATE state)
{
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
			_image = FINDIMG("해골병사 죽음");
			_maxFrame = _image->getMaxFrameX();
			break; // 얘는 x임 가로로 재생하기떄문
		}
	}
}
