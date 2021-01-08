#include "stdafx.h"
#include "mainScene.h"


void mainScene::zOrderRender()
{ // ###################### z오더 구현 여기부터 ##################
	int temp;
	for (int i = 0; i < _em->getVEnemy().size(); ++i)
	{ // 벡터에 객체들의 렉트.바텀값을 추가(푸시백)해줌
		temp = _em->getVEnemy()[i]->getRect().bottom; // 이건 적들
		bottomY.push_back(temp);
	}
	for (int i = 0; i < _sm->getVObject().size(); ++i)
	{ // 벡터에 객체들의 렉트.바텀값을 추가(푸시백)해줌
		temp = _sm->getVObject()[i]->getRect().bottom; // 이건 오브젝트들
		bottomY.push_back(temp);
	}
	for (int i = 0; i < _im->getVItem().size(); ++i)
	{ // 벡터에 객체들의 렉트.바텀값을 추가(푸시백)해줌
		temp = _im->getVItem()[i]->getRect().bottom; // 이건 아이템들
		bottomY.push_back(temp);
	}
	temp = _pl->getGroundRc().bottom; // 이건 플레이어
	bottomY.push_back(temp);
	// y값을 하나하나 넣었음

	sprintf_s(_str, "정렬전:");
	TextOut(getMemDC(), CAMX+340, CAMY, _str, strlen(_str));
	for (int i = 0; i < bottomY.size(); ++i)
	{
		sprintf_s(_str, "%d", bottomY[i]);
		TextOut(getMemDC(), CAMX + 400 + i * 40, CAMY, _str, strlen(_str));
	} // 텍스트는 이해를 돕기위해 참고용으로 넣어봤어. 나중에 없앨거


	for (int i = 0; i < bottomY.size() - 1; ++i)
	{
		for (int j = i + 1; j > 0 && bottomY[j] < bottomY[j - 1]; --j)
		{
			swap(bottomY[j], bottomY[j - 1]);
		}
	}	// 삽입 알고리즘을 통한 정렬이야
	// 반복문을 잘 분석한다면 알 수 있겠지만, 순차적으로 반복문이 도는데
	// 뒤의것이 앞의것보다 작다면 swap(위치바꿈)을 반복하는 반복문이라 보면 돼

	sprintf_s(_str, "정렬후:");
	TextOut(getMemDC(), CAMX+340, CAMY+20, _str, strlen(_str));
	for (int i = 0; i < bottomY.size(); ++i)
	{
		sprintf_s(_str, "%d", bottomY[i]);
		TextOut(getMemDC(), CAMX + 400 + i * 40, CAMY+20, _str, strlen(_str));
	} // 텍스트는 이해를 돕기위해 참고용으로 넣어봤어. 나중에 없앨거

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

	//너무 비효율적이지 않을까..
}


