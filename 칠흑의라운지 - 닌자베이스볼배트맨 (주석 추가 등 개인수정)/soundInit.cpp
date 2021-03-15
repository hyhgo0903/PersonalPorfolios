#include "stdafx.h"
#include "playGround.h"

void playGround::soundInit()
{//브금류
	SOUNDMANAGER->addSound("셀렉트씬", "sound/셀렉트씬.mp3", true, true);
	SOUNDMANAGER->addSound("메인브금", "sound/bgm메인.wav", true, true);
	SOUNDMANAGER->addSound("보스브금", "sound/bgm보스.wav", true, true);

	//효과음류
	SOUNDMANAGER->addSound("엔딩", "sound/게임끝.wav", false, false);
	SOUNDMANAGER->addSound("시작", "sound/코인넣음.mp3", false, false);
	SOUNDMANAGER->addSound("선택 이동", "sound/셀렉트 이동.wav", false, false);
	SOUNDMANAGER->addSound("선택 엔터", "sound/선택2.wav", false, false);
	
	SOUNDMANAGER->addSound("적등장1", "sound/적 등장01.wav", false, false);
	SOUNDMANAGER->addSound("적등장2", "sound/적 등장02.wav", false, false);
	SOUNDMANAGER->addSound("보스등장", "sound/보스등장.wav", false, false);
	SOUNDMANAGER->addSound("보스목소리", "sound/보스목소리.wav", false, false);

	SOUNDMANAGER->addSound("폭탄", "sound/폭탄.wav", false, false);
	SOUNDMANAGER->addSound("던지기", "sound/공 던지기.wav", false, false);
	SOUNDMANAGER->addSound("쓰레기통부수는소리", "sound/쓰레기통부수는소리.wav", false, false);
	SOUNDMANAGER->addSound("의자부수는소리", "sound/의자부수는 소리.wav", false, false);
	SOUNDMANAGER->addSound("먹는소리", "sound/음식먹기.wav", false, false);

	SOUNDMANAGER->addSound("타격1", "sound/타격음01.wav", false, false);
	SOUNDMANAGER->addSound("타격2", "sound/타격음02.wav", false, false);
	SOUNDMANAGER->addSound("타격3", "sound/타격음03.wav", false, false);
	SOUNDMANAGER->addSound("타격4", "sound/타격음04.wav", false, false);
	SOUNDMANAGER->addSound("잡기공격", "sound/잡기공격.wav", false, false);
	SOUNDMANAGER->addSound("기합1", "sound/기합01.wav", false, false);
	SOUNDMANAGER->addSound("기합2", "sound/기합02.wav", false, false);

}