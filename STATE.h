#pragma once
class player;

class STATE 
{
protected:
	player* _pl;
	// 상속클래스들도 player를 지칭?하는 _pl을 공통적으로 갖는것
	// 근데 이것만 있으면 껍데기겠지?
	// player.cpp보면 상태할당될때마다 링크함수(밑에있는)로 연결을 시켜주는 것
	// 우리가 참조할때 연결하던것과 같은 원리야
public:
	~STATE();
	virtual void EnterState()=0;
	virtual void updateState() = 0;
	virtual void ExitState() = 0;
	// 상속된 상태클래스가 이 함수를 이용할 수 있도록 함수명을 공통적으로 선언?했을뿐이지 이 함수가 실제로 실행되지는 않는다.
	// = 0의 용법이 그런 역할이래. 혹시라도 이걸로는 연산안하도록 하는 것임
	// 그게 interface니까..

	void LinkMemberAdress(player* player)	{_pl = player;}
};
