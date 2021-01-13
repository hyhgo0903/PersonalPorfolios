#include "stdafx.h"
#include "minion3.h"


minion3::minion3()
{
}


minion3::~minion3()
{
}

void minion3::enemyState()
{
	_count++;
	//HIT상태에서만 hit카운트가 더해진다
	if (_state == E_HIT) _hitCount++;
	//GRAB상태에서만 grab카운트가 더해진다
	if (_state == E_GRAB) _grabCount++;


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

	switch (_state)
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
			if((getDistance(_x, _y, _pX, _pY) > 200)) setState(E_WALK);
			else
			{
				_attackCount++;
				if (_attackCount > 45)
				{
					setState(E_ATK);
					_attackCount = 0;
				}
			}
			_index = 0;
		}
		else
		{
			//엘스로 오른쪽도 설정
			_left = false;
			if ((getDistance(_x, _y, _pX, _pY) > 200)) setState(E_WALK);
			else
			{
				_attackCount++;
				if (_attackCount > 45)
				{
					setState(E_ATK);
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
				setState(E_ATK);
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

		if (_left)
		{
			_attackRc = RectMakeCenter(_x - 130, _y, 150, 60);
		}
		else
		{
			_attackRc = RectMakeCenter(_x + 130, _y, 150, 60);
		}

		if (_index > 2)
		{
			_attackRc = RectMakeCenter(0, 0, 0, 0);
			setState(E_IDLE);
		}
		break;

	case E_DEAD:
		_alpha -= 7;

		if (_index > 3) _isDead = true;
		break;

	case E_HIT:
		_index = 0;
		if (_left) _x += 0.8f;
		else _x -= 0.8f;
		//피격모션 유지시간 (30 = 0.5초)
		if (_hitCount > 30)
		{
			setState(E_IDLE);
			_hitCount = 0;
		}
		if (_currentHP <= 0)
		{
			setState(E_DEAD);
		}
		break;

	case E_GRAB:
		_index = 0;

		if (_left)
		{
			_x = _pX + 150;
			_y = _pY + 10;
		}
		else
		{
			_x = _pX - 150;
			_y = _pY + 10;
		}

		//그랩모션 유지시간 (90 = 1.5초)
		if (_grabCount > 90)
		{
			setState(E_IDLE);
			_grabCount = 0;
		}
		break;

	case E_FLYING:
		//날고있는상태에서 인덱스를 고정시켜줌
		if (_flying) _index = 0;

		//몬스터 렉트의 라이트가 카메라 화면 오른쪽 밖으로 나가려고한다면 체공상태를 풀고 인덱스를 1로 바꾼다
		if (_rc.right > CAMX + WINSIZEX && _flying && _left)
		{
			//if (_currentHP <= 0) setState(E_DEAD);
			//else _currentHP -= 20;

			//_flying = false;
			//_index = 1;
			setState(E_FLYING2);
			//x좌표 위치를 보정해주는 이유는 안해주면 애가 가끔 낑김
			_x -= 5;
		}
		//몬스터 렉트의 레프트가 카메라 화면 왼쪽 밖으로 나가려고한다면 체공상태를 풀고 인덱스를 1로 바꾼다
		if (_rc.left < CAMX && _flying && !_left && _index == 0)
		{
			//if (_currentHP <= 0) setState(E_DEAD);
			//else _currentHP -= 20;

			//_flying = false;
			//_index = 1;
			setState(E_FLYING2);
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

	case E_FLYING2:
		if (_flying) _index = 0;

		if (!_flyDown)
		{
			if (_shadow.left != _shadow.right)
			{
				_shadow.left += 1;
				_shadow.right -= 1;
			}
		}
		if (_flyDown && _left && _shadow.left != _shadow.right)
		{
			_shadow.left -= 6;
			_shadow.right -= 6;
		}
		if (_flyDown && !_left && _shadow.left != _shadow.right)
		{
			_shadow.left += 6;
			_shadow.right += 6;
		}
		if (_left && !_flyDown)
		{
			_y -= 25.0f;
			_x -= 5.5f;
		}
		else if (_left && _flyDown)
		{
			_y += 25.0f;
			_x -= 5.5f;
		}
		else if (!_left && !_flyDown)
		{
			_y -= 25.0f;
			_x += 5.5f;
		}
		else
		{
			_y += 25.0f;
			_x += 5.5f;
		}
		if (_flyDown && _rc.bottom >= _shadow.top - 10)
		{
			setState(E_FLYING);
			_index = 1;
			_flyDown = false;
			_flying = false;
			if (_currentHP <= 0) setState(E_DEAD);
			getDamage(20);
		}
		if (_shadow.top - _rc.bottom > 400)
		{
			_flyDown = true;
		}
	}
}

void minion3::enemyStateRender()
{
	//볼 몬스터의 상태에 따라 렌더되는 이미지를 정해줌
	switch (_state)
	{
	case E_IDLE:
		if (_left) FINDIMG("enemy3_idle")->frameRender(getMemDC(), _rc.left - 40, _rc.top - 45, _index, 0);
		else FINDIMG("enemy3_idle")->frameRender(getMemDC(), _rc.left - 35, _rc.top - 45, _index, 1);		break;
	case E_WALK:
		if (_left) FINDIMG("enemy3_walk")->frameRender(getMemDC(), _rc.left - 43, _rc.top - 54, _index, 0);
		else FINDIMG("enemy3_walk")->frameRender(getMemDC(), _rc.left - 32, _rc.top - 54, _index, 1);		break;
	case E_ATK:
		if (_left) FINDIMG("enemy3_atk")->frameRender(getMemDC(), _rc.left - 130, _rc.top - 48, _index, 0);
		else FINDIMG("enemy3_atk")->frameRender(getMemDC(), _rc.left - 80, _rc.top - 48, _index, 1);		break;
	case E_DEAD:
		if (_left) FINDIMG("enemy3_dead")->alphaFrameRender(getMemDC(), _rc.left - 40, _rc.top - 55, _index, 0, _alpha);
		else FINDIMG("enemy3_dead")->alphaFrameRender(getMemDC(), _rc.left - 50, _rc.top - 55, _index, 1, _alpha);		break;
	case E_HIT:
		if (_left) FINDIMG("enemy3_hit")->frameRender(getMemDC(), _rc.left - 45, _rc.top - 50, _index, 0);
		else FINDIMG("enemy3_hit")->frameRender(getMemDC(), _rc.left - 30, _rc.top - 50, _index, 1);		break;
	case E_GRAB:
		if (_left) FINDIMG("enemy3_grab")->frameRender(getMemDC(), _rc.left - 40, _rc.top - 70, _index, 0);
		else FINDIMG("enemy3_grab")->frameRender(getMemDC(), _rc.left - 35, _rc.top - 70, _index, 1); break;
	case E_FLYING:
		if (_left) FINDIMG("enemy3_flying")->frameRender(getMemDC(), _rc.left - 54, _rc.top - 56, _index, 0);
		else FINDIMG("enemy3_flying")->frameRender(getMemDC(), _rc.left - 36, _rc.top - 62, _index, 1); break;
	case E_FLYING2:
		if (_left) FINDIMG("enemy3_flying")->frameRender(getMemDC(), _rc.left - 30, _rc.top - 10, _index, 0);
		else FINDIMG("enemy3_flying")->frameRender(getMemDC(), _rc.left - 60, _rc.top - 10, _index, 1); break;
	}
}

void minion3::keyManager()
{
	//////////////////////////////////////////////////////////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) _left = true;
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) _left = false;
	if (KEYMANAGER->isOnceKeyDown('1')) { _index = 0; _state = E_IDLE; }
	if (KEYMANAGER->isOnceKeyDown('2')) { _index = 0; _state = E_WALK; }
	if (KEYMANAGER->isOnceKeyDown('3')) { _index = 0; _state = E_ATK; }
	if (KEYMANAGER->isOnceKeyDown('4')) { _index = 0; _state = E_DEAD; }
	if (KEYMANAGER->isOnceKeyDown('5')) { _index = 0; _state = E_HIT; }
	if (KEYMANAGER->isOnceKeyDown('6')) { _index = 0; _state = E_GRAB; }
	if (KEYMANAGER->isOnceKeyDown('7')) { _index = 0; _state = E_FLYING; }
	//////////////////////////////////////////////////////////////////////
}
HRESULT minion3::init(float x, float y)
{
	_x = CAMX + x;	_y = CAMY + y;
	_currentHP = _maxHP = 100;
	_count = _index = _attackCount = _hitCount = _grabCount = 0;
	setState(E_IDLE);
	_left = true;
	_flying = false;
	_atkArea = false;
	_randomNum = RND->getFromIntTo(20, 50);
	_isDead = false;
	_flyDown = false;
	_alpha = 255;
	return S_OK;
}

void minion3::release()
{
}

void minion3::update()
{
	_rc = RectMakeCenter(_x, _y, 120, 120);
	enemyState();

	//테스트용, 파일 합치기전엔 항상 주석처리할것
	//keyManager(); 
	//상태에 따라 그림자의 크기를 다르게하여 그려줍니다
	if (_state == E_IDLE || _state == E_WALK || _state == E_WALK2 || _state == E_ATK || _state == E_HIT)
		_shadow = RectMakeCenter(_rc.left + 60, _rc.bottom + 30, 230, 50);

	if (_state == E_GRAB || _state == E_FLYING) _shadow = RectMakeCenter(_rc.left + 60, _rc.bottom + 30, 180, 50);
}

void minion3::render()
{
	if(_state != E_DEAD) fillColorEllipse(40, 40, 40, _shadow);
	enemyStateRender();
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _rc);
		Rectangle(getMemDC(), _attackRc);
	}
}


