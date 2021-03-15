#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

gameNode* sceneManager::_currentScene = NULL;

HRESULT sceneManager::init()
{
	_currentScene = NULL;

	return S_OK;
}

void sceneManager::release()
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}
	_mSceneList.clear();
}

void sceneManager::update()
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
	if (_currentScene) _currentScene->render();
}

gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	if (!scene) return nullptr;
	_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

//나중에 눈여겨봤다가 자기입맛 또는 팀프로젝트의 구조대로 손봐야하면 손볼것

HRESULT sceneManager::changeScene(string sceneName, int x)
{
	//이터레이터에 찾고자 하는 씬의 키 값을 넣는다
	mapSceneIter find = _mSceneList.find(sceneName);
	//이터레이터가 리스트 끝이면 키값에 맞는 씬을 못 찾은 것이므로 실패를 반환
	if (find == _mSceneList.end()) return E_FAIL;
	//찾는 씬이 현재 씬에 해당하면 바꿀 필요가 없으므로 성공을 반환
	if (find->second == _currentScene) return S_OK;
	//씬을 바꾸는데 성공했으면 그 씬의 init()함수를 실행하며 if 조건에 들어옴
	if (SUCCEEDED(find->second->init()))
	{
		//기존 씬의 릴리즈 함수를 실행(메모리 해제)
		if (_currentScene) _currentScene->release();
		//바꾸려는 씬을 현재씬으로 체인지
		_currentScene = find->second;
		//씬교체 성공을 반환
		return S_OK;
	}
	//씬을 바꾸지 못했으므로 실패를 반환
	return E_FAIL;
}
