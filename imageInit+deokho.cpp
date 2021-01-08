#include "stdafx.h"
#include "playGround.h"

// °¢Á¾ ÀÌ¹ÌÁö¸Å´ÏÀú Ãß°¡´Â ¿©±â¼­

void playGround::imageInitDeokho()
{
	IMAGEMANAGER->addImage("°ø", "image/item_bmp/ball_basic.bmp", 47, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Âî±×·¯Áø°ø", "image/item_bmp/ball_strach.bmp", 98, 33, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÆøÅº", "image/item_bmp/bomb_angle.bmp", 560, 70, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Æø¹ßÀÌÆåÆ®", "image/item_bmp/bombEffect.bmp", 1035, 171, 9, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("Æø¹ß", "image/item_bmp/bombEffect.bmp", 1035, 171, 115, 171, 3, 0.1f, 20);
}