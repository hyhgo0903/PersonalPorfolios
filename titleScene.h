#pragma once
#include "gameNode.h"
class titleScene : public gameNode
{
private:
	RECT _rc;
	int _loopX; int _loopY;
	int _cursor;
	int _cursorCount;
	int _cursorFrame;
	bool _selected;

public:
	titleScene();
	~titleScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

