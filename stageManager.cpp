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
		createChair(3200 + (i * 350), 420);
	}

	//// 보스 등장 후 의자 위치지정.  (등장조건 필요함 - 보스가 등장하게되면 나타나게 된다.) 보스 등장하고, 백터 쓰는거 적응하고 만들기. 
	//for (int i = 0; i < 9; i++)
	//{
	//  for (int j = 0; j < 3; j++)
	//	{
	//		createChair(3200 + (i * 370), 420 + ( j * 120));
	//  }
	//}


	return S_OK;
}

void stageManager::release()
{
	_VObject.clear();
}

void stageManager::update()
{
	for (int i = 0; i < _VObject.size(); ++i)
	{
		_VObject[i]->update();
	}
}

void stageManager::render()
{ // 오브젝트 벡터들은 제트오더에서 한번에 그릴거임
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

