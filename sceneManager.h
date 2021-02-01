#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;

	mapSceneList _mSceneList;

	int _alpha;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//씬추가 함수
	gameNode* addScene(string sceneName, gameNode* scene);
	int getAlpha() { return _alpha; }

	//씬 변경 함수
	HRESULT changeScene(string sceneName);

	bool getMinimapScene(); // 미니맵을 그려야하는 씬인지?

	sceneManager() {};
	~sceneManager() {};
};

