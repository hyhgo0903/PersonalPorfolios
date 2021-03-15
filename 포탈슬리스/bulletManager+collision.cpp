#include "stdafx.h"
#include "bulletManager.h"
#include "playerManager.h"
#include "enemyManager.h"

void bulletManager::pBulletCollision()
{ // �� ��ź�� ��(��������)���� �¾Ҵ�
	RECT temp;
	for (int i = 0; i < _vPBullet.size(); ++i)
	{
		for (int j = 0; j < _em->getVFEnemy().size(); j++) 		{
			if (_em->getVFEnemy()[j]->getAlpha() < 255) continue; // ������� ���ΰ� �ȋ�����
			if (IntersectRect(&temp, &_em->getVFEnemy()[j]->getRect(),
				&_vPBullet[i]->getRect()) && _vPBullet[i]->getDuration() >= 0) // �ε�?
			{ // 0 �̻� ������ �����϶� �� �µ��� �ϱ� ���ؼ�(4��ź ��ü ��Ÿ��)
				--_vPBullet[i]->getHits(); // 0�̵Ǹ� isfire�� ������ �� ����
				_vPBullet[i]->getDuration() = -3; // (4��ź) ������ ��ü ���� �ο�(0.05�ʰ� ������)
				_em->getVFEnemy()[j]->dealDamage(_vPBullet[i]->getDamage()); // ��������ŭ ��
				EFFECTMANAGER->play("explosion", temp.left, temp.top - 31); // ����Ʈ�ִ� ����Ʈ
				++_bulletScore;
			}
		} // ���󿡳ʹ̵� ���� ����
		for (int j = 0; j < _em->getVGEnemy().size(); j++) // �������ֿ� ���� �ݺ����� �����ϴ�.
		{
			if (_em->getVGEnemy()[j]->getAlpha() < 255) continue; // �������ΰ� ���� ����
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
{ // ����ź�� �¾Ҵ�
	RECT temp;
	for (int i = 0; i < _vEBullet.size(); ++i)
	{
		if (IntersectRect(&temp,&_pm->getRect(),&_vEBullet[i]->getRect()))
		{
			_vEBullet[i]->getIsFire() = false;
			if (!_pm->getIsInvincible()) // �������¿����� ������ �����ϰ� ���̾ ���ݴϴ�
			{
				_pm->dealDamage(_vEBullet[i]->getDamage());
				EFFECTMANAGER->play("explosion", temp.left, temp.top - 31);
				_pm->setIsBlink();
			}
			break; // �̰� ���ϳ��ϸ� �÷��̾�� �ѹ��� �ϳ��� �°��ϰ� �ͱ� ��������
		}
	}
}

void bulletManager::guidedMissile()
{
	for (int i = 0; i < _vPBullet.size(); ++i)
	{
		// ��ź ������ 3, 7�� �ƴϸ�(����ź ������ �ƴϸ�) ��Ƽ��
		if ((_vPBullet[i]->getID() != 3 && _vPBullet[i]->getID() != 7) || _vPBullet[i]->getDuration() < 10) continue;
		_vPBullet[i]->getChase() = false; // ���� ������ ���ϸ� ������ ������ ��� false�� �����ֽ��ϴ�.
		float angle;			// �����ϸ� ��������ؼ� x,y�ӵ� ����		
		for (int j = 0; j < _em->getVFEnemy().size(); j++)
		{
			if (_em->getVFEnemy()[j]->getAlpha() < 255) continue; // ������� ���ΰ�(�״� �ִϸ��̼� ��) ���Ѵ´�
			RECT rc1 = _vPBullet[i]->getRect();			RECT rc2 = _em->getVFEnemy()[j]->getRect();
			if (getDistance((rc1.left + rc1.right) / 2, (rc1.top + rc1.bottom) / 2, (rc2.left + rc2.right) / 2,
				(rc2.top + rc2.bottom) / 2) < 120) // ��źRECT�� ���ʹ�RECT�� 120 �Ÿ� ���� ������!
			{
				angle = getAngle((rc1.left + rc1.right) / 2, (rc1.top + rc1.bottom) / 2, (rc2.left + rc2.right) / 2,
					(rc2.top + rc2.bottom) / 2);
				_vPBullet[i]->getChase() = true; // ���������� ����
				_vPBullet[i]->setXSpd(8*cosf(angle));		_vPBullet[i]->setYSpd(8 * -sinf(angle));
				_vPBullet[i]->setTargetRc(rc2);				break;
			}
		}
		// ���� ���ʹ̵� ���� �����ϰ� ����
		for (int j = 0; j < _em->getVGEnemy().size(); j++)
		{
			if (_em->getVGEnemy()[j]->getAlpha() < 255) continue; // ������� ���ΰ� ���Ѵ´�
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
