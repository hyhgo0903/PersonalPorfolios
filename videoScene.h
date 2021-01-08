#pragma once
#include "gameNode.h"
#include <Vfw.h>
#pragma comment (lib, "Vfw32.lib") // 영상 관련

class videoScene :	public gameNode
{
private:
	HWND LogoVideo;

public:
	videoScene();
	~videoScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


};

