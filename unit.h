#pragma once
#include "gameNode.h"

enum BELONG
{
	PLAYER,
	ENEMY
};

enum STATE
{
	WALK,		// 상대 기지로 가는 상태임
	ATTACKWAIT,	// 적을 발견하여 다음공격 대기하는 상태
	ATTACK,		// 공격할떄. 특정프레임에서 공격판정함
	DEAD		// 이게 끝나면 벡터에서 삭제
};

class unit : public gameNode
{
protected:
	int _ID;
	// ############ ID표 ##################
	// 유닛 만들때 무슨번호 쓸건지 톡으로 말해줘야 안겹칠듯. 유닛만들때 추가
	// 1 : 저글링(피50%이하면 연사력2배)
	// 2 : 마린
	// 3 : 시민(어그로)
	// 4 : 템플러(스톰)
	// 5 : 비숍
	// 6 : 디아블로
	// 7 : 해골병사
	// 8 : 고스트
	// ####################################

	int _frameCount;	// 프레임용 카운트
	int _frame;			// 현재프레임
	// 8방향 프레임이미지면 frameY에 쓰이고(bmp파일에서 세로방향으로 애니메이션)
	// 아니면(DEAD) frameX에 쓰인다(bmp파일에서 가로방향으로 애니메이션)
	int _maxFrame;
	// 끝프레임. 도달시 넘기거나 상태바꾸거나 하기 위함임.
	
	BELONG _belong;	// 누구소속인지(플레이어 아님 상대)
	STATE _state;	// 현재 상태	

	float _x;	float _y;
	int _width; int _height;
	RECT _rc; // _rc = RectMakeCenter(_x, _y, _width, _height);
	// 렉트크기는 바꾸지 말고 하나만 렉메센으로 씁시다..
	RECT _rangeRc; // 사거리렉트. 근접은 width에서 좀 더 크게
	// 이거 벗어나면 이동으로 셋스테이트 하려고 있는거
	RECT _focusRc; // 감지렉트. 타겟잡고 글로 가게끔하려고
	// 근거리 유닛이라도 충분히 커야됨.


	image* _image;

	float _destX; float _destY; // 목적지
	float _angle;	// 목적지나 적과의 각도(8방향이미지면 프레임x계산에도 이용)
	int _frameDirection; // 앵글에 따라 프레임도출(0~7)

	float _speed;	// 이동속도
	
	int _delay;		// 딜레이가 0일때 공격하도록 했음.
	int _maxDelay;	// 연사속도(얼마 주기로 한방씩 치는지). 60이면 1초에 한방씩 때릴듯

	float _damage;	// 데미지(이건 인터섹트에서 인자로 쓸거)

	float _HP;	//현재체력
	float _maxHP;		//최대체력

	int _target;
	// 벡터에 몇번째 상대를 타겟으로 잡았는지?
	// 만약 그 타겟이 죽음상태가 되면 인터섹트 클래스에서
	// 포문돌려서 그 죽은놈을 타겟잡고있는 놈들의
	// 타겟번호를 -1로 바꿔줘야합니다.(이해안되면 톡좀)
	// 안그러면 벡터 사라진걸 연산해서 벡터 터질수도 있을듯..

	int _attackIndex; // 어택상태에서 어떤프레임에서 공격판정될지
	bool _attackReady;
	// 공격상태에서 프레임바꿨을때 특정 프레임이면
	// (이 조건이어야 한번만 발동)
	// 이게 켜지고 인터섹트에서 공격연산하면서 이게 꺼짐
	bool _erase;
	// 죽음애니메이션 끝나면 이게 켜지고 유닛매니저에서 삭제

	int _tileNum;
	// 가장 최근 몇번타일까지 밟았는지
	// 그거에따라 목적지 바꿔줌. 플레이어면 역순으로 밟고
	// 적이면 순차대로 밟도록 함

	int _deathDuration;
	// 죽었을떄 시체(?)가 치워지는데까지 걸리는 카운트

	bool _active;

	int _count;
	bool _used;

public:
	unit();
	~unit();

	virtual HRESULT init(BELONG belong, float x, float y);
	// 누구건지?  그리고 생성위치
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	// 공통적으로 쓰이는것들은 유닛마다 넣기 번거로우니
	// 이 함수를 써주면 됨
	void commonInit();		// 자질구레한건 여기서 이닛
	void commonUpdate();	// 공통유닛 행동양식
	// 중요함) 함수는 여기서 마련됐지만
	// 사용은 상속클래스에서의 이닛 및 업데이트에 각각 넣는것임.
	// 함수 선언만 여기서 편의를 위해 해놓은것
	// 이닛에서 변수 적절히 넣기만하면 (좀 많지만..)
	// 그 변수에 따라 알아서 잘 행동하도록 해보려했음(그게 잘 될진 모름)
	// 그러다보니 멤버변수가 심하게 많은데 양해바람(물론 게터도 많아짐)

	// 공통렌더도 하고 싶었지만 이미지마다 위치보정해줘야해서

	void progressBarRender();
	virtual void reRender();
	void moveCancel(); // 이동했을테니 다시 돌려주는 함수(롤백)

	virtual void setState(STATE state) = 0;
	// 이건 유닛들마다 이미지가 다르므로 각각 만들어 씁시다.

	void RMC();
	// 렉트메이크센터 편하게 하려고

	// 게터들도 무지막지하게 많음
	int getID() { return _ID; }
	BELONG& getBelong() { return _belong; }
	// 이걸 변경할 일이 있을지 싶지만 마컨같은거면..
	STATE getState() { return _state; }
	// setState함수가 있으므로 이걸로 변경하면 안됨(참조자X)
	float& getX() { return _x; }
	float& getY() { return _y; }
	void setDest(float destX, float destY); // 목표설정은 이걸로할거임
	float getAngle1() { return _angle; }	// 왜 앵글에 1이 붙냐면 getAngle함수는 이미있기때문임..
	void setAngle(float angle);				// 각도설정은 이걸로 할거임
	int& getDelay() { return _delay; }
	float getDamage() { return _damage; }
	float& getHP() { return _HP; }
	int& getTarget() { return _target; }
	bool& getAttackReady() { return _attackReady; }
	bool getErase() { return _erase; }
	int getWidth() { return _width; }
	int getHeight() { return _height; }
	RECT getRect() { return _rc; }
	RECT getRangeRect() { return _rangeRc; }
	RECT getFocusRect() { return _focusRc; }
	int& getTileNum() { return _tileNum; }
	bool& getActive() { return _active; }
	float getSpeed() { return _speed; }
};

