#include "stdafx.h"
#include "playGround.h"

// 초기 이미지추가를 관리하는 함수입니다.

void playGround::imageInit()
{
	// 인터페이스 관련 이미지
	IMAGEMANAGER->addImage("인터페이스", "image/interface/interface.bmp", 800, 128, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인터페이스덧그리기", "image/interface/interfaceagain.bmp", 200, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("초록바", "image/interface/bargreen.bmp", 403, 20, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("빨강바", "image/interface/barred.bmp", 403, 20, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("파랑바", "image/interface/barblue.bmp", 403, 20, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("바람", "image/interface/barwind.bmp", 45, 9, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("온", "image/interface/on.bmp", 59, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("오프", "image/interface/off.bmp", 56, 23, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("눈", "image/interface/snow.bmp", 180, 30, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("모드", "image/interface/firemode.bmp", 29, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("현재탱크", "image/interface/currenttank.bmp", 112, 24, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("숫자", "image/interface/number.bmp", 250, 25, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("고", "image/interface/go.bmp", 512, 31, 16, 1, true, RGB(255, 0, 255));

	// 맵 관련 이미지
	IMAGEMANAGER->addImage("맵", "image/map.bmp", 5295, 448, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("맵픽셀", "image/mappixel.bmp", 5295, 448, true, RGB(255, 0, 255));

	// 탱크 관련 이미지
	IMAGEMANAGER->addFrameImage("캐논아이들", "image/tank/cannonidle.bmp", 3120, 236, 39, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("캐논이동", "image/tank/cannonrun.bmp", 721, 118, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("캐논공격", "image/tank/cannonattack.bmp", 870, 170, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("미탱아이들", "image/tank/missileidle.bmp", 1848, 138, 24, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("미탱이동", "image/tank/missilerun.bmp", 584, 154, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("미탱공격", "image/tank/missileattack.bmp", 945, 210, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("멀탱아이들", "image/tank/multiidle.bmp", 480, 112, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("멀탱이동", "image/tank/multirun.bmp", 400, 100, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("멀탱공격", "image/tank/multiattack.bmp", 663, 154, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("슈탱아이들", "image/tank/superidle.bmp", 287, 92, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("슈탱이동", "image/tank/supermove.bmp", 287, 92, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("슈탱공격", "image/tank/superattack.bmp", 472, 148, 8, 2, true, RGB(255, 0, 255));

	// 탱크의 포탄 관련 이미지
	IMAGEMANAGER->addFrameImage("캐논일반", "image/tankbullet/bulletcannon1.bmp", 92, 23, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("캐논특수", "image/tankbullet/bulletcannon2.bmp", 48, 12, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("미탱일반", "image/tankbullet/bulletmissile1.bmp", 216, 27, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("미탱특수", "image/tankbullet/bulletmissile2.bmp", 240, 30, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("멀탱일반", "image/tankbullet/bulletmulti1.bmp", 232, 29, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("멀탱특수", "image/tankbullet/bulletmulti2.bmp", 144, 18, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("슈탱일반", "image/tankbullet/bulletsuper1.bmp", 264, 33, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("슈탱특수", "image/tankbullet/bulletsuper2.bmp", 144, 19, 8, 1, true, RGB(255, 0, 255));

	// 아이템 관련 이미지
	IMAGEMANAGER->addImage("헬기", "image/item/helicopter.bmp", 90, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이템상자", "image/item/box.bmp", 144, 31, 4, 1, true, RGB(255, 0, 255));	// 알파프레임렌더하려면 trans true여야..
	IMAGEMANAGER->addFrameImage("상태템", "image/item/stateitem.bmp", 180, 39, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("상태템슬롯", "image/interface/stateitemslot.bmp", 148, 32, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사용템슬롯", "image/interface/usingitemslot.bmp", 124, 31, 4, 1, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("사용템버프표시", "image/interface/usingitem.bmp", 252, 59, 4, 1, true, RGB(255, 0, 255));

	// 적 관련 이미지 (모두 알파렌더 할 예정)
	IMAGEMANAGER->addFrameImage("적1대기", "image/enemy/enemy1idle.bmp", 370, 96, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("적1이동", "image/enemy/enemy1walk.bmp", 420, 100, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("적1공격", "image/enemy/enemy1attack.bmp", 1932, 90, 21, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("적2대기", "image/enemy/enemy2idle.bmp", 116, 76, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("적2이동", "image/enemy/enemy2walk.bmp", 420, 84, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("적2공격", "image/enemy/enemy2attack.bmp", 522, 82, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("적3", "image/enemy/enemy3.bmp", 752, 40, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("적4", "image/enemy/enemy4.bmp", 3912, 121, 24, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("적5", "image/enemy/enemy5.bmp", 220, 170, true, RGB(255, 0, 255));

	// 적 총알 관련 이미지
	IMAGEMANAGER->addFrameImage("적총알1", "image/enemy/enemybullet1.bmp", 52, 18, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("적총알2", "image/enemy/enemybullet2.bmp", 96, 15, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("적총알3", "image/enemy/enemybullet3.bmp", 26, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("적총알4", "image/enemy/enemybullet4.bmp", 21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("적총알5", "image/enemy/enemybullet5.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("적총알6", "image/enemy/enemybullet6.bmp", 24, 24, true, RGB(255, 0, 255));

	// 이펙트 관련 이미지
	IMAGEMANAGER->addFrameImage("바람이펙트", "image/effectwind.bmp", 276, 75, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("별이펙트", "image/effectpower.bmp", 320, 65, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쉴드이펙트", "image/effectshield.bmp", 455, 92, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("힐이펙트", "image/effectheal.bmp", 675, 50, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("타겟", "image/target.bmp", 80, 80, true, RGB(255, 0, 255));
	// 여기서부터는 이펙트매니저로 관리할 이펙트(단발성)
	IMAGEMANAGER->addImage("교체", "image/effectchange.bmp", 800, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스피드업", "image/effectspeedup.bmp", 900, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("파워업", "image/effectpowerup.bmp", 980, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("딜레이다운", "image/effectdelaydown.bmp", 900, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스코어업", "image/effectscore.bmp", 900, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("폭발", "image/explosion.bmp", 832, 62, true, RGB(255, 0, 255));

	// 씬 관련 이미지
	IMAGEMANAGER->addImage("메인씬", "image/scene/main.bmp", 800, 527, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("셀렉트씬", "image/scene/select.bmp", 800, 527, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("매뉴얼", "image/scene/manual.bmp", 800, 527, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("게임오버씬", "image/scene/gameover.bmp", 800, 527, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("승리씬", "image/scene/victory.bmp", 800, 527, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("탱크선택박스", "image/scene/selecttabletank.bmp", 247, 109, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("난이도선택박스", "image/scene/selecttabledifficulty.bmp", 264, 138, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("초기선택박스", "image/scene/selecttable.bmp", 218, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("기록갱신", "image/scene/record.bmp", 120, 116, true, RGB(255, 0, 255));
	
}
