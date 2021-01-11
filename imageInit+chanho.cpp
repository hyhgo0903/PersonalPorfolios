#include "stdafx.h"
#include "playGround.h"

// 각종 이미지매니저 추가는 여기서

void playGround::imageInitChanho()
{
	//이거는 예시. yoongho에 해놨으니 지워도 됨.
	//IMAGEMANAGER->addImage("맵", "image/AllStage_front.bmp", 4848, 2304, true, RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("플레이어대기", "image/player/idle.bmp", 240, 462, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어대기모션", "image/player/cidleAnimation.bmp", 792, 255, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어이동", "image/player/move.bmp", 1368, 522, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어대시", "image/player/dash.bmp", 768, 480, 4, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("플레이어슬라이딩", "image/player/slide.bmp", 306, 462, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("플레이어태클", "image/player/tackle.bmp", 192, 444, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어점프", "image/player/jump.bmp", 231, 498, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어공격", "image/player/attack1.bmp", 1104, 426, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어공격1-1", "image/player/attack1-1.bmp", 480, 444, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어공격1-2", "image/player/attack1-2.bmp", 732, 618, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어공격1-3", "image/player/attack1-3.bmp", 660, 522, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어공격2-1", "image/player/attack2-1.bmp", 576, 534, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어공격2-2", "image/player/attack2-2.bmp", 570, 456, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어공격2-3", "image/player/attack2-3.bmp", 1161, 426, 3, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("플레이어점프공격", "image/player/jumpAttack.bmp", 588, 750, 2, 2, true, RGB(255, 0, 255));
}