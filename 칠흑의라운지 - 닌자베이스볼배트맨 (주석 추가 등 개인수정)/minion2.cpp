#include "stdafx.h"
#include "minion2.h"

minion2::minion2()
{
}

minion2::~minion2()
{
}

HRESULT minion2::init(float x, float y)
{
	_x = CAMX + x;	_y = CAMY + y;
	_currentHP = _maxHP = 100;
	_count = _index = _attackCount = _hitCount = _grabCount = _deadCount = 0;
	_randomNum = RND->getFromIntTo(-15, 15);

	_alpha = 255;

	setState(E_IDLE);

	_left = true;	_flying = false;
	_atkArea = false;	_isDead = false;
	_flyDown = false;
	return S_OK;
}

void minion2::enemyState()
{
	_attackRc = { 0, 0, 0, 0 };
	_count++;
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

		//에너미가 플레이어의 오른쪽에 있다면
		if (_x > _pX)
		{
			//에너미는 왼쪽을 보고있다고 설정해준다
			_left = true;
			_index = 0;

			//만약 enemy와 player의 거리가 200보다 크다면 E_WALK상태로 변경
			if ((getDistance(_x, _y, _pX, _pY) > 200)) setState(E_WALK);
			
			//그게 아니라면 일정시간 후 E_ATK상태로 변경
			else
			{
				_attackCount++;
				if (_attackCount > 45)
				{
					setState(E_ATK);
					_attackCount = 0;
				}
			}
		}
		else
		{
			//엘스로 오른쪽도 설정
			_left = false;
			_index = 0;

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
		}
		break;

	case E_WALK:
		//프레임 이미지 최대 렌더값을 초과하지않도록 초기화해줌
		if (_index > 4) _index = 0;

		//플레이어와 에너미의 거리가 200이하라면 ATK상태로 변경
		if (getDistance(_x, _y, _pX, _pY) <= 200)
		{
			_attackCount++;
			if (_attackCount > 45)
			{
				setState(E_ATK);
				_attackCount = 0;
			}
		}

		//에너미가 플레이어의 오른쪽에있다면
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
		//E_ATK의 _index == 3의 이미지를 렌더할때 공격렉트를 아래의 위치에 생성한다
		if (_index == 3)
		{
			if (_left)
			{
				_attackRc = RectMakeCenter(_x - 90, _y - 40, 140, 60);
			}
			else
			{
				_attackRc = RectMakeCenter(_x + 90, _y - 40, 140, 60);
			}
		}
		//이미지 렌더의 최대값을 초과하면 공격렉트를 다른 위치로 치우고 E_IDLE상태로 변경시킨다
		if (_index > 15)
		{
			_attackRc = RectMakeCenter(0, 0, 0, 0);
			setState(E_IDLE);
		}

		break;

	case E_DEAD:
		_index = 0;

		//죽는 상태가 되면 알파값을 지속적으로 감소시켜 알파렌더가 되도록한다
		_alpha -= 7;

		//음수 값이 되면 이미지가 재생성되므로 음수로 내려가지않게 방지한다
		if (_alpha < 0) _alpha = 0;

		//E_DEAD상태가 된 후 일정시간이 지나면 _isDead를 true로 변경하여 벡터가 삭제되도록 한다
		if (_deadCount > 30)
		{
			_isDead = true;
			_deadCount = 0;
		}
		break;

	case E_HIT:
		//피격시 알파를 순식간에 더했다빼서 반짝거리는 효과를 추가
		_alpha -= 255;
		if (_alpha < 0) _alpha = 255;

		//E_HIT 이미지는 한개의 이미지이기때문에 _index를 0으로 고정시켜 이미지가 고정되도록 해준다
		_index = 0;

		//enemy 피격시 타격감을 위해 보고있는 위치에따라 뒤로 밀려나게 만듬
		if (_left) _x += 0.8f;
		else _x -= 0.8f;

		//enemy의 현재 체력이 0과 같거나 작아지면 E_DEAD상태로 변경
		if (_currentHP <= 0)
		{
			_alpha = 255;
			setState(E_DEAD);
		}

		//enemy가 피격 후 0.5초가 지나면 IDLE상태로 변경됨
		if (_hitCount > 30)
		{
			setState(E_IDLE);
			_hitCount = 0;
		}
		break;

	case E_GRAB:
		//E_GRAB 이미지는 한개의 이미지이기때문에 _index를 0으로 고정시켜 이미지가 고정되도록 해준다
		_index = 0;

		//E_GRAB 상태가 될때 enemy를 player의 좌표에 비교하여 위치보정을 해준다
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

		//enemy가 카메라 화면 오른쪽 밖으로 나가려고한다면 E_FLYING2로 변경
		if (_rc.right > CAMX + WINSIZEX && _flying && _left)
		{
			_alpha = 255;
			setState(E_FLYING2);
			_x -= 5;			//x좌표 위치를 보정
		}

		//enemy가 카메라 화면 왼쪽 밖으로 나가려고한다면 E_FLYING2로 변경
		if (_rc.left < CAMX && _flying && !_left && _index == 0)
		{
			_alpha = 255;
			setState(E_FLYING2);
			_x += 5;			//x좌표 위치를 보정
		}

		//enemy가 지상에있는 상태라면 _flying 상태로 변경시켜줌
		if (!_flying && _index == 0) _flying = true;
		//_flying가 true일때만 좌표를 이동시킨다(날고있는 상태이기 때문에)
		if (_flying && _left) _x += 15.5f;
		if (_flying && !_left) _x -= 15.5f;
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
			setState(E_IDLE);
			_flyDown = false;
			_flying = false;
			getDamage(20);
			if (_currentHP <= 0) setState(E_DEAD);
		}
		if (_shadow.top - _rc.bottom > 400)
		{
			_flyDown = true;
		}
	}
}

void minion2::enemyStateRender()
{
	switch (_state)
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
		if (_left) FINDIMG("enemy2_dead")->alphaFrameRender(getMemDC(), _rc.left - 110, _rc.top - 175, _index, 1, _alpha);
		else FINDIMG("enemy2_dead")->alphaFrameRender(getMemDC(), _rc.left - 60, _rc.top - 175, _index, 0, _alpha);		break;
	case E_HIT:
		if (_left) FINDIMG("enemy2_hit")->alphaFrameRender(getMemDC(), _rc.left - 50, _rc.top - 77, _index, 0, _alpha);
		else FINDIMG("enemy2_hit")->alphaFrameRender(getMemDC(), _rc.left - 175, _rc.top - 87, _index, 1, _alpha);		break;
	case E_GRAB:
		if (_left) FINDIMG("enemy2_grab")->frameRender(getMemDC(), _rc.left - 180, _rc.top - 100, _index, 0);
		else FINDIMG("enemy2_grab")->frameRender(getMemDC(), _rc.left - 50, _rc.top - 100, _index, 1);		break;
	case E_FLYING:
		if (_left) FINDIMG("enemy2_flying")->frameRender(getMemDC(), _rc.left - 30, _rc.top - 77, _index, 0);
		else FINDIMG("enemy2_flying")->frameRender(getMemDC(), _rc.left - 220, _rc.top - 77, _index, 1);	break;
	case E_FLYING2:
		if (_left) FINDIMG("enemy2_flying")->alphaFrameRender(getMemDC(), _rc.left - 30, _rc.top - 10, _index, 0, _alpha);
		else FINDIMG("enemy2_flying")->alphaFrameRender(getMemDC(), _rc.left - 60, _rc.top - 10, _index, 1, _alpha); break;
	}
}

void minion2::release()
{
}

void minion2::update()
{
	_rc = RectMakeCenter(_x, _y, 50, 200);
	enemyState();

	//상태에 따라 그림자의 크기를 다르게하여 그려줍니다
	if (_state == E_IDLE || _state == E_WALK || _state == E_WALK2 || _state == E_ATK || _state == E_HIT)
		_shadow = RectMakeCenter(_rc.left + 25, _rc.bottom + 10, 200, 50);

	if (_state == E_GRAB || _state == E_FLYING) _shadow = RectMakeCenter(_rc.left + 25, _rc.bottom + 10, 150, 50);
}

void minion2::render()
{
	if(_state != E_DEAD) fillColorEllipse(40, 40, 40, _shadow);
	enemyStateRender();
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _rc);
		Rectangle(getMemDC(), _attackRc);
	}
}

