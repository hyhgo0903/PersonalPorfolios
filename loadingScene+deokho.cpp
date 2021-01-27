#include "stdafx.h"
#include "loadingScene.h"
#define ADDF IMAGEMANAGER->addFrameImage
#define MGT RGB(255,0,255)
void loadingScene::deokhoInit()
{
	ADDF("¸¶¸°ÀÌµ¿ÆÄ¶û", "image/unit/Marine/Marine_Walk_Blue.bmp", 288, 256, 9, 8, true, MGT);
	imgLoaded();
	ADDF("¸¶¸°±âº»ÆÄ¶û", "image/unit/Marine/Marine_Idle_Blue.bmp", 32, 256, 1, 8, true, MGT);
	imgLoaded();
	ADDF("¸¶¸°°ø°ÝÆÄ¶û", "image/unit/Marine/Marine_Attack_Blue.bmp", 288, 288, 8, 8, true, MGT);
	imgLoaded();
	ADDF("¸¶¸°Á×À½ÆÄ¶û", "image/unit/Marine/Marine_Dead_Blue.bmp", 472, 36, 8, 1, true, MGT);
	imgLoaded();
	ADDF("¸¶¸°ÀÌµ¿»¡°­", "image/unit/Marine/Marine_Walk_Red.bmp", 288, 256, 9, 8, true, MGT);
	imgLoaded();
	ADDF("¸¶¸°±âº»»¡°­", "image/unit/Marine/Marine_Idle_Red.bmp", 32, 256, 1, 8, true, MGT);
	imgLoaded();
	ADDF("¸¶¸°°ø°Ý»¡°­", "image/unit/Marine/Marine_Attack_Red.bmp", 288, 288, 8, 8, true, MGT);
	imgLoaded();
	ADDF("¸¶¸°Á×À½»¡°­", "image/unit/Marine/Marine_Dead_Red.bmp", 472, 36, 8, 1, true, MGT);
	imgLoaded();
}