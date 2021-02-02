#include "stdafx.h"
#include "loadingScene.h"
#define ADDF IMAGEMANAGER->addFrameImage
#define MGT RGB(255,0,255)
#define ADDS SOUNDMANAGER->addSound
void loadingScene::deokhoInit()
{
	ADDS("비숍생성", "sound/BishopBirth.wav", false, false); 
	soundLoaded();
	ADDS("비숍공격", "sound/BishopAtk.wav", false, false);
	soundLoaded();
	ADDS("비숍사망", "sound/BishopDie.wav", false, false);
	soundLoaded();

	ADDS("저글링생성", "sound/ZerglingBirth.wav", false, false);
	soundLoaded();
	ADDS("저글링공격", "sound/ZerglingAtk.wav", false, false);
	soundLoaded();
	ADDS("저글링죽음", "sound/ZerglingDie.wav", false, false);
	soundLoaded();

	ADDS("마린생성", "sound/MarineBirth.wav", false, false);
	soundLoaded();
	ADDS("마린공격", "sound/MarineAtk.wav", false, false);
	soundLoaded();
	ADDS("마린사망", "sound/MarineDie.wav", false, false);
	soundLoaded();

	ADDS("템플러생성", "sound/TemplarBirth.wav", false, false);
	soundLoaded();
	ADDS("템플러사망", "sound/TemplarDie.wav", false, false);
	soundLoaded();
	ADDS("템플러공격", "sound/TemplarAtk.wav", false, false);
	soundLoaded();

	ADDS("어그로맨생성", "sound/CivilianBirth.wav", false, false);
	soundLoaded();
	ADDS("어그로맨사망", "sound/CivilianDie.wav", false, false);
	soundLoaded();
	ADDS("어그로맨공격", "sound/CivilianAtk.wav", false, false);
	soundLoaded();

	ADDS("고스트생성", "sound/GhostBirth.wav", false, false);
	soundLoaded();
	ADDS("고스트공격", "sound/GhostAtk.wav", false, false);
	soundLoaded();
	ADDS("고스트사망", "sound/GhostDie.wav", false, false);
	soundLoaded();


	ADDF("마린이동파랑", "image/unit/Marine/Marine_Walk_Blue.bmp", 288, 256, 9, 8, true, MGT);
	imgLoaded();
	ADDF("마린기본파랑", "image/unit/Marine/Marine_Idle_Blue.bmp", 32, 256, 1, 8, true, MGT);
	imgLoaded();
	ADDF("마린공격파랑", "image/unit/Marine/Marine_Attack_Blue.bmp", 288, 288, 8, 8, true, MGT);
	imgLoaded();
	ADDF("마린죽음파랑", "image/unit/Marine/Marine_Dead_Blue.bmp", 472, 36, 8, 1, true, MGT);
	imgLoaded();
	ADDF("마린이동빨강", "image/unit/Marine/Marine_Walk_Red.bmp", 288, 256, 9, 8, true, MGT);
	imgLoaded();
	ADDF("마린기본빨강", "image/unit/Marine/Marine_Idle_Red.bmp", 32, 256, 1, 8, true, MGT);
	imgLoaded();
	ADDF("마린공격빨강", "image/unit/Marine/Marine_Attack_Red.bmp", 288, 288, 8, 8, true, MGT);
	imgLoaded();
	ADDF("마린죽음빨강", "image/unit/Marine/Marine_Dead_Red.bmp", 472, 36, 8, 1, true, MGT);
	imgLoaded();
}