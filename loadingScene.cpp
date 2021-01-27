#include "stdafx.h"
#include "loadingScene.h"

//리소스 많이 잡아먹는 음악파일 그림파일.. 3d모델링파일
//싱글톤->메모리 상주시키는것.
//메모리 적재하면 그게 로딩이야

loadingScene::loadingScene()
	: _background(nullptr), _loadingBar(nullptr),
	_currentCount(0), _loadingEnd(0), _soundLoaded(0)
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	_loadingBar = new progressBar;
	_loadingBar->init(0, WINSIZEY / 2 - 50, WINSIZEX, 50);
	_loadingBar->setGauge(0, 0);
	_background = IMAGEMANAGER->addImage("로딩배경", "image/titleTemp.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));


	//쓰레드를 사용해보자
	CreateThread(
		NULL,				//스레드의 보안속성(자식윈도우가 존재할때)
		NULL,				//스레드의 스택크기(NULL로 두면 메인쓰레드 크기와 동일)
		threadFunction,		//스레드 사용할 함수 명
		this,				//스레드 매개변수(this로 두면 본 클래스)
		NULL,				//스레드의 특성(기다릴지, 바로 실행(NULL이면 요게 해당))
		NULL				//스레드 생성 후 스레드의 ID 넘겨줌 보통은 NULL로 둔다
	);

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loadingBar);
}

void loadingScene::update()
{
	_loadingBar->update();
	_loadingBar->setGauge(_currentCount, LOADINGMAX);

	//로딩이 다 되면
	if (_loadingEnd)
	{
		SCENEMANAGER->changeScene("타이틀씬");
	}
}

void loadingScene::render()
{
	//그림파일 이미지 경로를 텍스트로 보여줘도 되고


	_background->render(getMemDC());
	_loadingBar->render();
	char cstr[128];
	ZeroMemory(cstr, 126);
	if (!_soundLoaded)
	{
		strcpy_s(cstr, IMAGEMANAGER->getLoading().c_str());
	}
	else
	{
		strcpy_s(cstr, SOUNDMANAGER->getLatestAdded().c_str());
	}
	TextOut(getMemDC(), 0, WINSIZEY -50, cstr, strlen(cstr));
}


DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	//여기에다가
	//이미지매니저나, 사운드 매니저 써서
	//add 해주면 된다.
	loadingScene* loadingHelper = (loadingScene*)lpParameter;



	//while (loadingHelper->_currentCount != LOADINGMAX)
	//{
	//	IMAGEMANAGER->addImage("인게임", "시작화면.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//	IMAGEMANAGER->addImage("로딩배경", "리그오브레전드로딩.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//	//여기에 와일문 돌리지말고 이미지랑 사운드 등 리소스 파일 추가해라

	//	//CPU 잠깐 정지거는건데
	//	//이거 안걸면 너무 빨라가지고 눈 깜빡이면 넘어가버림 (1000개여도)
	//	Sleep(1);
	//	loadingHelper->_currentCount++;
	//}

	loadingHelper->chanhoInit();
	loadingHelper->deokhoInit();
	loadingHelper->hyunjeonghoInit();
	loadingHelper->yoonghoInit();
	loadingHelper->younghanInit();


	// 로딩 완료시
	loadingHelper->_loadingEnd = true;

	return 0;
}

void loadingScene::imgLoaded()
{
	_soundLoaded = false;
	++_currentCount;
	Sleep(20);
}

void loadingScene::soundLoaded()
{
	_soundLoaded = true;
	++_currentCount;
	Sleep(20);
}
