#include "stdafx.h"
#include "skillNEffectManager.h"

skillNEffectManager::skillNEffectManager()
{
}

skillNEffectManager::~skillNEffectManager()
{
}

HRESULT skillNEffectManager::init()
{
	return S_OK;
}

void skillNEffectManager::release()
{
	_vSne.clear();
}

void skillNEffectManager::update()
{
	for (int i = 0; i < _vSne.size(); ++i)
	{
		_vSne[i]->update();
	}
	for (int i = 0; i < _vSne.size(); ++i)
	{
		if (_vSne[i]->getErase())
		{
			_vSne.erase(_vSne.begin() + i);
		}
	}
}

void skillNEffectManager::render()
{
	for (int i = 0; i < _vSne.size(); ++i)
	{
		_vSne[i]->render();
	}
}

void skillNEffectManager::createPsionic(S_BELONG belong, float x, float y)
{
	psionic* psi = new psionic;
	psi->init(belong, x, y);
	_vSne.push_back(psi);
}


void skillNEffectManager::createHeal(S_BELONG belong, float x, float y)
{
	heal* cure = new heal;
	cure->init(belong, x, y);
	_vSne.push_back(cure);
}

void skillNEffectManager::createThunder(S_BELONG belong, float x, float y)
{
	thunder* thd = new thunder;
	thd->init(belong, x, y);
	_vSne.push_back(thd);
}
