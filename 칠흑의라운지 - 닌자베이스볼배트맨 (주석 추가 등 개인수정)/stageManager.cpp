#include "stdafx.h"
#include "stageManager.h"

stageManager::stageManager()
{
}

stageManager::~stageManager()
{
}

HRESULT stageManager::init()
{
	// 추가하는 함수. 나중에 배치할떄 쓰고 지금은 지워도 됨

	// 스테이지 1 쓰레기통 위치지정. (등장조건 불필요)
	createTrashCan(600, CAMY + 500);
	createTrashCan(1450, CAMY + 450);
	createTrashCan(1300, CAMY + 650);

	// 보스스테이지 쓰레기통 위치지정.  (등장조건 불필요)
	createTrashCan(4400, 450);
	createTrashCan(4500, 700);

	// 보스 등장 전 의자 위치지정. (등장조건 불필요)
	for (int i = 0; i < 3; i++)
	{
		//if (!_VObject[i]->getIsBossOn()) // 보스 등장 전이라면. 
		//{
			createChair(3100 + (i * 360), 465);
		//}
	}

	//// 보스 등장 후 의자 위치지정.  (등장조건 필요함 - 보스가 등장하게되면 나타나게 된다.) 보스 등장하고 만들기. 
	/*for (int i = 0; i < 3; i++)
	{
		createChair(3135 + (i * 360), 490);
		for (int j = 0; j < 3; j++)
		{
			createChair(3300 + (j * 355), 760);
		}
	}*/


	return S_OK;
}

void stageManager::release()
{
	_VObject.clear(); // 벡터자체를 없애버리는 함수.
}

void stageManager::update()
{
	for (int i = 0; i < _VObject.size(); ++i)
	{
		_VObject[i]->update();
	}


	for (int i = 0; i < _VObject.size(); ++i)
	{
		if (!_VObject[i]->getIsFire()) // _isFire확인
		{
			removeObject(i);
			break;
		}
	}
	

}

void stageManager::render()
{ // 오브젝트 벡터들은 제트오더에서 한번에 그릴거임
}

//----------------------------------------------------------------------------------------------------------
// 1-1.충돌함수에서 충돌여부 확인 > 2.확인된다면 removeObject()로 와서 쓰레기통인지 판별 > 쓰레기통이 맞다면 지워준다는 계획.
// 2-1.충돌함수에서 충돌여부 확인 > 2.확인된다면 removeObject()로 와서 의자인지 판별 > 의자가 맞다면 && 플레이어가 공격중이라면 지워준다.
// 2-1.충돌함수에서 충돌여부 확인 > 2.확인된다면 removeObject()로 와서 의자인지 판별 > 의자가 맞다면 && 플레이어가 상호작용중이라면 방패로 변신.

// 충돌 시 일어날 일들.
void stageManager::removeObject(int arrNum) // arrNum여기에 i가 들어가게 된다. 
{
	//외부에서 특정 애를 지워라고해서 그것만 지우는 함수
	// id로 찾기 (각 클래스(의자, 쓰레기통)마다 id를 붙여준다. (의자 = 0, 쓰레기통 = 1) 그리고 이 id를 보고 의자인지 쓰레기통인지 확인하게된다.)
	if (_VObject[arrNum]->getId() == 0) // 0 > 의자이다.
	{
		_VObject.erase(_VObject.begin() + arrNum);
	}
	else if (_VObject[arrNum]->getId() == 1) // 1 > 쓰레기통이다. 
	{
		_VObject.erase(_VObject.begin() + arrNum);
	}



	/*
	if (_FINDIMG("쓰레기통"))
	{
		_VObject.erase(_VObject.begin() + arrNum);
	}
	if (_img == FINDIMG("의자"))
	{
		if (플레이어가 공격상태일때)
		{
			// 의자가 사라진다. 
			_VObject.erase(_VObject.begin() + arrNum);
		}

		if (플레이어가 의자에게 상호작용키를 눌렀을때)
		{
			// 의자가 방패가 된다. (의자의 모양이 뒤집어지며 플레이어의 랙트와 붙게된다. (플레이어가 오른쪽일 때, 왼쪽일 때 의자의 방향도 달라진다.)) 
		}
	}
	*/
}

void stageManager::createChair(float x, float y)
{
	chair* vchair;
	vchair = new chair;
	vchair->init(x, y); // 의자를 만들어서 이닛하라. 
	_VObject.push_back(vchair); // 벡터안에 vchair(의자를 init한 객체하나)를 집어넣어라.
}

void stageManager::createTrashCan(float x, float y)
{
	trashCan* vTrashCan;
	vTrashCan = new trashCan;
	vTrashCan->init(x, y);
	_VObject.push_back(vTrashCan);
}
