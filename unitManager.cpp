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
		if (_vUnit[i]->getState() != DEAD)_vUnit[i]->progressBarRender();
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
	zergling* zergl = new zergling;
	zergl->init(belong, x, y);
	_vUnit.push_back(zergl);
}

void unitManager::createCivilian(BELONG belong, float x, float y)
{
	civilian* civil = new civilian;
	civil->init(belong, x, y);
	_vUnit.push_back(civil);
}

void unitManager::createMarine(BELONG belong, float x, float y)
{
	marine* _marine = new marine;
	_marine->init(belong, x, y);
	_vUnit.push_back(_marine);
}

void unitManager::createTemplar(BELONG belong, float x, float y)
{
	templar* templ = new templar;
	templ->init(belong, x, y);
	_vUnit.push_back(templ);
}

void unitManager::createBishop(BELONG belong, float x, float y)
{
	bishop* bi = new bishop;
	bi->init(belong, x, y);
	_vUnit.push_back(bi);
}

void unitManager::createGhost(BELONG belong, float x, float y)
{
	ghost* gt = new ghost;
	gt->init(belong, x, y);
	_vUnit.push_back(gt);
}

void unitManager::createDiablo(BELONG belong, float x, float y)
{
	diablo* db = new diablo;
	db->init(belong, x, y);
	_vUnit.push_back(db);
}

void unitManager::createBone(BELONG belong, float x, float y)
{
	bone* bn = new bone;
	bn->init(belong, x, y);
	_vUnit.push_back(bn);
}
