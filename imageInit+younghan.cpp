#include "stdafx.h"
#include "playGround.h"

void playGround::imageInitYounghan()
{
	//적 이미지 관련 이미지 추가
	IMAGEMANAGER->addFrameImage("enemy1_idle", "image/enemy1(ball)/enemy1_idle.bmp", 810, 360, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy1_walk", "image/enemy1(ball)/enemy1_walk.bmp", 1800, 390, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy1_atk", "image/enemy1(ball)/enemy1_atk.bmp", 990, 660, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy1_dead", "image/enemy1(ball)/enemy1_dead.bmp", 2160, 390, 8, 2, true, RGB(255, 0, 255));
}