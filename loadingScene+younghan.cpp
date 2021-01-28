#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::younghanInit()
{
	//이미지 영역
	IMAGEMANAGER->addFrameImage("mapTiles", "image/maptool/tile512x384ver2.bmp", 0, 0, 512, 384, 8, 12, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("save1", "image/maptool/save1.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("save2", "image/maptool/save2.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("save3", "image/maptool/save3.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("load1", "image/maptool/load1.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("load2", "image/maptool/load2.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("load3", "image/maptool/load3.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("move", "image/maptool/move.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("unmove", "image/maptool/unmove.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("undo", "image/maptool/undo.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("fill", "image/maptool/fill.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("tileMenu", "image/maptool/tilemenu.bmp", 522, 394, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("open", "image/maptool/open.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("close", "image/maptool/close.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("small", "image/maptool/10x10.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("medium", "image/maptool/20x20.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("max", "image/maptool/max.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("leftBt", "image/maptool/left.bmp", 32, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("rightBt", "image/maptool/right.bmp", 32, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("tree", "image/maptool/tree.bmp", 107, 113, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("objDel", "image/maptool/objdel.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("icon_zergling", "image/icon/icon_zergling.bmp", 80, 90, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("delAll", "image/maptool/delall.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("un", "image/maptool/un.bmp", 16, 16, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("tree2", "image/maptool/tree2.bmp", 89, 115, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("tree3", "image/maptool/tree3.bmp", 84, 139, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("tree4", "image/maptool/tree4.bmp", 94, 128, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("tree5", "image/maptool/tree5.bmp", 76, 83, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ghost_move", "image/unit/ghost/ghost_move.bmp", 320, 324, 8, 9, true, RGB(255, 0, 255));
	imgLoaded();
}

