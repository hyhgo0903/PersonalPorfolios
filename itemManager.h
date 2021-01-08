#pragma once
#include "gameNode.h"
#include "baseball.h"
#include "bat.h"
#include "bomb.h"
#include <vector>

class itemManager :	public gameNode
{
private:
	vector<item*> _vItem;
	vector<item*>::iterator _viItem;
	// (중요함) 벡터에는 에너미로써(부모클래스) 넣는거야
	// 따라서 subclass만의 고유한 함수를 만들어 이용하고 싶다면
	// [ex) (다른클래스에서) getVItem()[i]->고유함수();]
	// 사용할 수 없다고 밑줄이 뜰거야. (벡터내의 item클래스라고 인식하고 있어)

	// 그럴떈 item.h에서 " 고유한 함수() = 0; " 요런식으로 껍데기 함수를 마련할수 있어.
	// 그러면 item에 그 함수가 있으니 에러는 안나지만 item의 함수가 아닌 상속클래스로 잘 연산하게 돼
	bool itemAttack;
	bool _direction;
public:
	itemManager();
	~itemManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	

	void createBaseball(float x, float y);
	void createBomb(float x, float y);
	void throwing();
	void throwing(bool direction);
	vector<item*> getVItem() { return _vItem; }
	vector<item*>::iterator getViItem() { return _viItem; }
};

