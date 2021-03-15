#include "stdafx.h"
#include "unitManager.h"

unitManager::unitManager()
{
}

unitManager::~unitManager()
{
}

HRESULT unitManager::init()
{
	return S_OK;
}

void unitManager::release()
{
	_vUnit.clear();
}

void unitManager::update()
{
	deadErase();
	for (int i = 0; i < _vUnit.size(); ++i)
	{
		if (!_vUnit[i]->getActive()) continue;
		_vUnit[i]->update();

		if (_vUnit[i]->getState() == DEAD)
		{ // 죽은거 타겟잡은게 있다면 풀어줘야함
			for (int j = 0; j < _vUnit.size(); ++j)
			{
				if (_vUnit[j]->getTarget() == i)
				{
					_vUnit[j]->getTarget() = -1;
				}
			}
		}
	}

	chanhoUpdate();
	deokhoUpdate();
	hyunjeongUpdate();
	yoonghoUpdate();
	younghanUpdate();
	
}

void unitManager::render()
{ // 죽은거 먼저 그려줘서 가려지게끔
	for (int i = 0; i < _vUnit.size(); ++i)
	{
		if (_vUnit[i]->getState() == DEAD)	_vUnit[i]->render();
	}
	for (int i = 0; i < _vUnit.size(); ++i)
	{
		if (_vUnit[i]->getState() != DEAD)	_vUnit[i]->render();
	}
}

void unitManager::reRender()
{ // 투명하게
	for (int i = _vUnit.size() - 1; i > -1; --i)
	{
		_vUnit[i]->reRender();
	}
}

void unitManager::deadErase()
{
	bool erased = true;
	while (erased == true)
	{ // 지웠으면 다시 와일걸려서 지움(하나씩 지우지 않도록)
		// 밑에 업데이트 나올건데 죽은거 연산하지 않도록함
		erased = false;
		for (int i = 0; i < _vUnit.size(); ++i)
		{
			if (_vUnit[i]->getErase())
			{
				for (int j = 0; j < _vUnit.size(); ++j)
				{ // i보다 큰 타겟잡고있는 놈들 땅겨주기
					if (_vUnit[j]->getTarget() > i)
					{
						_vUnit[j]->getTarget() -= 1;
					}
				}
				_vUnit.erase(_vUnit.begin() + i);
				erased = true;
				break;
			}
		}
	}
}

void unitManager::progressBarRender()
{
	Rectangle(getMemDC(), CAMX, CAMY+580, CAMX+240, CAMY+700);
	for (int i = 0; i < _vUnit.size(); ++i)
	{		
		if (_vUnit[i]->getState() != DEAD && _vUnit[i]->getHP() >= 0
			&& _vUnit[i]->getID() != 20) _vUnit[i]->progressBarRender();
	}
}

void unitManager::setActive()
{
	for (int i = 0; i < _vUnit.size(); ++i)
	{
		_vUnit[i]->getActive() = true;
	}
}

void unitManager::createZergling(BELONG belong, float x, float y)
{
	//PLAYSND("저글링생성");
	zergling* zergl = new zergling;
	zergl->init(belong, x, y);
	_vUnit.push_back(zergl);
}

void unitManager::createCivilian(BELONG belong, float x, float y)
{
	//PLAYSND("어그로맨생성");
	civilian* civil = new civilian;
	civil->init(belong, x, y);
	_vUnit.push_back(civil);
}

void unitManager::createMarine(BELONG belong, float x, float y)
{
	//PLAYSND("마린생성");
	marine* _marine = new marine;
	_marine->init(belong, x, y);
	_vUnit.push_back(_marine);
}

void unitManager::createTemplar(BELONG belong, float x, float y)
{
	//PLAYSND("템플러생성");
	templar* templ = new templar;
	templ->init(belong, x, y);
	_vUnit.push_back(templ);
}

void unitManager::createBishop(BELONG belong, float x, float y)
{
	//PLAYSND("비숍생성");
	bishop* bi = new bishop;
	bi->init(belong, x, y);
	_vUnit.push_back(bi);
}

void unitManager::createGhost(BELONG belong, float x, float y)
{
	//PLAYSND("고스트생성");
	ghost* gt = new ghost;
	gt->init(belong, x, y);
	_vUnit.push_back(gt);
}

void unitManager::createDiablo(BELONG belong, float x, float y)
{
	//PLAYSND("디아블로생성");
	diablo* db = new diablo;
	db->init(belong, x, y);
	_vUnit.push_back(db);
}

void unitManager::createskeleton(BELONG belong, float x, float y)
{
	PLAYSND("해골병사생성");
	skeleton* bn = new skeleton;
	bn->init(belong, x, y);
	_vUnit.push_back(bn);
}

void unitManager::createSkeleton(BELONG belong, float x, float y)
{
	PLAYSND("해골병사생성");
	skeleton* sk = new skeleton;
	sk->init(belong, x, y);
	_vUnit.push_back(sk);
}

void unitManager::createDragon(BELONG belong, float x, float y)
{
    dragon* dr = new dragon;
    dr->init(belong, x, y);
    _vUnit.push_back(dr);
}

void unitManager::createNaruto(BELONG belong, float x, float y)
{
    naruto* na = new naruto;
    na->init(belong, x, y);
    _vUnit.push_back(na);
}

void unitManager::createFlag(BELONG belong, float x, float y)
{
	flagUnit* fl = new flagUnit;
	fl->init(belong, x, y);
	_vUnit.push_back(fl);
}

void unitManager::createTower1(BELONG belong, float x, float y)
{
	tower1* tw1 = new tower1;
	tw1->init(belong, x, y);
	_vUnit.push_back(tw1);
}
