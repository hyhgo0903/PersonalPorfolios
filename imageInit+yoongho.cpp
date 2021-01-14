#include "stdafx.h"
#include "playGround.h"

// 각종 이미지매니저 추가는 여기서

void playGround::imageInitYoongho()
{
	IMAGEMANAGER->addImage("맵", "image/AllStage_front.bmp", 4848, 2304, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("창문배경", "image/ui/airstageback.bmp", 1024, 704, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("기둥", "image/ui/column.bmp", 77, 769, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("셀렉배경", "image/ui/selectbackground.bmp", 957, 674, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("셀렉커서", "image/ui/selectcursor.bmp", 96, 96, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("셀렉캐릭", "image/ui/selectcharacter.bmp", 1024, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("셀렉레드", "image/ui/selectred.bmp", 480, 404, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("초록숫자", "image/ui/numbertime.bmp", 450, 45, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("하얀숫자", "image/ui/number.bmp", 240, 24, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("노란숫자", "image/ui/numberscore.bmp", 240, 24, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레이어체력바", "image/ui/hpbar.bmp", 132, 18, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레이어ui", "image/ui/playerui.bmp", 213, 102, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("컷씬루프배경", "image/ui/cutsceneback.bmp", 1538, 410, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("컷씬캐릭", "image/ui/cutscenefront.bmp", 1024, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("컷씬배경", "image/ui/cutscenebackground.bmp", 1024, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("컷씬대사창", "image/ui/cutscenedialogback.bmp", 1024, 204, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("컷씬대사1", "image/ui/cutscenedialog1.bmp", 664, 28, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("컷씬대사2", "image/ui/cutscenedialog2.bmp", 818, 26, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("컷씬대사3", "image/ui/cutscenedialog3.bmp", 459, 27, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("컷씬레드", "image/ui/cutscenered.bmp", 75, 83, false, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("빨피일때", "image/ui/playericon.bmp", 126, 72, 2, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스체력바", "image/ui/bossbar.bmp", 576, 96, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("그냥텍스트", "image/ui/text.bmp", 864, 96, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("보스텍스트", "image/ui/bosstext.bmp", 168, 24, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("플레이어죽음", "image/player/dead.bmp", 1665, 588, 5, 2, true, RGB(255, 0, 255));

}