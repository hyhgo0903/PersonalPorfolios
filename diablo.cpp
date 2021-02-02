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
	_speed = 2.0f;
	_maxDelay = 120; // 대충 1초에 한대 치게끔
	_damage = 20;
	_maxHP = 300;
	_attackIndex = 2; // 2번 인덱스가 될때 공격판정
	_width = 21;
	_height = 22; // 일단은 대충 설정해놓은거임(이미지크기) 
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
	_summonRc = RectMakeCenter(_x, _y, 300, 300);
	_rangeRc = RectMakeCenter(_x, _y, _width + 500, _height + 500);
}

void diablo::render()
{
	switch (_state)
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		Rectangle(getMemDC(), _summonRc);
		_image->frameRender(getMemDC(), _rc.left - 5, _rc.top - 5, _frame, _frameDirection);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		Rectangle(getMemDC(), _summonRc);
		_image->frameRender(getMemDC(), _rc.left - 7, _rc.top - 10, 0, _frameDirection);
		break;
	case ATTACK:
		Rectangle(getMemDC(), _summonRc);
		_image->frameRender(getMemDC(), _rc.left - 7, _rc.top - 10, _frame, _frameDirection);
		break;
	case DEAD: // 프레임인덱스 다르게 도니까 주의
		Rectangle(getMemDC(), _summonRc); 
		_image->frameRender(getMemDC(), _rc.left - 18, _rc.top - 8, _frame, 0);
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
			_image = FINDIMG("디아블로 서기");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("디아블로 걷기");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACK:
			_image = FINDIMG("디아블로 소환");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("디아블로 죽음");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}
}

void diablo::reRender()
{
}