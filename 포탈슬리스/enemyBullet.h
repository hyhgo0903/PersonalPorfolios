#pragma once
#include "bullets.h"

class enemyBullet :	public bullets
{
public:
	enemyBullet() {};
	~enemyBullet() {};

	virtual HRESULT init(int ID, float x, float y, int left, float angle);
	virtual void release();
	virtual void update();
	virtual void render();
};

