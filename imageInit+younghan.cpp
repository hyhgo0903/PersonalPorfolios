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

	//적2
	IMAGEMANAGER->addFrameImage("enemy2_idle", "image/enemy2(bat)/idle.bmp", 330, 768, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy2_move", "image/enemy2(bat)/move.bmp", 990, 768, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy2_atk", "image/enemy2(bat)/attack.bmp", 7296, 768, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy2_hit", "image/enemy2(bat)/enemy2_hit.bmp", 291, 588, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy2_dead", "image/enemy2(bat)/dead.bmp", 219, 768, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy2_grab", "image/enemy2(bat)/enemy2_grab.bmp", 291, 588, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy2_flying", "image/enemy2(bat)/enemy2_flying.bmp", 285, 588, 1, 2, true, RGB(255, 0, 255));

	//적3
	IMAGEMANAGER->addFrameImage("enemy3_idle", "image/enemy3(card)/enemy3_idle.bmp", 390, 390, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy3_walk", "image/enemy3(card)/enemy3_walk.bmp", 975, 420, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy3_atk", "image/enemy3(card)/enemy3_atk.bmp", 990, 390, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy3_hit", "image/enemy3(card)/enemy3_hit.bmp", 195, 390, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy3_dead", "image/enemy3(card)/enemy3_dead.bmp", 840, 420, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy3_grab", "image/enemy3(card)/enemy3_grab.bmp", 195, 480, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy3_flying", "image/enemy3(card)/enemy3_flying.bmp", 210, 420, 1, 2, true, RGB(255, 0, 255));


	//보스 관련 이미지 추가
	IMAGEMANAGER->addFrameImage("boss_idle", "image/boss/boss_idle.bmp", 212, 400, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_walk", "image/boss/boss_walk.bmp", 728, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_atk", "image/boss/boss_kick.bmp", 933, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_hit", "image/boss/boss_AttackByPlayer_Side.bmp", 158, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_dead", "image/boss/boss_AttackedByPlayer_fallSpin.bmp", 832, 400, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_shakes", "image/boss/boss_shakes.bmp", 1230, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_crawl", "image/boss/boss_Crawl.bmp", 969, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_car", "image/boss/boss_withCar.bmp", 1200, 594, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_hit2", "image/boss/boss_AttackedByPlayer_downToUpAndJump.bmp", 222, 400, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_hit3", "image/boss/boss_AttackedByPlayer_downToUp.bmp", 142, 400, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_hit4", "image/boss/boss_AttackedByPlayer_rightToLeft.bmp", 192, 400, 1, 2, true, RGB(255, 0, 255));
	
}