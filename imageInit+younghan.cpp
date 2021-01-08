#include "stdafx.h"
#include "playGround.h"

void playGround::imageInitYounghan()
{
	//적 관련 이미지 추가
	IMAGEMANAGER->addFrameImage("enemy1_idle", "image/enemy1(ball)/enemy1_idle.bmp", 810, 360, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy1_walk", "image/enemy1(ball)/enemy1_walk.bmp", 3000, 390, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy1_atk", "image/enemy1(ball)/enemy1_atk.bmp", 990, 660, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy1_dead", "image/enemy1(ball)/enemy1_dead.bmp", 2160, 390, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy1_hit1", "image/enemy1(ball)/enemy1_hit1.bmp", 270, 420, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy1_hit2", "image/enemy1(ball)/enemy1_hit2.bmp", 270, 330, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy1_hit3", "image/enemy1(ball)/enemy1_hit3.bmp", 270, 360, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy1_hit4", "image/enemy1(ball)/enemy1_hit4.bmp", 270, 390, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy1_grab", "image/enemy1(ball)/enemy1_grab1.bmp", 180, 390, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy1_flying", "image/enemy1(ball)/enemy1_flying.bmp", 1080, 360, 4, 2, true, RGB(255, 0, 255));

	//보스 관련 이미지 추가
	IMAGEMANAGER->addFrameImage("boss_idle", "image/boss/boss_idle.bmp", 424, 800, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_walk", "image/boss/boss_walk.bmp", 1456, 800, 4, 2, true, RGB(255, 0, 255));
}