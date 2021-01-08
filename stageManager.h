#pragma once
#include "gameNode.h"
#include "trashCan.h"
#include "chair.h" // 상속클래스들만 넣어줘도 됨.

class stageManager : public gameNode
{
private:
	vector<object*> _VObject;
	vector<object*>::iterator _ViObject;
	// (중요함) 벡터에는 에너미로써(부모클래스) 넣는거야
	// 따라서 subclass만의 고유한 함수를 만들어 이용하고 싶다면
	// [ex) (다른클래스에서) getVObject()[i]->고유함수();]
	// 사용할 수 없다고 밑줄이 뜰거야. (벡터내의 object클래스라고 인식하고 있어)

	// 그럴떈 object.h에서 " 고유한 함수() = 0; " 요런식으로 껍데기 함수를 마련할수 있어.
	// 그러면 object에 그 함수가 있으니 에러는 안나지만 object의 함수가 아닌 상속클래스로 잘 연산하게 돼

public:
	stageManager();
	~stageManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void createChair(float x, float y);
	void createTrashCan(float x, float y);

	vector<object*> getVObject() { return _VObject; }
	vector<object*>::iterator getViObject() { return _ViObject; }
};

