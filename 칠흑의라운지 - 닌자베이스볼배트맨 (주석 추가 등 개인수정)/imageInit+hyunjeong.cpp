#include "stdafx.h"
#include "playGround.h"

// 각종 이미지매니저 추가는 여기서

void playGround::imageInitHyunjeong()
{
	//이거는 예시. yoongho에 해놨으니 지워도 됨.
	//IMAGEMANAGER->addImage("맵", "image/AllStage_front.bmp", 4848, 2304, true, RGB(255,0,255));	
	IMAGEMANAGER->addImage("의자", "image/Stage_Objects/chair.bmp", 233, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쓰레기통", "image/Stage_Objects/trashCan.bmp", 110, 150, true, RGB(255, 0, 255));
}