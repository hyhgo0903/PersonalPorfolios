#include "stdafx.h"
#include "diablo.h"

diablo::diablo()
{
}

diablo::~diablo()
{
}
/*
디아블로
 - 일정 시간마다 해골들을 소환한다
 - 해골들이 죽을때마다 디아블로 자신 주위에 근원거리 공격을 한다
*/
HRESULT diablo::init(BELONG belong, float x, float y)
{
	_belong = ENEMY;
	_ID = 6;
	_x = x; _y = y;
	_speed = 0.9f;
	_maxDelay = 120; // 대충 1초에 한대 치게끔
	_damage = 0;
	_maxHP = 1000;
	_attackIndex = 5; // 2번 인덱스가 될때 공격판정
	_width = 80;
	_height = 80; // 일단은 대충 설정해놓은거임(이미지크기) 
	_count = 0;
	_used = false;

	//_isAttack = false;
	//_isAttackCount = 0;
	commonInit(); // 앞에변수 참조해서 만드는 변수도 있으므로 뒤에다 만들어야함

	return S_OK;
}

void diablo::release()
{
}

void diablo::update()
{
	commonUpdate();
	_summonRc = RectMakeCenter(_x + 40, _y + 90, 180, 180);
	_rangeRc = RectMakeCenter(_x, _y, _width + 600, _height + 600);
	_focusRc = RectMakeCenter(_x, _y, _width + 600, _height + 600);
	// 이게 감지렉트인데 사거리렉트보다 작으면 안되겠지?
}

void diablo::render()
{
	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 54, _rc.top - 41, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 54, _rc.top - 41, _frameDirection, 5);
		break;
	case ATTACK:
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 73, _rc.top - 77, _frameDirection, _frame);
		break;
	case DEAD: // 프레임인덱스 다르게 도니까 주의
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 54, _rc.top - 84,  _frame , 0);
		break;
	}
}

void diablo::setState(STATE state)
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
			_image = FINDIMG("디아블로 걷기");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("디아블로 걷기");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			_image = FINDIMG("디아블로 소환");
			_maxFrame = _image->getMaxFrameY();
			PLAYSND("디아블로공격");
			break;
		case DEAD:
			PLAYSND("디아블로사망");
			_damage = 0; // 어차피 안쓸테니 죽었을때 카운트로 재활용한다(..)
			_image = FINDIMG("디아블로 죽음");
			_maxFrame = _image->getMaxFrameX();
			break; // 얘는 x임 가로로 재생하기떄문
		}
	}
}

void diablo::reRender()
{
	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->alphaFrameRender(getMemDC(), _rc.left - 54, _rc.top - 41, _frameDirection, _frame,150);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->alphaFrameRender(getMemDC(), _rc.left - 54, _rc.top - 41, _frameDirection, 5,150);
		break;
	case ATTACK:
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->alphaFrameRender(getMemDC(), _rc.left - 73, _rc.top - 77, _frameDirection, _frame,150);
		break;
	}
}