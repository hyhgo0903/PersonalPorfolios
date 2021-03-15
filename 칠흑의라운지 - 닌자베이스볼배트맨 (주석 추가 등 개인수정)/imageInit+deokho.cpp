#include "stdafx.h"
#include "playGround.h"
#define MAGENTA RGB(255,0,255)
#define ADDIMG IMAGEMANAGER->addImage
#define ADDFRAME IMAGEMANAGER->addFrameImage
// 각종 이미지매니저 추가는 여기서

void playGround::imageInitDeokho()
{
	IMAGEMANAGER->addImage("공", "image/item_bmp/ball_basic.bmp", 47, 45, true, MAGENTA);
	IMAGEMANAGER->addImage("찌그러진공", "image/item_bmp/ball_strach.bmp", 98, 33, true, RGB(255, 0, 255));
	ADDIMG("배트", "image/item_bmp/bat.bmp", 100, 97, true, MAGENTA);

	IMAGEMANAGER->addImage("피자", "image/item_bmp/pizza.bmp", 104, 57, true, RGB(255, 0, 255));
	ADDIMG("주스", "image/item_bmp/juice.bmp", 38, 70, true, MAGENTA);
	ADDIMG("감튀", "image/item_bmp/fries.bmp", 54, 94, true, MAGENTA);
	ADDIMG("햄버거", "image/item_bmp/hamberger.bmp", 56, 44, true, MAGENTA);
	ADDIMG("푸딩", "image/item_bmp/pudding.bmp", 63, 63, true, MAGENTA);
	ADDIMG("씨리얼", "image/item_bmp/cereal.bmp", 83, 72, true, MAGENTA);

	ADDFRAME("베이스", "image/item_bmp/base_angle.bmp", 488, 61, 8, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("폭탄", "image/item_bmp/bomb_angle.bmp", 560, 70, 8, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("폭발", "image/item_bmp/bombEffect.bmp", 1035, 171, 115, 171, 3, 0.1f, 20);
	EFFECTMANAGER->addEffect("라이프업", "image/ui/LIFE_UP.bmp", 1372, 102, (1372 / 4), 102, 2, 0.1f, 10);
}