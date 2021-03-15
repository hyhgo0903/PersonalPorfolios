#include "stdafx.h"
#include "playGround.h"

// °¢Á¾ ÀÌ¹ÌÁö¸Å´ÏÀú Ãß°¡´Â ¿©±â¼­

void playGround::imageInitYoongho()
{
	IMAGEMANAGER->addImage("¸Ê", "image/AllStage_front.bmp", 4848, 2304, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("Ã¢¹®¹è°æ", "image/ui/airstageback.bmp", 1024, 704, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("±âµÕ", "image/ui/column.bmp", 77, 769, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼¿·º¹è°æ", "image/ui/selectbackground.bmp", 957, 674, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¼¿·ºÄ¿¼­", "image/ui/selectcursor.bmp", 96, 96, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼¿·ºÄ³¸¯", "image/ui/selectcharacter.bmp", 1024, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¼¿·º·¹µå", "image/ui/selectred.bmp", 480, 404, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÃÊ·Ï¼ýÀÚ", "image/ui/numbertime.bmp", 450, 45, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÇÏ¾á¼ýÀÚ", "image/ui/number.bmp", 240, 24, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("³ë¶õ¼ýÀÚ", "image/ui/numberscore.bmp", 240, 24, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÇÃ·¹ÀÌ¾îÃ¼·Â¹Ù", "image/ui/hpbar.bmp", 132, 18, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÇÃ·¹ÀÌ¾îui", "image/ui/playerui.bmp", 213, 102, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ÄÆ¾À·çÇÁ¹è°æ", "image/ui/cutsceneback.bmp", 1538, 410, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÄÆ¾ÀÄ³¸¯", "image/ui/cutscenefront.bmp", 1024, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÄÆ¾À¹è°æ", "image/ui/cutscenebackground.bmp", 1024, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÄÆ¾À´ë»çÃ¢", "image/ui/cutscenedialogback.bmp", 1024, 204, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÄÆ¾À´ë»ç1", "image/ui/cutscenedialog1.bmp", 664, 28, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("ÄÆ¾À´ë»ç2", "image/ui/cutscenedialog2.bmp", 818, 26, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("ÄÆ¾À´ë»ç3", "image/ui/cutscenedialog3.bmp", 459, 27, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("ÄÆ¾À·¹µå", "image/ui/cutscenered.bmp", 75, 83, false, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("»¡ÇÇÀÏ¶§", "image/ui/playericon.bmp", 126, 72, 2, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("º¸½ºÃ¼·Â¹Ù", "image/ui/bossbar.bmp", 576, 96, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("±×³ÉÅØ½ºÆ®", "image/ui/text.bmp", 864, 96, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("º¸½ºÅØ½ºÆ®", "image/ui/bosstext.bmp", 168, 24, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("ÇÃ·¹ÀÌ¾îÁ×À½", "image/player/dead.bmp", 1665, 588, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("º¼·ý¹Ù", "hpBarTop.BMP", 53, 5, false, RGB(255, 0, 255));
}