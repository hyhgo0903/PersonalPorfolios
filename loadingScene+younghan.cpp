#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::younghanInit()
{
	//이미지 영역
	///////////맵 타일
	IMAGEMANAGER->addFrameImage("mapTiles", "image/maptool/tile512x384ver2.bmp", 0, 0, 512, 384, 8, 12, true, RGB(255, 0, 255));
	imgLoaded();
	///////////버튼
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
	IMAGEMANAGER->addImage("objDel", "image/maptool/objdel.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("delAll", "image/maptool/delall.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("un", "image/maptool/un.bmp", 16, 16, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("drag", "image/maptool/drag.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	//////////////////오브젝트
	IMAGEMANAGER->addImage("tree", "image/maptool/tree.bmp", 107, 113, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("tree2", "image/maptool/tree2.bmp", 89, 115, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("tree3", "image/maptool/tree3.bmp", 84, 139, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("tree4", "image/maptool/tree4.bmp", 94, 128, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("tree5", "image/maptool/tree5.bmp", 76, 83, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("wall1", "image/maptool/wall1.bmp", 32, 45, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("wall2", "image/maptool/wall2.bmp", 32, 45, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("lava_obj1", "image/maptool/lava_obj1.bmp", 54, 97, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("lava_obj2_l", "image/maptool/lava_obj2_l.bmp", 54, 86, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("lava_obj2_r", "image/maptool/lava_obj2_r.bmp", 54, 86, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("lava_obj3", "image/maptool/lava_obj3.bmp", 70, 52, true, RGB(255, 0, 255));
	imgLoaded();
	/////////////////유닛
	IMAGEMANAGER->addFrameImage("ghost_move_red", "image/unit/ghost/ghost_move_red.bmp", 320, 324, 8, 9, true, RGB(255, 255, 0));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ghost_move_blue", "image/unit/ghost/ghost_move_blue.bmp", 320, 324, 8, 9, true, RGB(255, 255, 0));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ghost_atk_red", "image/unit/ghost/ghost_atk_red.bmp", 320, 144, 8, 4, true, RGB(255, 255, 0));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ghost_atk_blue", "image/unit/ghost/ghost_atk_blue.bmp", 320, 144, 8, 4, true, RGB(255, 255, 0));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ghost_dead_red", "image/unit/ghost/ghost_dead_red.bmp", 280, 41, 5, 1, true, RGB(255, 255, 0));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("ghost_dead_blue", "image/unit/ghost/ghost_dead_blue.bmp", 280, 41, 5, 1, true, RGB(255, 255, 0));
	imgLoaded();
	/////////////////아이콘
	IMAGEMANAGER->addImage("icon_zergling", "image/icon/icon_zergling.bmp", 80, 90, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("icon_marine", "image/icon/icon_marine.bmp", 80, 90, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("icon_bishop", "image/icon/icon_bishop.bmp", 80, 90, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("icon_civilian", "image/icon/icon_aggroman.bmp", 80, 90, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("icon_diablo", "image/icon/icon_diablo.bmp", 80, 90, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("icon_ghost", "image/icon/icon_ghost.bmp", 80, 90, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("icon_templar", "image/icon/icon_templar.bmp", 80, 90, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("icon_skeleton", "image/icon/icon_skeleton.bmp", 80, 90, false, RGB(255, 0, 255));
	imgLoaded();
	//////////////////////UI///////////////////////
	IMAGEMANAGER->addImage("ui_menu", "image/ui/ui_menu.bmp", 900, 132, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("ui_home", "image/ui/ui_home.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("ui_retry", "image/ui/ui_retry.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("ui_clear", "image/ui/ui_clear.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("ui_start", "image/ui/ui_start.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("ui_on", "image/ui/ui_on.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("ui_off", "image/ui/ui_off.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("ui_stage1", "image/ui/ui_stage1.bmp", 80, 30, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("ui_stage2", "image/ui/ui_stage2.bmp", 80, 30, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("ui_BossStage", "image/ui/ui_bossstage.bmp", 80, 30, false, RGB(255, 0, 255));
	imgLoaded();
}

