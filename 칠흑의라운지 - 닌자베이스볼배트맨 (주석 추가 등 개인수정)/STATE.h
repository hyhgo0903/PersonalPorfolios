#pragma once
class player;

class STATE 
{
protected:
	player* _pl;
	// 각각의 상태들에게 플레이어를 링크로 받아올 수 있게 만들었습니다
public:
	~STATE();
	virtual void EnterState() = 0;
	virtual void updateState() = 0;
	virtual void ExitState() = 0;
	// 순수 가상합수를 사용해서 상속받는 클래스들은 해당 함수를 쓸 수 있게 했습니다

	void LinkMemberAdress(player* player)	{_pl = player;}
};
