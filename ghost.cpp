#include "stdafx.h"
#include "ghost.h"


ghost::ghost()
{
}


ghost::~ghost()
{
}

HRESULT ghost::init(BELONG belong, float x, float y)
{ // 뭐 놓치지 않게 이거 복붙해서 각각 바꿔놓는걸 추천
	_belong = belong;
	_ID = 8;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 120; // 대충 1초에 한대 치게끔
	_damage = 18;
	_maxHP = 45;
	_attackIndex = 2; // 2번 인덱스가 될때 공격판정
	_width = 21;
	_height = 22; // 일단은 대충 설정해놓은거임(이미지크기)
	_count = 0;
	_used = false;

	commonInit(); // 앞에변수 참조해서 만드는 변수도 있으므로 뒤에다 만들어야함
	if (_belong == PLAYER)PLAYSND("고스트생성");
	return S_OK;
}

void ghost::release()
{
	SAFE_DELETE(_image);
}

void ghost::update()
{
	commonUpdate();
	_focusRc = RectMakeCenter(_x, _y, _width + 500, _height + 500);
	_rangeRc = RectMakeCenter(_x, _y, _width + 500, _height + 500);
	// 사거리 맞춰서 여기서 설정

	//현재 체력이 33%이하가 되면 체력의 절반을 회복한다
	if (_HP < _maxHP / 3 && !_used)
	{
		_HP += _maxHP / 2;
		_used = true;
	}
}

void ghost::render()
{
	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, 0);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, _frame);
		break;
	case DEAD: // 프레임인덱스 다르게 도니까 주의
		_image->frameRender(getMemDC(), _rc.left - 18, _rc.top - 8, _frame, 0);
		break;
	}

	if (KEYMANAGER->isToggleKey(VK_F1)) Rectangle(getMemDC(), _rc);
}

void ghost::reRender()
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

void ghost::setState(STATE state)
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
			_image = FINDIMG("ghost_move_blue");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("ghost_atk_blue");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			PLAYSND("고스트공격");
			_image = FINDIMG("ghost_atk_blue");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			PLAYSND("고스트사망");
			_image = FINDIMG("ghost_dead_blue");
			_maxFrame = _image->getMaxFrameX();
			break; // 얘는 x임 가로로 재생하기떄문
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("ghost_move_red");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("ghost_atk_red");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			PLAYSND("고스트공격");
			_image = FINDIMG("ghost_atk_red");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			PLAYSND("고스트사망");
			_image = FINDIMG("ghost_dead_red");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}

}
