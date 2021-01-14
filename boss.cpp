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
	//DEAD상태에서만 dead카운트가 더해진다
	if (_state == E_DEAD) _deadCount++;

	//공격범위 안에 플레이어가 있는지 체크함, 플레이어와 에너미의 간격이 100미만이면 true
	if (getDistance(_x, _y, _pX, _pY) < 100) _atkArea = true;
	//간격이 100이상이면 false
	if (getDistance(_x, _y, _pX, _pY) >= 100) _atkArea = false;


	if (_phaseCount > 300 && _state != E_GRAB && _state != E_DEAD && _state != E_HIT
		&& _state != E_FLYING && _currentHP > 0) // 페이즈 바꿈
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
			if (_shakeCount > 2)
			{
				setState(E_WALK);
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
				setState(E_WALK);
			}
			else
			{
				//엘스로 오른쪽도 설정
				_left = false;
				setState(E_WALK);
			}
		}
		else
		{
			_attackCount++;
			if (_attackCount > 45)
			{
				setState(E_ATK);
				_attackCount = 0;
			}
		}

		break;

	case E_WALK:
		//프레임 이미지 최대 렌더값을 초과하지않도록 초기화해줌
		if (_index > 3) _index = 0;

		if (_destX > _x) _left = false;
		else _left = true;
		//플레이어와 에너미의 거리가 200이하라면 ATK상태로 변경 후
		//이미지를 처음부터 렌더하기위해 인덱스 초기화
		if (getDistance(_x, _y, _pX, _pY) <= 200)
		{
			_attackCount++;
			if (_attackCount > 45)
			{
				setState(E_ATK);
				_attackCount = 0;
			}
		}
		//플레이어와 에너미의 거리가 450이상이라면 WALK2상태로 변경 후
		//이미지를 처음부터 렌더하기위해 인덱스 초기화
		if (getDistance(_x, _y, _pX, _pY) >= 450)
		{
			setState(E_WALK2);
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
					_x += 4.f * cosf(getAngle(_x, _y, _pX + 90, _pY));
					_y -= 4.f * sinf(getAngle(_x, _y, _pX + 90, _pY));
				}
			}
			else
			{
				_left = false; //에너미는 오른쪽을 바라보고
				if (!_atkArea) //플레이어의 아래좌표까지 따라간다
				{
					_x += 4.f * cosf(getAngle(_x, _y, _pX - 90, _pY));
					_y -= 4.f * sinf(getAngle(_x, _y, _pX - 90, _pY));
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
			setState(E_WALK);
		}
		//플레이어가 에너미의
		if (_x > _pX) //오른쪽에 있다면
		{
			_left = true; //에너미는 왼쪽을 바라보고
			if (!_atkArea) //플레이어의 아래좌표까지 이동한다
			{
				_x += 8.f * cosf(getAngle(_x, _y, _pX + 100, _pY));
				_y -= 8.f * sinf(getAngle(_x, _y, _pX + 100, _pY));
			}
		}
		else //왼쪽에 있다면
		{
			_left = false; //에너미는 오른쪽을 바라보고
			if (!_atkArea) //플레이어의 아래좌표까지 이동한다.
			{
				_x += 8.f * cosf(getAngle(_x, _y, _pX - 100, _pY));
				_y -= 8.f * sinf(getAngle(_x, _y, _pX - 100, _pY));
			}
		}
		break;

	case E_ATK:
		if (_index == 2)
		{
			if (_left)
			{
				_attackRc = RectMakeCenter(_x - 110, _y - 45, 120, 80);
			}
			else
			{
				_attackRc = RectMakeCenter(_x + 110, _y - 45, 120, 80);
			}
		}
		if (_index > 2)
		{
			_attackRc = RectMakeCenter(0, 0, 0, 0);
			setState(E_IDLE);
		}
		break;

	case E_DEAD:
		if (_index >= 3)
		{
			_index = 3;
		}
		else
		{
			if (_left) _x += 2;
			else _x -= 2;
		}
		break;

	case E_HIT:
		_index = 0;
		if (_left) _x += 0.8f;
		else _x -= 0.8f;

		if (_currentHP <= 0)
		{
			setState(E_DEAD);
		}

		//피격모션 유지시간 (30 = 0.5초)
		//0.5초가 지나면 IDLE상태로 변경됨
		if (_hitCount > 30 && _currentHP > 0)
		{
			setState(E_IDLE);
			_hitCount = 0;
		}
		break;

	case E_GRAB:
		_index = 0;

		if (_left)
		{
			_x = _pX + 120;
			_y = _pY;
		}
		else
		{
			_x = _pX - 120;
			_y = _pY;
		}

		break;

	case E_FLYING:
		//몬스터 렉트의 라이트가 카메라 화면 오른쪽 밖으로 나가려고한다면 체공상태를 풀고 인덱스를 1로 바꾼다
		if (_flying) _index = 0;

		//몬스터 렉트의 라이트가 카메라 화면 오른쪽 밖으로 나가려고한다면 체공상태를 풀고 인덱스를 1로 바꾼다
		if (_rc.right > CAMX + WINSIZEX && _flying && _left)
		{
			if (_currentHP <= 0) setState(E_DEAD);
			else _currentHP -= 20;

			_flying = false;
			_index = 1;
			//x좌표 위치를 보정해주는 이유는 안해주면 애가 가끔 낑김
			_x -= 5;
		}
		//몬스터 렉트의 레프트가 카메라 화면 왼쪽 밖으로 나가려고한다면 체공상태를 풀고 인덱스를 1로 바꾼다
		if (_rc.left < CAMX && _flying && !_left)
		{
			if (_currentHP <= 0) setState(E_DEAD);
			else _currentHP -= 20;

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
			setState(E_IDLE);
		}
		break;
	}
}

void boss::phase1() // 공격렉트가 전신에 생겨서 치고다님
{
	_state = E_HIT;
	if (getDistance(_x, _y, _destX, _destY) > 30)
	{
		_x += 10.f * cosf(getAngle(_x, _y, _destX, _destY));
		_y -= 10.f * sinf(getAngle(_x, _y, _destX, _destY));
		_attackRc = RectMakeCenter(_x, _y+100, 300, 100);
	}
	else
	{
		_attackRc = { 0,0,0,0 };
		++_rideCount;
		if (_rideCount > 80)
		{
			_rideCount = 0;
			_destX = _pX;
			_destY = _pY;
			if (_destX > _x) _left = false;
			else _left = true;
		}
	}
	if (_phaseCount > 300)
	{
		_phaseCount = 0; _phase = 0; _index = _rideCount = 0;
		_state = E_IDLE;
		_attackRc = { 0,0,0,0 };
	}


	if (_index > 2)
	{
		_index = 0;
	}
}

void boss::phase2()
{ 
	_state = E_HIT;
	if (_jumping)
	{ // 점프중
		_attackRc = { 0,0,0,0 };
		_y -= 20;
		if (_destY - _y > WINSIZEY)
		{
			_destY = _pY+60;
			_destX = _pX;
			_x = _destX;
			_jumping = false;
		}
	}
	else if (_destY > _rc.bottom)
	{ // 착지
		_attackRc = RectMakeCenter(_x, _y + 70, 180, 60);
		_y += 20;
	}
	else if (_destY <= _rc.bottom)
	{ // 착지후 쉐이킹
		_phaseCount = _phase = _shakeCount = 0;
		setState(E_SHAKE);
		_attackRc = { 0,0,0,0 };
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
	_phase = 1;
	_plAtkNum = 1;
	_flying = _atkArea = false;
	_left = true;
	_destX = CAMX + WINSIZEY / 2;
	_destY = CAMY + WINSIZEY / 2;

	SOUNDMANAGER->stop("메인브금");
	SOUNDMANAGER->play("보스등장");
	return S_OK;
}

void boss::release()
{
}

void boss::update()
{	//프레임 렌더가 되는 속도를 조절해줌
	_attackRc = { 0,0,0,0 };
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
	//상태에 따라 그림자의 크기를 다르게하여 그려줍니다
	if (_phase == 0)
	{
		switch (_state)
		{
		case E_IDLE: case E_WALK: case E_ATK: case E_HIT: case E_GRAB:
			_rc = RectMakeCenter(_x, _y, 150, 200);
			_shadow = RectMakeCenter(_rc.left + 75, _rc.bottom + 10, 150, 50);
			break;
		case E_DEAD: case E_FLYING:
			_rc = RectMakeCenter(_x, _y, 208, 200);
			_shadow = RectMakeCenter(_rc.left + 104, _rc.bottom - 20, 208, 50);
			break;
		case E_SHAKE:		case E_WALK2:
			_rc = RectMakeCenter(_x, _y+40, 180, 120);
			_shadow = RectMakeCenter(_rc.left + 90, _rc.bottom + 10, 180, 50);
			break;
		}
	}	
	if (_phase == 1)
	{ // 차탔음
		_rc = RectMakeCenter(_x, _y, 200, 200);
		_shadow = RectMakeCenter(_rc.left + 100, _rc.bottom + 50, 350, 70);
	}
	if (_phase == 2)
	{
		_rc = RectMakeCenter(_x, _y, 180, 120);
		if (_jumping)
		{
			_shadow = RectMake(_shadow.left, _shadow.top, 180, 50);
		}
		else  _shadow = RectMakeCenter(_destX, _destY+60, 180, 50);
	}
	if(!SOUNDMANAGER->isPlaySound("보스등장") && 
		!SOUNDMANAGER->isPlaySound("보스브금") &&
		!SOUNDMANAGER->isPlaySound("메인브금"))
	{//사운드 설정.
		SOUNDMANAGER->play("보스목소리");
		SOUNDMANAGER->play("보스브금");
	}
}

void boss::render()
{
	fillColorEllipse(40, 40, 40, _shadow);
	if (_phase == 0)
	{
		//볼 몬스터의 상태에 따라 렌더되는 이미지를 정해줌
		switch (_state)
		{
		case E_SHAKE:
			if (_left) FINDIMG("boss_shakes")->frameRender(getMemDC(), _rc.left-20, _rc.top-15, _index, 1);
			else FINDIMG("boss_shakes")->frameRender(getMemDC(), _rc.left-30, _rc.top-15, _index, 0);		break;
		case E_IDLE:
			if (_left) FINDIMG("boss_idle")->frameRender(getMemDC(), _rc.left-48, _rc.top, _index, 1);
			else FINDIMG("boss_idle")->frameRender(getMemDC(), _rc.left-20, _rc.top, _index, 0);		break;
		case E_WALK:
			if (_left) FINDIMG("boss_walk")->frameRender(getMemDC(), _rc.left-15, _rc.top, _index, 1);
			else FINDIMG("boss_walk")->frameRender(getMemDC(), _rc.left-25, _rc.top, _index, 0);		break;
		case E_WALK2:
			if (_left) FINDIMG("boss_crawl")->frameRender(getMemDC(), _rc.left-21, _rc.top-5, _index, 1);
			else FINDIMG("boss_crawl")->frameRender(getMemDC(), _rc.left-40, _rc.top-5, _index, 0);		break;
		case E_ATK:
			if (_left) FINDIMG("boss_atk")->frameRender(getMemDC(), _rc.left-120, _rc.top, _index, 1);
			else FINDIMG("boss_atk")->frameRender(getMemDC(), _rc.left-45, _rc.top, _index, 0);		break;
		case E_DEAD:
			if (_left) FINDIMG("boss_dead")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 1);
			else FINDIMG("boss_dead")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 0);		break;
		case E_HIT:
			// _plAtkNum : 플레이어 공격상태 체크용 테스트 변수
			// 1 = 오른쪽에서 왼쪽으로 공격 , 2 = 왼쪽에서 오른쪽으로 공격
			if (_plAtkNum == 1)
			{
				if (_left) FINDIMG("boss_hit4")->frameRender(getMemDC(), _rc.left - 33, _rc.top, 0, 1);
				else FINDIMG("boss_hit4")->frameRender(getMemDC(), _rc.left - 3, _rc.top, 0, 0);	break;
			}
			if (_plAtkNum == 2)
			{
				if (_left) FINDIMG("boss_hit4")->frameRender(getMemDC(), _rc.left - 33, _rc.top, 0, 1);
				else FINDIMG("boss_hit4")->frameRender(getMemDC(), _rc.left - 3, _rc.top, 0, 0);	break;
			}
		case E_GRAB:

			if (_plAtkNum == 1)
			{
				if (_left) FINDIMG("boss_hit")->frameRender(getMemDC(), _rc.left - 5, _rc.top, 0, 1);
				else FINDIMG("boss_hit")->frameRender(getMemDC(), _rc.left - 3, _rc.top, 0, 0); break;
			}
			if (_plAtkNum == 2)
			{
				if (_left) FINDIMG("boss_hit")->frameRender(getMemDC(), _rc.left - 5, _rc.top, 0, 1);
				else FINDIMG("boss_hit")->frameRender(getMemDC(), _rc.left - 3, _rc.top, 0, 0); break;
			}
		case E_FLYING:
			if (_left) FINDIMG("boss_dead")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 1);
			else FINDIMG("boss_dead")->frameRender(getMemDC(), _rc.left, _rc.top, _index, 0); break;
		}
	}
	else if (_phase == 1)
	{
		if (_left) FINDIMG("boss_car")->frameRender(getMemDC(), _rc.left-100, _rc.top-50, _index, 1);
		else FINDIMG("boss_car")->frameRender(getMemDC(), _rc.left-100, _rc.top-50, _index, 0);
	}
	else if (_phase == 2)
	{
		if (_left) FINDIMG("boss_crawl")->frameRender(getMemDC(), _rc.left - 21, _rc.top-5, _index, 1);
		else FINDIMG("boss_crawl")->frameRender(getMemDC(), _rc.left - 40, _rc.top - 5, _index, 0);
	}
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _rc);
		Rectangle(getMemDC(), _attackRc);
	}
	
}
