#include "stdafx.h"
#include "minion2.h"

minion2::minion2()
{
}

minion2::~minion2()
{
}

void minion2::enemyState()
{
	_count++;
	//HIT상태에서만 hit카운트가 더해진다
	if (_state2 == E_HIT) _hitCount++;
	//GRAB상태에서만 grab카운트가 더해진다
	if (_state2 == E_GRAB) _grabCount++;

	//공격범위 안에 플레이어가 있는지 체크함, 플레이어와 에너미의 간격이 100미만이면 true
	if (getDistance(_x, _y, _pX, _pY) < 100) _atkArea = true;
	//간격이 100이상이면 false
	if (getDistance(_x, _y, _pX, _pY) >= 100) _atkArea = false;
	//프레임 렌더가 되는 속도를 조절해줌
	if (_count % 10 == 0)
	{
		_index++;
		_count = 0;
	}

	switch (_state2)
	{
	case E_IDLE:
		//프레임 이미지의 최대 렌더값을 초과하지 않도록 설정해줌
		if (_index > 1) _index = 0;

		//플레이어가 에너미의 오른쪽에 있다면
		if (_x > _pX)
		{
			//에너미는 왼쪽을 보고있다고 설정해주고 WALK상태로 변경 후 
			//애니메이션을 처음부터 처리하기위해 인덱스를 0으로 초기화
			_left = true;
			if ((getDistance(_x, _y, _pX, _pY) > 200)) _state2 = E_WALK;
			else
			{
				_attackCount++;
				if (_attackCount > 45)
				{
					_state2 = E_ATK;
					_index = 0;
					_attackCount = 0;
				}
			}
			_index = 0;
		}
		else
		{
			//엘스로 오른쪽도 설정
			_left = false;
			if ((getDistance(_x, _y, _pX, _pY) > 200)) _state2 = E_WALK;
			else
			{
				_attackCount++;
				if (_attackCount > 45)
				{
					_state2 = E_ATK;
					_index = 0;
					_attackCount = 0;
				}
			}
			_index = 0;
		}
		break;

	case E_WALK:
		//프레임 이미지 최대 렌더값을 초과하지않도록 초기화해줌
		if (_index > 4) _index = 0;
		//플레이어와 에너미의 거리가 200이하라면 ATK상태로 변경 후
		//이미지를 처음부터 렌더하기위해 인덱스 초기화
		if (getDistance(_x, _y, _pX, _pY) <= 200)
		{
			_attackCount++;
			if (_attackCount > 45)
			{
				_state2 = E_ATK;
				_index = 0;
				_attackCount = 0;
			}
		}
			//플레이어가 에너미의 오른쪽에있다면
		if (_x > _pX)
		{
			_left = true; //에너미는 왼쪽을바라보고
			if (!_atkArea) //플레이어의 아래좌표까지 따라간다
			{
				_x += 2.7f * cosf(getAngle(_x, _y, _pX + 90, _pY + _randomNum));
				_y -= 2.7f * sinf(getAngle(_x, _y, _pX + 90, _pY + _randomNum));
			}
		}
		else
		{
			_left = false; //에너미는 오른쪽을 바라보고
			if (!_atkArea) //플레이어의 아래좌표까지 따라간다
			{
				_x += 2.7f * cosf(getAngle(_x, _y, _pX - 90, _pY + _randomNum));
				_y -= 2.7f * sinf(getAngle(_x, _y, _pX - 90, _pY + _randomNum));
			}
		}
		break;

	case E_ATK:
		if (_index > 15)
		{
			_state2 = E_IDLE;
			_index = 0;
		}
		break;

	case E_DEAD:
		_index = 0;
		break;

	case E_HIT:
		_index = 0;
		//피격모션 유지시간 (30 = 0.5초)
		if (_hitCount > 30)
		{
			_state2 = E_IDLE;
			_hitCount = 0;
		}
		break;

	case E_GRAB:
		_index = 0;
		//그랩모션 유지시간 (90 = 1.5초)
		if (_grabCount > 90)
		{
			_state2 = E_IDLE;
			_grabCount = 0;
		}
		break;

	case E_FLYING:
		_index = 0;
		//몬스터 렉트의 라이트가 카메라 화면 오른쪽 밖으로 나가려고한다면 체공상태를 풀고 IDLE 상태로 변경
		if (_rc.right > CAMX + WINSIZEX && _flying && _left)
		{
			_flying = false;
			_state2 = E_IDLE;
			//x좌표 위치를 보정해주는 이유는 안해주면 애가 가끔 낑김
			_x -= 5;
		}
		//몬스터 렉트의 레프트가 카메라 화면 왼쪽 밖으로 나가려고한다면 체공상태를 풀고 인덱스를 1로 바꾼다
		if (_rc.left < CAMX && _flying && !_left)
		{
			_flying = false;
			_state2 = E_IDLE;
			//x좌표 위치를 보정해주는 이유는 안해주면 애가 가끔 낑김
			_x += 5;
		}
		//인덱스가 정상적으로 초기화되었고 지상에있는 상태라면 플라잉 상태로 변경시켜줌
		if (!_flying) _flying = true;
		//플라잉 상태에서만 좌표를 이동시킨다
		if (_flying && _left) _x += 15.5f;
		if (_flying && !_left) _x -= 15.5f;

		break;
	}
}

void minion2::enemyStateRender()
{
	switch (_state2)
	{
	case E_IDLE:
		if (_left) FINDIMG("enemy2_idle")->frameRender(getMemDC(), _rc.left - 70, _rc.top - 160, _index, 1);
		else FINDIMG("enemy2_idle")->frameRender(getMemDC(), _rc.left - 50, _rc.top - 160, _index, 0);		break;
	case E_WALK:
		if (_left) FINDIMG("enemy2_move")->frameRender(getMemDC(), _rc.left - 75, _rc.top - 160, _index, 1);
		else FINDIMG("enemy2_move")->frameRender(getMemDC(), _rc.left - 75, _rc.top - 160, _index, 0);		break;
	case E_ATK:
		if (_left) FINDIMG("enemy2_atk")->frameRender(getMemDC(), _rc.left - 253, _rc.top - 172, _index, 1);
		else FINDIMG("enemy2_atk")->frameRender(getMemDC(), _rc.left - 158, _rc.top - 172, _index, 0);		break;
	case E_DEAD:
		if (_left) FINDIMG("enemy2_dead")->frameRender(getMemDC(), _rc.left - 110, _rc.top - 175, _index, 1);
		else FINDIMG("enemy2_dead")->frameRender(getMemDC(), _rc.left - 60, _rc.top - 175, _index, 0);		break;
	case E_HIT:
		if (_left) FINDIMG("enemy2_hit")->frameRender(getMemDC(), _rc.left - 50, _rc.top - 77, _index, 0);
		else FINDIMG("enemy2_hit")->frameRender(getMemDC(), _rc.left - 175, _rc.top - 87, _index, 1);		break;
	case E_GRAB:
		if (_left) FINDIMG("enemy2_grab")->frameRender(getMemDC(), _rc.left - 180, _rc.top - 100, _index, 0);
		else FINDIMG("enemy2_grab")->frameRender(getMemDC(), _rc.left - 50, _rc.top - 100, _index, 1);		break;
	case E_FLYING:
		if (_left) FINDIMG("enemy2_flying")->frameRender(getMemDC(), _rc.left - 30, _rc.top - 77, _index, 0);
		else FINDIMG("enemy2_flying")->frameRender(getMemDC(), _rc.left - 220, _rc.top - 77, _index, 1);	break;
	}
}

void minion2::keyManager()
{
	//////////////////////////////////////////////////////////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) _left = true;
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) _left = false;
	if (KEYMANAGER->isOnceKeyDown('1')) { _index = 0; _state2 = E_IDLE; }
	if (KEYMANAGER->isOnceKeyDown('2')) { _index = 0; _state2 = E_WALK; }
	if (KEYMANAGER->isOnceKeyDown('3')) { _index = 0; _state2 = E_ATK; }
	if (KEYMANAGER->isOnceKeyDown('4')) { _index = 0; _state2 = E_DEAD; }
	if (KEYMANAGER->isOnceKeyDown('5')) { _index = 0; _state2 = E_HIT; }
	if (KEYMANAGER->isOnceKeyDown('6')) { _index = 0; _state2 = E_GRAB; }
	if (KEYMANAGER->isOnceKeyDown('7')) { _index = 0; _state2 = E_FLYING; }
	//////////////////////////////////////////////////////////////////////
}

HRESULT minion2::init(float x, float y)
{
	_x = CAMX + x;	_y = CAMY + y;
	_currentHP = _maxHP = 100;
	_count = _index = _attackCount = _hitCount = _grabCount = 0;
	_state2 = E_IDLE;
	_left = true;
	_flying = false;
	return S_OK;
}

void minion2::release()
{
}

void minion2::update()
{
	_rc = RectMakeCenter(_x, _y, 50, 200);
	enemyState();
	//테스트용, 파일 합치기전엔 항상 주석처리할것
	//keyManager();

	//상태에 따라 그림자의 크기를 다르게하여 그려줍니다
	if (_state2 == E_IDLE || _state2 == E_WALK || _state2 == E_WALK2 || _state2 == E_ATK || _state2 == E_DEAD || _state2 == E_HIT)
		_shadow = RectMakeCenter(_rc.left + 25, _rc.bottom + 10, 200, 50);

	if (_state2 == E_GRAB || _state2 == E_FLYING) _shadow = RectMakeCenter(_rc.left + 25, _rc.bottom + 10, 150, 50);
}

void minion2::render()
{
	fillColorEllipse(40, 40, 40, _shadow);
	enemyStateRender();
	if (KEYMANAGER->isToggleKey(VK_F1)) Rectangle(getMemDC(), _rc);
}

