#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::yoonghoInit()
{ // 로디드가 뭐냐면 로딩바 올리기용 함수. 이미지 추가할떄마다 넣어주길	

	SOUNDMANAGER->addSound("테란브금", "sound/treamedterran1.mp3", true, true);
	soundLoaded();
	SOUNDMANAGER->addSound("골드부족", "sound/goldlack.wav", false, false);
	soundLoaded();
	SOUNDMANAGER->addSound("배치실패", "sound/tadErr03.wav", false, false);
	soundLoaded();
	

	IMAGEMANAGER->addFrameImage("저글링이동블루", "image/unit/zergling/zerglingwalkblue.bmp", 320, 273, 8, 7, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("저글링이동퍼플", "image/unit/zergling/zerglingwalk.bmp", 320, 273, 8, 7, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("저글링공격블루", "image/unit/zergling/zerglingattackblue.bmp", 320, 195, 8, 5, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("저글링공격퍼플", "image/unit/zergling/zerglingattack.bmp", 320, 195, 8, 5, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("저글링죽음", "image/unit/zergling/zerglingdead.bmp", 455, 53, 7, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("사이오닉스톰", "image/sne/psionic.bmp", 2590, 150, 14, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("시민파랑", "image/unit/civilian/civilianwalkblue.bmp", 168, 256, 8, 8, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("시민퍼플", "image/unit/civilian/civilianwalk.bmp", 168, 256, 8, 8, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("시민죽음", "image/unit/civilian/civiliandead.bmp", 420, 37, 7, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("템플러대기퍼플", "image/unit/templar/idle.bmp", 240, 336, 8, 8, true, RGB(255, 255, 0));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("템플러대기블루", "image/unit/templar/idleblue.bmp", 240, 336, 8, 8, true, RGB(255, 255, 0));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("템플러공격퍼플", "image/unit/templar/attack.bmp", 528, 280, 8, 5, true, RGB(255, 255, 0));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("템플러공격블루", "image/unit/templar/attackblue.bmp", 528, 280, 8, 5, true, RGB(255, 255, 0));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("템플러이동퍼플", "image/unit/templar/walk.bmp", 240, 42, 8, 1, true, RGB(255, 255, 0));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("템플러이동블루", "image/unit/templar/walkblue.bmp", 240, 42, 8, 1, true, RGB(255, 255, 0));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("템플러죽음", "image/unit/templar/dead.bmp", 217, 53, 7, 1, true, RGB(255, 255, 0));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("템플러잔상", "image/unit/templar/afterimage.bmp", 240, 168, 8, 4, true, RGB(255, 255, 0));
	imgLoaded();

	IMAGEMANAGER->addImage("타이틀메뉴", "image/title.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("볼륨조절", "image/ui/vol/VolumeSet.bmp", 300, 300, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("브금조절바", "image/ui/vol/volbgmbar.bmp", 120, 29, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("효과음조절바", "image/ui/vol/voleffectbar.bmp", 120, 29, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("소리키고끄기", "image/ui/vol/volumetest.bmp", 36, 15, 2, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("씬체인지", "image/ui/scenechange.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("저장팝업", "image/maptool/savepopup.bmp", 349, 200, 1, 2, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("가이드타일", "image/maptool/guidetile.bmp", 64, 32, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addImage("딜레이바", "image/ui/progress_Bar/delaybar.bmp", 50, 3, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("플레이어깃발", "image/maptool/flagplayer.bmp", 64, 118, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("에너미깃발", "image/maptool/flagenemy.bmp", 64, 118, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("숫자", "image/ui/number.bmp", 150, 19, 10, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("달러", "image/ui/dollar.bmp", 18, 25, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("현재스테이지", "image/ui/currentstage.bmp", 60, 28, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("지급골드", "image/ui/stagegold.bmp", 200, 32, false, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addImage("배치가능", "image/ui/createable.bmp", 800, 800, true, RGB(255, 0, 255));
	imgLoaded();


	IMAGEMANAGER->addImage("정글썸", "image/stage/junglesum.bmp", 85, 43, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("싸펑썸", "image/stage/cyberSpacesum.bmp", 85, 43, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("눈산썸", "image/stage/snowMountainsum.bmp", 85, 43, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("우주썸", "image/stage/spacesum.bmp", 85, 43, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("화산썸", "image/stage/volcanosum.bmp", 85, 43, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("사막썸", "image/stage/wildernesssum.bmp", 85, 43, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("배경", "image/backGround.bmp", MAPSIZEX, MAPSIZEY, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("롤승리", "image/ui/lastVictory.bmp", 1200, 700, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("스코어", "image/ui/score.bmp", 150, 32, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("고스트펑", "image/sne/ghosteffect.bmp", 350, 33, 10, 1, true, RGB(255, 0, 255));
	imgLoaded();
}