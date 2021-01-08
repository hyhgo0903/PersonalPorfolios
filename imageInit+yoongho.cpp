#include "stdafx.h"
#include "playGround.h"

// ∞¢¡æ ¿ÃπÃ¡ˆ∏≈¥œ¿˙ √ﬂ∞°¥¬ ø©±‚º≠

void playGround::imageInitYoongho()
{
	IMAGEMANAGER->addImage("∏ ", "image/AllStage_front.bmp", 4848, 2304, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("√¢πÆπË∞Ê", "image/ui/airstageback.bmp", 1024, 704, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("±‚µ’", "image/ui/column.bmp", 77, 769, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ºø∑∫πË∞Ê", "image/ui/selectbackground.bmp", 957, 674, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºø∑∫ƒøº≠", "image/ui/selectcursor.bmp", 96, 96, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ºø∑∫ƒ≥∏Ø", "image/ui/selectcharacter.bmp", 1024, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºø∑∫∑πµÂ", "image/ui/selectred.bmp", 480, 404, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("√ ∑œº˝¿⁄", "image/ui/numbertime.bmp", 450, 45, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("«œæ·º˝¿⁄", "image/ui/number.bmp", 240, 24, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("≥Î∂ıº˝¿⁄", "image/ui/numberscore.bmp", 240, 24, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("«√∑π¿ÃæÓ√º∑¬πŸ", "image/ui/hpbar.bmp", 132, 18, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("«√∑π¿ÃæÓui", "image/ui/playerui.bmp", 213, 102, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ƒ∆æ¿∑Á«¡πË∞Ê", "image/ui/cutsceneback.bmp", 1538, 410, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ƒ∆æ¿ƒ≥∏Ø", "image/ui/cutscenefront.bmp", 1024, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ƒ∆æ¿πË∞Ê", "image/ui/cutscenebackground.bmp", 1024, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ƒ∆æ¿¥ÎªÁ√¢", "image/ui/cutscenedialogback.bmp", 1024, 204, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ƒ∆æ¿¥ÎªÁ1", "image/ui/cutscenedialog1.bmp", 664, 28, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("ƒ∆æ¿¥ÎªÁ2", "image/ui/cutscenedialog2.bmp", 818, 26, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("ƒ∆æ¿¥ÎªÁ3", "image/ui/cutscenedialog3.bmp", 459, 27, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("ƒ∆æ¿∑πµÂ", "image/ui/cutscenered.bmp", 75, 83, false, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("ª°««¿œ∂ß", "image/ui/playericon.bmp", 240, 24, 10, 1, true, RGB(255, 0, 255));

	
}