#include "stdafx.h"
#include "playGround.h"

// 각종 이미지매니저 추가는 여기서

void playGround::imageInitDeokho()
{
	IMAGEMANAGER->addImage("공", "image/item_bmp/ball_basic.bmp", 47, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("찌그러진공", "image/item_bmp/ball_strach.bmp", 98, 33, true, RGB(255, 0, 255));

}