#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::hyunjeonghoInit()
{
	IMAGEMANAGER->addImage("체력바뒤", "image/ui/progress_Bar/Hp_Bar_Blocked.bmp", 50, 6, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("초록피", "image/ui/progress_Bar/full_Hp_Blocked.bmp", 50, 6, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("노랑피", "image/ui/progress_Bar/medium_Hp_Blocked.bmp", 50, 6, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("빨간피", "image/ui/progress_Bar/low_Hp_Blocked.bmp", 50, 6, false, RGB(255, 0, 255));
	imgLoaded();

	//################## 디아블로 ###################################################################
	IMAGEMANAGER->addFrameImage("디아블로 서기", "image/unit/diablo/Diablo_walk.bmp", 1631, 1352, 8, 8, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("디아블로 걷기", "image/unit/diablo/Diablo_walk.bmp", 1631, 1352, 8, 8, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("디아블로 소환", "image/unit/diablo/Diablo_Summon.bmp", 2000, 2370, 8, 10, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("디아블로 죽음", "image/unit/diablo/Diablo_Summon.bmp", 2000, 2370, 8, 10, true, RGB(255, 0, 255));
	imgLoaded();

	//################## 해골병사 ###################################################################
	IMAGEMANAGER->addFrameImage("해골병사 서기", "image/unit/diablo_Bone/Bone_walk.bmp", 440, 220, 8, 4, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("해골병사 걷기", "image/unit/diablo_Bone/Bone_walk.bmp", 440, 220, 8, 4, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("해골병사 공격", "image/unit/diablo_Bone/Bone_Attack.bmp", 400, 450, 8, 9, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("해골병사 죽음", "image/unit/diablo_Bone/Bone_Dead.bmp", 640, 560, 8, 7, true, RGB(255, 0, 255));
	imgLoaded();
}