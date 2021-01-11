#include "stdafx.h"
#include "mainScene.h"

void mainScene::zOrderRender()
{ // ###################### z오더 구현 여기부터 ##################
	RECT temp;
	for (int i = 0; i < _em->getVEnemy().size(); ++i)
	{ // 벡터에 객체들의 렉트.바텀값을 추가(푸시백)해줌
		temp = _em->getVEnemy()[i]->getRect(); // 이건 적들
		if (temp.bottom > CAMY && temp.top <CAMY + WINSIZEY && temp.right >CAMX && temp.left < CAMX + WINSIZEX) bottomY.push_back(temp.bottom);
	}
	for (int i = 0; i < _sm->getVObject().size(); ++i)
	{ // 벡터에 객체들의 렉트.바텀값을 추가(푸시백)해줌
		temp = _sm->getVObject()[i]->getRect(); // 이건 오브젝트들
		if (temp.bottom > CAMY && temp.top <CAMY + WINSIZEY && temp.right >CAMX && temp.left < CAMX + WINSIZEX) bottomY.push_back(temp.bottom);
	}
	for (int i = 0; i < _im->getVItem().size(); ++i)
	{ // 벡터에 객체들의 렉트.바텀값을 추가(푸시백)해줌
		temp = _im->getVItem()[i]->getRect(); // 이건 아이템들
		if (temp.bottom > CAMY && temp.top <CAMY + WINSIZEY && temp.right >CAMX && temp.left < CAMX + WINSIZEX) bottomY.push_back(temp.bottom);		
	}
	temp = _pl->getGroundRc(); // 이건 플레이어
	bottomY.push_back(temp.bottom);
	// y값을 하나하나 넣었음	

	if (bottomY.size() > 1 ) QuickSort(0, bottomY.size() - 1); // 이게 퀵정렬

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{

		for (int i = 0; i < bottomY.size(); ++i)
		{
			sprintf_s(_str, "%d", bottomY[i]);
			TextOut(getMemDC(), CAMX + 80 * i, CAMY + 100, _str, strlen(_str));
		}

	}
	for (int i = 0; i < bottomY.size(); ++i)
	{ // 정렬했으니 벡터에 담긴 순서대로 그리기로 함
		if (_pl->getGroundRc().bottom == bottomY[i])
		{ // 내가 찾는 바텀값과 동일한지?
			_pl->playerRender(); // 그렇다면 렌더
		}
		for (int j = 0; j < _em->getVEnemy().size(); ++j)
		{
			if (_em->getVEnemy()[j]->getRect().bottom == bottomY[i])
			{
				_em->getVEnemy()[j]->render();
			}
		}
		for (int j = 0; j < _im->getVItem().size(); ++j)
		{
			if (_im->getVItem()[j]->getRect().bottom == bottomY[i])
			{
				_im->getVItem()[j]->render();
			}
		}
		for (int j = 0; j < _sm->getVObject().size(); ++j)
		{
			if (_sm->getVObject()[j]->getRect().bottom == bottomY[i])
			{
				_sm->getVObject()[j]->render();
			}
		}
	}
	bottomY.clear();
}


void mainScene::uiRender()
{
	FINDIMG("플레이어ui")->render(getMemDC(), CAMX + 170, CAMY);
	FINDIMG("그냥텍스트")->frameRender(getMemDC(), CAMX + 670, CAMY, _timeLimit % 2, 0);
	FINDIMG("초록숫자")->frameRender(getMemDC(), CAMX + 466, CAMY + 30, _timeLimit / 10, 0);
	FINDIMG("초록숫자")->frameRender(getMemDC(), CAMX + 513, CAMY + 30, _timeLimit % 10, 0);
	FINDIMG("노란숫자")->frameRender(getMemDC(), CAMX + 359, CAMY + 53, _life, 0);

	// _score = _cl->getScore();
	_score = 1500;
	FINDIMG("하얀숫자")->frameRender(getMemDC(), CAMX + 359, CAMY + 29, _score%10, 0);
	if (_score > 9)		FINDIMG("하얀숫자")->frameRender(getMemDC(), CAMX + 335, CAMY + 29, _score / 10 % 10, 0);
	if (_score > 99)	FINDIMG("하얀숫자")->frameRender(getMemDC(), CAMX + 311, CAMY + 29, _score / 100 % 10, 0);
	if (_score > 999)	FINDIMG("하얀숫자")->frameRender(getMemDC(), CAMX + 287, CAMY + 29, _score / 1000 % 10, 0);
	if (_score > 9999)	FINDIMG("하얀숫자")->frameRender(getMemDC(), CAMX + 263, CAMY + 29, _score / 10000 % 10, 0);

	// _playerHpRatio = _pl->getCurrentHp()/100.f;
	// _bossHpRatio = _em->;

	if (_playerHpRatio > 0) _playerHpRatio -= 0.01f;
	else _playerHpRatio = 1.f; // 확인용

	if (_playerHpRatio < 0.3f)
	{
		FINDIMG("빨피일때")->frameRender(getMemDC(), CAMX + 173, CAMY + 31, _redCount/15, 0);
	}
	FINDIMG("플레이어체력바")->render(getMemDC(), CAMX + 245, CAMY + 81, 132 - 132 * _playerHpRatio, 0, 132 * _playerHpRatio, 18);
	
	if (_bossHpRatio > 0) _bossHpRatio -= 0.01f;
	else _bossHpRatio = 1.f; // 확인용 576 96 6~570
	FINDIMG("보스텍스트")->render(getMemDC(), CAMX + 428, CAMY + 176);
	if (_bossHpRatio > 0.5f) FINDIMG("보스체력바")->render(getMemDC(), CAMX + 224, CAMY + 200, 0, 24, 576, 24);
	else  FINDIMG("보스체력바")->render(getMemDC(), CAMX + 224, CAMY + 200, 0, 72, 576, 24);
	if (_bossHpRatio > 0.5f) FINDIMG("보스체력바")->render(getMemDC(), CAMX + 230, CAMY + 200, 576 - 570 * (_bossHpRatio -0.5f) * 2, 0, 570 * (_bossHpRatio - 0.5f) * 2, 24);
	else  FINDIMG("보스체력바")->render(getMemDC(), CAMX + 230, CAMY + 200, 576 - 570 * (_bossHpRatio) * 2, 48, 570 * (_bossHpRatio) * 2, 24);
	
}

int mainScene::paritition(int left, int right)
{
	int pivot = bottomY[left];//피벗의 위치는 가장 왼쪽에서 시작
	int low = left + 1;
	int high = right;

	while (low <= high) // 교차되기 전까지 반복한다 
	{
		while (low <= right && pivot >= bottomY[low]) // 피벗보다 큰 값을 찾는 과정 
		{
			low++; // low를 오른쪽으로 이동 
		}
		while (high >= (left + 1) && pivot <= bottomY[high])// 피벗보다 작은 값을 찾는 과정
		{
			high--; // high를 왼쪽으로 이동
		}
		if (low <= high) // 교차되지 않은 상태이면 스왑 과정 실행 
		{
			int temp = bottomY[low];
			bottomY[low] = bottomY[high];
			bottomY[high] = temp;
		}


	}
	// 피벗과 high가 가리키는 대상을 교환 
	int temp = bottomY[left];
	bottomY[left] = bottomY[high];
	bottomY[high] = temp;

	// 옮겨진 피벗의 위치정보를 반환 
	return high;
}

void mainScene::QuickSort(int left, int right)
{
	if (left < right)
	{
		int q = paritition(left, right);  // 둘로 나누어서
		QuickSort(left, q - 1); // 왼쪽 영역을 정렬한다.
		QuickSort(q + 1, right); // 오른쪽 영역을 정렬한다.
	}
}