#include "stdafx.h"
#include "playGround.h"
#define MAGENTA RGB(255,0,255)
#define ADDIMG IMAGEMANAGER->addImage
#define ADDFRAME IMAGEMANAGER->addFrameImage
// °¢Á¾ ÀÌ¹ÌÁö¸Å´ÏÀú Ãß°¡´Â ¿©±â¼­

void playGround::imageInitDeokho()
{
	IMAGEMANAGER->addImage("°ø", "image/item_bmp/ball_basic.bmp", 47, 45, true, MAGENTA);
	IMAGEMANAGER->addImage("Âî±×·¯Áø°ø", "image/item_bmp/ball_strach.bmp", 98, 33, true, RGB(255, 0, 255));
	ADDIMG("¹èÆ®", "image/item_bmp/bat.bmp", 100, 97, true, MAGENTA);

	IMAGEMANAGER->addImage("ÇÇÀÚ", "image/item_bmp/pizza.bmp", 104, 57, true, RGB(255, 0, 255));
	ADDIMG("ÁÖ½º", "image/item_bmp/juice.bmp", 38, 70, true, MAGENTA);
	ADDIMG("°¨Æ¢", "image/item_bmp/fries.bmp", 54, 94, true, MAGENTA);
	ADDIMG("ÇÜ¹ö°Å", "image/item_bmp/hamberger.bmp", 56, 44, true, MAGENTA);
	ADDIMG("Çªµù", "image/item_bmp/pudding.bmp", 63, 63, true, MAGENTA);
	ADDIMG("¾¾¸®¾ó", "image/item_bmp/cereal.bmp", 83, 72, true, MAGENTA);

	ADDFRAME("º£ÀÌ½º", "image/item_bmp/base_angle.bmp", 488, 61, 8, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("ÆøÅº", "image/item_bmp/bomb_angle.bmp", 560, 70, 8, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("Æø¹ß", "image/item_bmp/bombEffect.bmp", 1035, 171, 115, 171, 3, 0.1f, 20);
}