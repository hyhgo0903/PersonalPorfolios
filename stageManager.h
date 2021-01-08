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
	void removeObject(int arrNum); // 충돌한 오브젝트가 의자인지 쓰레기통인지 판별 후 > 쓰레기통이라면 해당 객체를 없애주는 함수

	vector<object*> getVObject() { return _VObject; }
	vector<object*>::iterator getViObject() { return _ViObject; }

	// getVObject()[i] << 외부에서 이 벡터가 몇번째인지 찾아줄때 이렇게 한다. (for문으로)


};

