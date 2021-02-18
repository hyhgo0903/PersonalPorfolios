#include "stdafx.h"
#include "bulletManager.h"
#include "playerManager.h"
#include "enemyManager.h"

void bulletManager::pBulletCollision()
{ // 내 포탄이 적(포문돌림)에게 맞았다
	RECT temp;
	for (int i = 0; i < _vPBullet.size(); ++i)
	{
		for (int j = 0; j < _em->getVFEnemy().size(); j++) // 공중유닛에 대한 반복문을 돌립니다.
		{
			if (_em->getVFEnemy()[j]->getAlpha() < 255) continue; // 사라지는 중인건 안떄린다
			if (IntersectRect(&temp, &_em->getVFEnemy()[j]->getRect(),
				&_vPBullet[i]->getRect()) && _vPBullet[i]->getDuration() >= 0) // 부딪?
			{ // 0 이상 조건은 음수일땐 안 맞도록 하기 위해서(4발탄 자체 쿨타임)
				--_vPBullet[i]->getHits(); // 0이되면 isfire가 꺼지게 돼 있음
				_vPBullet[i]->getDuration() = -3; // (4발탄) 터진후 자체 쿨다운을 부여
				_em->getVFEnemy()[j]->dealDamage(_vPBullet[i]->getDamage()); // 데미지만큼 딜
				EFFECTMANAGER->play("explosion", temp.left, temp.top - 31); // 임팩트있는 이펙트
				++_bulletScore;
			}

		}
		for (int j = 0; j < _em->getVGEnemy().size(); j++) // 지상유닛에 대한 반복문을 돌립니다.
		{
			if (_em->getVGEnemy()[j]->getAlpha() < 255) continue; // 세부적인건 위와 같음
			if (IntersectRect(&temp, &_em->getVGEnemy()[j]->getRect(),
				&_vPBullet[i]->getRect()) && _vPBullet[i]->getDuration() >= 0)
			{
				--_vPBullet[i]->getHits();
				_vPBullet[i]->getDuration() = -3;
				_em->getVGEnemy()[j]->dealDamage(_vPBullet[i]->getDamage());
				EFFECTMANAGER->play("explosion", temp.left, temp.top - 31);
				++_bulletScore;
			}
		}
	}	
}

void bulletManager::eBulletCollision()
{ // 적포탄에 맞았다
	RECT temp;
	for (int i = 0; i < _vEBullet.size(); ++i)
	{
		if (IntersectRect(&temp,&_pm->getRect(),&_vEBullet[i]->getRect()))
		{
			_vEBullet[i]->getIsFire() = false;
			if (!_pm->getIsInvincible()) // 무적상태였으면 데미지 무시하고 파이어만 꺼줍니다
			{
				_pm->dealDamage(_vEBullet[i]->getDamage());
				EFFECTMANAGER->play("explosion", temp.left, temp.top - 31);
				_pm->setIsBlink();
			}
			break; // 이건 왜하냐하면 플레이어는 한번에 하나씩 맞게하고 싶기 때문이죠
		}
	}
}

void bulletManager::guidedMissile()
{
	for (int i = 0; i < _vPBullet.size(); ++i)
	{
		if ((_vPBullet[i]->getID() != 3 && _vPBullet[i]->getID() != 7) || _vPBullet[i]->getDuration() < 10) continue; // 유도 아니면 연산 X
		_vPBullet[i]->getChase() = false; // 유도 감지를 못하면 계속 false로 남아있습니다.
		float angle;			// 유도하면 각도계산해서 x,y속도 수정
		
		for (int j = 0; j < _em->getVFEnemy().size(); j++)
		{
			if (_em->getVFEnemy()[j]->getAlpha() < 255) continue; // 사라지는 중인건 안쫓는다
			RECT rc1 = _vPBullet[i]->getRect();
			RECT rc2 = _em->getVFEnemy()[j]->getRect();
			if (getDistance((rc1.left + rc1.right) / 2, (rc1.top + rc1.bottom) / 2, (rc2.left + rc2.right) / 2,
				(rc2.top + rc2.bottom) / 2) < 120) // 중점 기준으로 거리 내에 있으면!
			{
				angle = getAngle((rc1.left + rc1.right) / 2, (rc1.top + rc1.bottom) / 2, (rc2.left + rc2.right) / 2,
					(rc2.top + rc2.bottom) / 2);
				_vPBullet[i]->getChase() = true; // 추적중임을 켜줌
				_vPBullet[i]->setXSpd(8*cosf(angle));
				_vPBullet[i]->setYSpd(8 * -sinf(angle));
				_vPBullet[i]->setTargetRc(rc2);
				break;
			}
		}
		for (int j = 0; j < _em->getVGEnemy().size(); j++)
		{
			if (_em->getVGEnemy()[j]->getAlpha() < 255) continue; // 사라지는 중인건 안쫓는다
			if (_vPBullet[i]->getChase()) break;
			RECT rc1 = _vPBullet[i]->getRect();
			RECT rc2 = _em->getVGEnemy()[j]->getRect();
			if (getDistance((rc1.left + rc1.right) / 2, (rc1.top + rc1.bottom) / 2, (rc2.left + rc2.right) / 2,
				(rc2.top + rc2.bottom) / 2) < 120)
			{
				angle = getAngle((rc1.left + rc1.right) / 2, (rc1.top + rc1.bottom) / 2, (rc2.left + rc2.right) / 2,
					(rc2.top + rc2.bottom) / 2);
				_vPBullet[i]->getChase() = true;
				_vPBullet[i]->setXSpd(8 * cosf(angle));
				_vPBullet[i]->setYSpd(8 * -sinf(angle));
				_vPBullet[i]->setTargetRc(rc2);
				break;
			}
		}
	}
}
