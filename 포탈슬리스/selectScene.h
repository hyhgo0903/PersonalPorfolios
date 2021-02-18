#pragma once
#include "gameNode.h"

#pragma warning(disable:4996)

class selectScene :	public gameNode
{
private:
	bool _manualPop;		//매뉴얼 나오는 중이니?
	bool _selectPhase;		//선택페이즈로 진입했니?
	bool _selected;			//난이도를 선택했니? (탱크선택으로 진입)
	int _data;//선택된 난이도(저장할것)	//선택된 탱크(저장할것)
	int _cursor[2];			//커서
public:
	selectScene();
	~selectScene();


	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
};

