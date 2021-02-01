#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::chanhoInit()
{
	IMAGEMANAGER->addFrameImage("·¹µåºñ¼ó´ë±â", "image/unit/bishop/redBishopIdle.bmp", 100, 24, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("·¹µåºñ¼óÀÌµ¿", "image/unit/bishop/redBishopWalk.bmp", 100, 186, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("·¹µåºñ¼óÈú", "image/unit/bishop/redBishopHeal.bmp", 55, 117, 4, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("·¹µåºñ¼óÁ×À½", "image/unit/bishop/redBishopDead.bmp", 83, 15, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("ºí·çºñ¼ó´ë±â", "image/unit/bishop/blueBishopIdle.bmp", 100, 24, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºí·çºñ¼óÀÌµ¿", "image/unit/bishop/blueBishopWalk.bmp", 100, 186, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºí·çºñ¼óÈú", "image/unit/bishop/blueBishopHeal.bmp", 55, 117, 4, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºí·çºñ¼óÁ×À½", "image/unit/bishop/blueBishopDead.bmp", 83, 15, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Èú", "image/sne/healEffect.bmp", 2016, 96, 21, 1, true, RGB(255, 0, 255));
}