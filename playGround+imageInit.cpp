#include "stdafx.h"
#include "playGround.h"

// 각종 이미지매니저 추가는 여기서

void playGround::imageInit()
{
	// 맵관련
	IMAGEMANAGER->addImage("맵", "image/AllStage_front.bmp", 4848, 2304, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("창문배경", "image/ui/airstageback.bmp", 1024, 704, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("기둥", "image/ui/column.bmp", 77, 769, false, RGB(255, 0, 255));
}