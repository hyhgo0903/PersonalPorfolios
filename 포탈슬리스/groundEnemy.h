#pragma once
#include "enemy.h"

enum enemyState
{
	IDLE, WALK, ATTACK
};

class groundEnemy : public enemy
{
private:
	int _left; // 왼쪽이면 1이 되고 오른쪽이면 0. 0보다 클때 미사일발사시 x속도에 -1을 곱해줌	
	int _playerX; // 플레이어의 위치
	enemyState _state;
	float _ySpd; // 중력껏 떨구려고
	int _probeY; // 픽셀충돌용
	int _destX; // 목적지
	bool _offGround; // 땅에 없는지

public:
	groundEnemy() {};
	~groundEnemy() {};

	virtual HRESULT init(int ID, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void pixelCollision();
	void frameXUpdate();
	void stateChange();
	void stateRender();
	void fireReady();
	void groundMove();

	inline int getLeft() { return _left; }
	inline void setPlayerX(int playerX) { _playerX = playerX; }
};

