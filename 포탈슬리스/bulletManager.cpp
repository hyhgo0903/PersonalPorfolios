#include "stdafx.h"
#include "bulletManager.h"
#include "playerManager.h"
#include "enemyManager.h"

HRESULT bulletManager::init()
{
	_explosionEffect = new effect;
	_explosionEffect->init(IMAGEMANAGER->findImage("폭발"), 32, 62, 1, 0.5f);
	EFFECTMANAGER->addEffect("explosion", "image/explosion.bmp", 832, 62, 32, 62, 1.0f, 0.3f, 300);
	_bulletScore = 0;
	_wind = 0.f;
	return S_OK;
}

void bulletManager::release()
{
	_vEBullet.clear();	_vPBullet.clear();
	SAFE_RELEASE(_explosionEffect)
	SAFE_DELETE(_explosionEffect);
}

void bulletManager::update()
{
	pBulletCollision();
	eBulletCollision();
	guidedMissile();
	EFFECTMANAGER->update();
	_explosionEffect->update();
	for (int i = 0; i < _vEBullet.size(); ++i)
	{
		_vEBullet[i]->update(); // 업데이트 돌려주구유
		_vEBullet[i]->setWind(_wind); // 바람입력
	}
	for (int i = 0; i < _vPBullet.size(); ++i)
	{
		_vPBullet[i]->update(); // 업데이트 돌려주구유
		_vPBullet[i]->setWind(_wind); // 바람입력
	}
	bool recheck;
	recheck = true;
	while (recheck)
	{
		recheck = false;// 이즈파이어 없으면 무난하게 false인상태로 반복문이 끝난다
		for (int i = 0; i < _vEBullet.size(); ++i)
		{
			if (!(_vEBullet[i]->getIsFire()))
			{ // 이즈파이어가 꺼졌다면 지워준다
				SAFE_RELEASE(_vEBullet[i]);
				SAFE_DELETE(_vEBullet[i]);
				_vEBullet.erase(_vEBullet.begin() + i);
				recheck = true; // 반복문 중간에 나간거면 리체크해줘야한다.
				break;
			}
		}
	}
	recheck = true;
	while (recheck)
	{
		recheck = false;// 이즈파이어 없으면 무난하게 false인상태로 반복문이 끝난다
		for (int i = 0; i < _vPBullet.size(); ++i)
		{
			if (!(_vPBullet[i]->getIsFire()))
			{ // 이즈파이어가 꺼졌다면 지워준다
				SAFE_RELEASE(_vPBullet[i]);
				SAFE_DELETE(_vPBullet[i]);
				_vPBullet.erase(_vPBullet.begin() + i);
				recheck = true;
				break;
			}
		}
	}	
}

void bulletManager::render()
{
	for (int i = 0; i < _vEBullet.size(); ++i)
	{
		_vEBullet[i]->render();
	}
	for (int i = 0; i < _vPBullet.size(); ++i)
	{
		_vPBullet[i]->render();
	}
	EFFECTMANAGER->render();
	_explosionEffect->render();
}

void bulletManager::playerFire(int ID, float x, float y, float angle, float power, float damageCoefficient)
{ // 탄알의 종류, 중점의 x좌표, 중점의 y좌표, 각도, 파워, 데미지계수(탄알의 종류에 지정된 데미지에 곱해짐)
	if (_vPBullet.size() >= BULLETMAX) return;					// 탄알 수 제한보다 벡터사이즈가 크면 리턴
	playerBullet* pbullet;										// 객체를 생성합니다
	pbullet = new playerBullet;
	pbullet->init(ID, x, y, angle, power, damageCoefficient);	// 설정값대로 초기화합니다
	_vPBullet.push_back(pbullet);								// 벡터에 넣어줍니다
}

void bulletManager::enemyFire(int ID, float x, float y, int left, float angle)
{
	if (_vEBullet.size() >= BULLETMAX) return;
	enemyBullet* ebullet;
	ebullet = new enemyBullet;
	ebullet->init(ID, x, y, left, angle);
	_vEBullet.push_back(ebullet);
}