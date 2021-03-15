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

//���߿� �����ܺôٰ� �ڱ��Ը� �Ǵ� ��������Ʈ�� ������� �պ����ϸ� �պ���

HRESULT sceneManager::changeScene(string sceneName, int x)
{
	//���ͷ����Ϳ� ã���� �ϴ� ���� Ű ���� �ִ´�
	mapSceneIter find = _mSceneList.find(sceneName);
	//���ͷ����Ͱ� ����Ʈ ���̸� Ű���� �´� ���� �� ã�� ���̹Ƿ� ���и� ��ȯ
	if (find == _mSceneList.end()) return E_FAIL;
	//ã�� ���� ���� ���� �ش��ϸ� �ٲ� �ʿ䰡 �����Ƿ� ������ ��ȯ
	if (find->second == _currentScene) return S_OK;
	//���� �ٲٴµ� ���������� �� ���� init()�Լ��� �����ϸ� if ���ǿ� ����
	if (SUCCEEDED(find->second->init()))
	{
		//���� ���� ������ �Լ��� ����(�޸� ����)
		if (_currentScene) _currentScene->release();
		//�ٲٷ��� ���� ��������� ü����
		_currentScene = find->second;
		//����ü ������ ��ȯ
		return S_OK;
	}
	//���� �ٲ��� �������Ƿ� ���и� ��ȯ
	return E_FAIL;
}
