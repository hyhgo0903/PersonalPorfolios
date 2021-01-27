#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include <string>

#define LOADINGMAX 30
#define ADDF IMAGEMANAGER->addFrameImage
#define MGT RGB(255,0,255)

class progressBar;

class loadingScene : public gameNode
{
private:
	progressBar* _loadingBar;
	image* _background;

public:
	loadingScene();
	~loadingScene();

	int _currentCount;
	bool _loadingEnd;
	bool _soundLoaded; // 사운드를 로딩했는지?
	string _soundName; // 사운드는 그냥 매개변수에 텍스트 입력하자..

	HRESULT init();
	void release();
	void update();
	void render();

	void chanhoInit();
	void deokhoInit();
	void hyunjeonghoInit();
	void yoonghoInit();
	void younghanInit();

	void imgLoaded();
	void soundLoaded();
};

static DWORD CALLBACK threadFunction(LPVOID lpParameter);
