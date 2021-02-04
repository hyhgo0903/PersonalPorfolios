#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::chanhoInit()
{
	IMAGEMANAGER->addFrameImage("·¹µåºñ¼ó´ë±â", "image/unit/bishop/redBishopIdle.bmp", 100, 24, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("·¹µåºñ¼óÀÌµ¿", "image/unit/bishop/redBishopWalk.bmp", 100, 186, 8, 8, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("·¹µåºñ¼óÈú", "image/unit/bishop/redBishopHeal.bmp", 55, 117, 4, 5, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("·¹µåºñ¼óÁ×À½", "image/unit/bishop/redBishopDead.bmp", 83, 15, 4, 1, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addFrameImage("ºí·çºñ¼ó´ë±â", "image/unit/bishop/blueBishopIdle.bmp", 100, 24, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ºí·çºñ¼óÀÌµ¿", "image/unit/bishop/blueBishopWalk.bmp", 100, 186, 8, 8, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ºí·çºñ¼óÈú", "image/unit/bishop/blueBishopHeal.bmp", 55, 117, 4, 5, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ºí·çºñ¼óÁ×À½", "image/unit/bishop/blueBishopDead.bmp", 83, 15, 4, 1, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addFrameImage("·¹µåµå·¡°ï´ë±â", "image/unit/dragon/redDragonIdle.bmp", 336, 40, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("·¹µåµå·¡°ïÀÌµ¿", "image/unit/dragon/redDragonFly.bmp", 344, 80, 8, 2, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("·¹µåµå·¡°ï°ø°İ", "image/unit/dragon/redDragonAttack.bmp", 344, 80, 8, 2, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("·¹µåµå·¡°ïÁ×À½", "image/unit/dragon/redDragonDead.bmp", 344, 40, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addFrameImage("ºí·çµå·¡°ï´ë±â", "image/unit/dragon/blueDragonIdle.bmp", 336, 40, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ºí·çµå·¡°ïÀÌµ¿", "image/unit/dragon/blueDragonFly.bmp", 344, 80, 8, 2, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ºí·çµå·¡°ï°ø°İ", "image/unit/dragon/blueDragonAttack.bmp", 344, 80, 8, 2, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ºí·çµå·¡°ïÁ×À½", "image/unit/dragon/blueDragonDead.bmp", 344, 40, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addFrameImage("Èú", "image/sne/healEffect.bmp", 2016, 96, 21, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ºÒ", "image/sne/fireEffect.bmp", 288, 32, 9, 1, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addFrameImage("ºÒ", "image/sne/fireEffect.bmp", 288, 32, 9, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ºÒ", "image/sne/fireEffect.bmp", 288, 32, 9, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ºÒ", "image/sne/fireEffect.bmp", 288, 32, 9, 1, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addImage("Á¤±Û", "image/stage/jungle.bmp", 1920, 960, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("½ÎÆã", "image/stage/cyberSpace.bmp", 1920, 960, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("´«»ê", "image/stage/snowMountain.bmp", 1920, 960, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("¿ìÁÖ", "image/stage/space.bmp", 1920, 960, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("È­»ê", "image/stage/volcano.bmp", 1920, 960, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("»ç¸·", "image/stage/wilderness.bmp", 1920, 960, false, RGB(0, 0, 0));
	imgLoaded();
}