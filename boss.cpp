#include "stdafx.h"
#include "boss.h"

boss::boss()
{
}

boss::~boss()
{
}

void boss::bossState()
{
	//HIT상태에서만 hit카운트가 더해진다
	if (_state == E_HIT) _hitCount++;
	//GRAB상태에서만 grab카운트가 더해진다
	if (_state == E_GRAB) _grabCount++;

	//공격범위 안에 플레이어가 있는지 체크함, 플레이어와 에너미의 간격이 100미만이면 true
	if (getDistance(_x, _y, _pX, _pY) < 100) _atkArea = true;
	//간격이 100이상이면 false
	if (getDistance(_x, _y, _pX, _pY) >= 100) _atkArea = false;


	if (_phaseCount > 400) // 페이즈 바꿈
	{
		_phase = 1 + rand() % 2;
		_destX = _pX;	_destY = _pY; // 목적지설정
		_jumping = true;
		_phaseCount = _rideCount = 0; _index = 0;
		_state = E_WALK;
		if (_destX > _x) _left = false;
		else _left = true;
		return;
	}

	//상태마다 기능을 정의해
	switch (_state)
	{
	case E_SHAKE:
		if (_index > 2)
		{
			if (_shakeCount > 3)
			{
				_state = E_WALK;
				_index = 3;
				break;
			}
			_index = 0;
			++_shakeCount;
		}
		break;
	case E_IDLE:
		//프레임 이미지의 최대 렌더값을 초과하지 않도록 설정해줌
		if (_index > 0) _index = 0;

		//플레이어와 에너미의 거리가 100이상일때
		if (getDistance(_x, _y, _pX, _pY) >= 100)
		{
			//플레이어가 에너미의 오른쪽에 있다면
			if (_x > _pX)
			{
				//에너미는 왼쪽을 보고있다고 설정해주고 WALK상태로 변경 후 
				//애니메이션을 처음부터 처리하기위해 인덱스를 0으로 초기화
				_left = true;
				_state = E_WALK;
				_index = 0;
			}
			else
			{
				//엘스로 오른쪽도 설정
				_left = false;
				_state = E_WALK;
				_index = 0;
			}
		}
		break;

	case E_WALK:
		//프레임 이미지 최대 렌더값을 초과하지않도록 초기화해줌
		if (_index > 3) _index = 0;
		//플레이어와 에너미의 거리가 200이하라면 ATK상태로 변경 후
		//이미지를 처음부터 렌더하기위해 인덱스 초기화
		if (getDistance(_x, _y, _pX, _pY) <= 200)
		{
			_attackCount++;
			if (_attackCount > 45)
			{
				_state = E_ATK;
				_index = 0;
				_attackCount = 0;
			}
		}
		//플레이어와 에너미의 거리가 450이상이라면 WALK2상태로 변경 후
		//이미지를 처음부터 렌더하기위해 인덱스 초기화
		if (getDistance(_x, _y, _pX, _pY) >= 450)
		{
			_state = E_WALK2;
			_index = 0;
		}
		//플레이어와 에너미의 거리가 450미만이고
		if (getDistance(_x, _y, _pX, _pY) < 450)
		{
			//플레이어가 에너미의 오른쪽에있다면
			if (_x > _pX)
			{
				_left = true; //에너미는 왼쪽을바라보고
				if (!_atkArea) //플레이어의 아래좌표까지 따라간다
				{
					_x += 2.7f * cosf(getAngle(_x, _y, _pX + 90, _pY));
					_y -= 2.7f * sinf(getAngle(_x, _y, _pX + 90, _pY));
				}
			}
			else
			{
				_left = false; //에너미는 오른쪽을 바라보고
				if (!_atkArea) //플레이어의 아래좌표까지 따라간다
				{
					_x += 2.7f * cosf(getAngle(_x, _y, _pX - 90, _pY));
					_y -= 2.7f * sinf(getAngle(_x, _y, _pX - 90, _pY));
				}
			}
		}
		break;

	case E_WALK2:
		//프레임 이미지 최대 렌더값을 초과하지않도록 인덱스 초기화
		if (_index > 2) _index = 0;
		//플레이어와 에너미의 거리가 450미만이라면 WALK상태로 변경 후
		//프레임 이미지 정상 렌더를 위해 인덱스 초기화
		if (getDistance(_x, _y, _pX, _pY) < 450)
		{
			_state = E_WALK;
			_index = 0;
		}
		//플레이어가 에너미의
		if (_x > _pX) //오른쪽에 있다면
		{
			_left = true; //에너미는 왼쪽을 바라보고
			if (!_atkArea) //플레이어의 아래좌표까지 이동한다
			{
				_x += 4.f * cosf(getAngle(_x, _y, _pX + 100, _pY));
				_y -= 4.f * sinf(getAngle(_x, _y, _pX + 100, _pY));
			}
		}
		else //왼쪽에 있다면
		{
			_left = false; //에너미는 오른쪽을 바라보고
			if (!_atkArea) //플레이어의 아래좌표까지 이동한다.
			{
				_x += 2.7f * cosf(getAngle(_x, _y, _pX - 100, _pY));
				_y -= 2.7f * sinf(getAngle(_x, _y, _pX - 100, _pY));
			}
		}
		break;

	case E_ATK:
		if (_index > 2)
		{
			_state = E_WALK;
			_index = 0;
		}
		break;

	case E_DEAD:
		if (_index > 3)
		{
			_index = 3;
		}
		break;

	case E_HIT:
		_index = 0;

		//피격모션 유지시간 (30 = 0.5초)
		//0.5초가 지나면 IDLE상태로 변경됨
		if (_hitCount > 30)
		{
			_state = E_IDLE;
			_hitCount = 0;
		}
		if (_left) ++_x;
		else --_x;
		break;

	case E_GRAB:
		_index = 0;

		//그랩모션 유지시간 (90 = 1.5초)
		//1.5초가 지나면 IDLE상태로 변경됨
		if (_grabCount > 90)
		{
			_state = E_IDLE;
			_grabCount = 0;
		}
		break;

	case E_FLYING:
		//몬스터 렉트의 라이트가 카메라 화면 오른쪽 밖으로 나가려고한다면 체공상태를 풀고 인덱스를 1로 바꾼다
		if (_rc.right > CAMX + WINSIZEX && _flying && _left)
		{
			_flying = false;
			_index = 1;
			//x좌표 위치를 보정해주는 이유는 안해주면 애가 가끔 낑김
			_x -= 5;
		}
		//몬스터 렉트의 레프트가 카메라 화면 왼쪽 밖으로 나가려고한다면 체공상태를 풀고 인덱스를 1로 바꾼다
		if (_rc.left < CAMX && _flying && !_left)
		{
			_flying = false;
			_index = 1;
			//x좌표 위치를 보정해주는 이유는 안해주면 애가 가끔 낑김
			_x += 5;
		}
		//인덱스가 정상적으로 초기화되었고 지상에있는 상태라면 플라잉상태로 변경시켜줌
		if (!_flying && _index == 0) _flying = true;
		//플라잉 상태에서만 좌표를 이동시킨다
		if (_flying && _left) _x += 15.5f;
		if (_flying && !_left) _x -= 15.5f;
		//이미지가 정상적으로 마지막까지 렌더된다면 IDLE상태로 변경시키고 인덱스를 초기화
		if (_index > 3)
		{
			_state = E_IDLE;
			_index = 0;
		}
		break;
	}
}

void boss::phase1() // 공격렉트가 전신에 생겨서 치고다님
{
	if (getDistance(_x, _y, _destX, _destY) > 30)
	{
		_x += 10.f * cosf(getAngle(_x, _y, _destX, _destY));
		_y -= 10.f * sinf(getAngle(_x, _y, _destX, _destY));
	}
	else
	{
		++_rideCount;
		if (_rideCount > 120)
		{
			_rideCount = 0;
			_destX = _pX;
			_destY = _pY;
			if (_destX > _x) _left = false;
			else _left = true;
		}
	}
	if (_phaseCount > 600)
	{
		_phaseCount = 0; _phase = 0; _index = _rideCount = 0;
		_state = E_IDLE;
	}


	if (_index > 2)
	{
		_index = 0;
	}
}

void boss::phase2()
{ // 이때는 그림자 렌더도 _destY에다 만들어야할듯
	if (_jumping)
	{ // 점프중
		_y -= 20;
		if (_destY - _y > WINSIZEY)
		{
			_jumping = false;
			_x = _destX;
		}
	}
	else if (_destY > _y)
	{ // 착지
		_y += 20;
	}
	else if (_destY <= _rc.bottom && !_jumping)
	{ // 착지후 쉐이킹
		_phaseCount = 0; _phase = 0; _index = _shakeCount = 0;
		_state = E_SHAKE;
		return;
	}

	if (_index > 2)
	{
		_index = 0;
	}
}


HRESULT boss::init(float x, float y)
{
	_x = CAMX + x;	_y = CAMY + y;
	_currentHP = _maxHP = 500.f;
	_count = _index = _attackCount = _hitCount = _grabCount = _phaseCount = _rideCount = 0;
	_state = E_IDLE;
	_phase = 0;
	_flying = _atkArea = _left = false;
	   
	_destX = _destY = 0;

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{	//프레임 렌더가 되는 속도를 조절해줌
	_count++;
	if (_count % 10 == 0)
	{
		if (!_flying) _index++;
		_count = 0;
	}
	++_phaseCount;
	if (_phase == 0 ) bossState();
	else if (_phase == 1) phase1();
	else if (_phase == 2) phase2();

	_rc = RectMakeCenter(_x, _y, 200, 200);
}

void boss::render()
{
	Rectangle(getMemDC(), _rc);

	if (_phase == 0)
	{
		//볼 몬스터의 상태에 따라 렌더되는 이미지를 정해줌
		switch (_state)
		{
		case E_SHAKE:
			if (_left) FINDIMG("boss_shakes")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 1);
			else FINDIMG("boss_shakes")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 0);		break;
		case E_IDLE:
			if (_left) FINDIMG("boss_idle")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 1);
			else FINDIMG("boss_idle")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 0);		break;
		case E_WALK:
			if (_left) FINDIMG("boss_walk")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 1);
			else FINDIMG("boss_walk")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 0);		break;
		case E_WALK2:
			if (_left) FINDIMG("boss_crawl")->frameRender(getMemDC(), _rc.left - 61, _rc.top, _index, 1);
			else FINDIMG("boss_crawl")->frameRender(getMemDC(), _rc.left - 74, _rc.top, _index, 0);		break;
		case E_ATK:
			if (_left) FINDIMG("boss_atk")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 1);
			else FINDIMG("boss_atk")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 0);		break;
		case E_DEAD:
			if (_left) FINDIMG("boss_dead")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 1);
			else FINDIMG("boss_dead")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 0);		break;
		case E_HIT:
			// _plAtkNum : 플레이어 공격상태 체크용 테스트 변수
			// 1 = 오른쪽에서 왼쪽으로 공격 , 2 = 왼쪽에서 오른쪽으로 공격
			if (_plAtkNum == 1)
			{
				if (_left) FINDIMG("boss_hit4")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 1);
				else FINDIMG("boss_hit4")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 0);
			}
			if (_plAtkNum == 2)
			{
				if (_left) FINDIMG("boss_hit2")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 1);
				else FINDIMG("boss_hit2")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 0);
			}
			break;
		case E_GRAB:
			if (_left) FINDIMG("boss_hit")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 1);
			else FINDIMG("boss_hit")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 0); break;
		case E_FLYING:
			if (_left) FINDIMG("enemy1_flying")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 1);
			else FINDIMG("enemy1_flying")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 0); break;
		}
	}
	else if (_phase == 1)
	{
		if (_left) FINDIMG("boss_car")->frameRender(getMemDC(), _rc.left-75, _rc.top-90, _index, 1);
		else FINDIMG("boss_car")->frameRender(getMemDC(), _rc.left-136, _rc.top-90, _index, 0);
	}
	else if (_phase == 2)
	{
		if (_left) FINDIMG("boss_crawl")->frameRender(getMemDC(), _rc.left-61, _rc.top, _index, 1);
		else FINDIMG("boss_crawl")->frameRender(getMemDC(), _rc.left-74, _rc.top, _index, 0);
	}

}
