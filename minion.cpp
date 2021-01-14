#include "stdafx.h"
#include "minion.h"

minion::minion()
{
}

minion::~minion()
{
}

void minion::enemyState()
{	
	_attackRc = { 0, 0, 0, 0 };
	_count++;
	//HIT상태에서만 hit카운트가 더해진다
	if (_state == E_HIT) _hitCount++;
	//GRAB상태에서만 grab카운트가 더해진다
	if (_state == E_GRAB) _grabCount++;
	//DEAD상태에서 공중에 뜨는 시간을 체크하기위해 만듬
	if (_state == E_DEAD) _flyingCount++;

	//공격범위 안에 플레이어가 있는지 체크함, 플레이어와 에너미의 간격이 100미만이면 true
	if (getDistance(_x, _y, _pX, _pY) < 100) _atkArea = true;
	//간격이 100이상이면 false
	if (getDistance(_x, _y, _pX, _pY) >= 100) _atkArea = false;

	//프레임 렌더가 되는 속도를 조절해줌
	if (_count % 10 == 0)
	{
		if(!_flying) _index++;
		_count = 0;
	}
		

	//상태마다 기능을 정의해
	switch (_state)
	{
	case E_IDLE:
		//프레임 이미지의 최대 렌더값을 초과하지 않도록 설정해줌
		if (_index > 2) _index = 0;
		
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
		break;

	case E_WALK:
		//프레임 이미지 최대 렌더값을 초과하지않도록 초기화해줌
		if (_index > 2) _index = 0;
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
		}
		break;

	case E_WALK2:
		//프레임 이미지 최대 렌더값을 초과하지않도록 인덱스 초기화
		if (_index > 9) _index = 0;
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
				_x += 2.7f * cosf(getAngle(_x, _y, _pX + 100, _pY + _randomNum));
				_y -= 2.7f * sinf(getAngle(_x, _y, _pX + 100, _pY + _randomNum));
			}
		}
		else //왼쪽에 있다면
		{
			_left = false; //에너미는 오른쪽을 바라보고
			if (!_atkArea) //플레이어의 아래좌표까지 이동한다.
			{
				_x += 2.7f * cosf(getAngle(_x, _y, _pX - 100, _pY + _randomNum));
				_y -= 2.7f * sinf(getAngle(_x, _y, _pX - 100, _pY + _randomNum));
			}
		}
		break;

	case E_ATK:

		if (_index == 2)
		{
			if (_left)
			{
				_attackRc = RectMakeCenter(_x - 110, _y - 45, 80, 80);
			}
			else
			{
				_attackRc = RectMakeCenter(_x + 110, _y - 45, 80, 80);
			}
		}

		if (_index > 2)
		{
			_attackRc = RectMakeCenter(0, 0, 0, 0);
			setState(E_WALK);
		}
		break;

	case E_DEAD:
		_alpha -= 7;
		if (_alpha < 0) _alpha = 0;

		if (_index > 6)
		{
			_isDead = true;
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
			_x = _pX + 150;
			_y = _pY + 10;
		}
		else
		{
			_x = _pX - 150;
			_y = _pY + 10;
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

void minion::enemyStateRender()
{
	//볼 몬스터의 상태에 따라 렌더되는 이미지를 정해줌
	switch (_state)
	{
	case E_IDLE:
		if (_left) FINDIMG("enemy1_idle")->frameRender(getMemDC(), _rc.left - 40, _rc.top - 10, _index, 0);
		else FINDIMG("enemy1_idle")->frameRender(getMemDC(), _rc.left - 80, _rc.top - 10, _index, 1);		break;
	case E_WALK:
		if (_left) FINDIMG("enemy1_idle")->frameRender(getMemDC(), _rc.left - 40, _rc.top - 10, _index, 0);
		else FINDIMG("enemy1_idle")->frameRender(getMemDC(), _rc.left - 80, _rc.top - 10, _index, 1);		break;
	case E_WALK2:
		if (_left) FINDIMG("enemy1_walk")->frameRender(getMemDC(), _rc.left - 75, _rc.top - 28, _index, 0);
		else FINDIMG("enemy1_walk")->frameRender(getMemDC(), _rc.left - 75, _rc.top - 28, _index, 1);		break;
	case E_ATK:
		if (_left) FINDIMG("enemy1_atk")->frameRender(getMemDC(), _rc.left - 130, _rc.top - 160, _index, 0);
		else FINDIMG("enemy1_atk")->frameRender(getMemDC(), _rc.left - 50, _rc.top - 160, _index, 1);		break;
	case E_DEAD:
		if (_left) FINDIMG("enemy1_dead")->alphaFrameRender(getMemDC(), _rc.left - 60, _rc.top - 30, _index, 0, _alpha);
		else FINDIMG("enemy1_dead")->alphaFrameRender(getMemDC(), _rc.left - 60, _rc.top - 30, _index, 1, _alpha);		break;
	case E_HIT:
		// _plAtkNum : 플레이어 공격상태 체크용 테스트 변수
		// 1 = 오른쪽에서 왼쪽으로 공격 , 2 = 왼쪽에서 오른쪽으로 공격
		if (_plAtkNum == 1)
		{
			if (_left) FINDIMG("enemy1_hit1")->frameRender(getMemDC(), _rc.left - 65, _rc.top - 43, _index, 0);
			else FINDIMG("enemy1_hit1")->frameRender(getMemDC(), _rc.left - 65, _rc.top - 43, _index, 1);
		}
		if (_plAtkNum == 2)
		{
			if (_left) FINDIMG("enemy1_hit3")->frameRender(getMemDC(), _rc.left - 65, _rc.top - 13, _index, 0);
			else FINDIMG("enemy1_hit3")->frameRender(getMemDC(), _rc.left - 65, _rc.top - 13, _index, 1);
		}
		break;
	case E_GRAB:
		if (_left) FINDIMG("enemy1_grab")->frameRender(getMemDC(), _rc.left - 30, _rc.top - 30, _index, 0);
		else FINDIMG("enemy1_grab")->frameRender(getMemDC(), _rc.left, _rc.top - 30, _index, 1); break;
	case E_FLYING:
		if (_left) FINDIMG("enemy1_flying")->frameRender(getMemDC(), _rc.left - 30, _rc.top - 10, _index, 0);
		else FINDIMG("enemy1_flying")->frameRender(getMemDC(), _rc.left - 60, _rc.top - 10, _index, 1); break;
	case E_FLYING2:
		if (_left) FINDIMG("enemy1_flying")->frameRender(getMemDC(), _rc.left - 30, _rc.top - 10, _index, 0);
		else FINDIMG("enemy1_flying")->frameRender(getMemDC(), _rc.left - 60, _rc.top - 10, _index, 1); break;
	}
}

void minion::keyManager()
{
	//////////////////////////////////////////////////////////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) _left = true;
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) _left = false;
	if (KEYMANAGER->isOnceKeyDown(VK_F4)) { _plAtkNum += 1; if (_plAtkNum > 2) _plAtkNum = 1; }
	if (KEYMANAGER->isOnceKeyDown('1')) { setState(E_IDLE); }
	if (KEYMANAGER->isOnceKeyDown('2')) { setState(E_WALK);	}
	if (KEYMANAGER->isOnceKeyDown('3')) { setState(E_ATK);	}
	if (KEYMANAGER->isOnceKeyDown('4')) { setState(E_DEAD); }
	if (KEYMANAGER->isOnceKeyDown('5')) { setState(E_HIT);	}
	if (KEYMANAGER->isOnceKeyDown('6')) { setState(E_GRAB);	}
	if (KEYMANAGER->isOnceKeyDown('7')) { setState(E_FLYING);	}
	//////////////////////////////////////////////////////////////////////
}

HRESULT minion::init(float x, float y)
{
	_x = CAMX + x;	_y = CAMY + y;
	_currentHP = _maxHP = 100;
	_count = _index = _attackCount = _hitCount = _grabCount = _flyingCount = 0;
	setState(E_IDLE);
	_left = true;
	_plAtkNum = 1;
	_flying = false;
	_atkArea = false;
	_randomNum = RND->getFromIntTo(-3, 3);
	_isDead = false;
	_flyDown = false;
	_alpha = 255;
	return S_OK;
}

void minion::release()
{
}

void minion::update()
{
	_rc = RectMakeCenter(_x, _y, 150, 150);
	enemyState();
	//테스트용, 파일 합치기전엔 항상 주석처리할것
	//keyManager();
	
	
	//상태에 따라 그림자의 크기를 다르게하여 그려줍니다
	if(_state == E_IDLE || _state == E_WALK || _state == E_WALK2 || _state == E_ATK || _state == E_HIT) 
	_shadow = RectMakeCenter(_rc.left + 75, _rc.bottom + 10, 250, 50);

	if (_state == E_GRAB || _state == E_FLYING) _shadow = RectMakeCenter(_rc.left + 75, _rc.bottom + 10, 200, 50);
}

void minion::render()
{
	if(_state != E_DEAD) fillColorEllipse(40, 40, 40, _shadow);
	//Ellipse(getMemDC(), _shadow);

	enemyStateRender();
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _rc);
		Rectangle(getMemDC(), _attackRc);
	}
}