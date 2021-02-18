#include "stdafx.h"
#include "playScene.h"

playScene::playScene()
{
}


playScene::~playScene()
{
}

HRESULT playScene::init(int data)
{
	CAMERAMANAGER->setCameraX(0);
	srand(time(NULL));
	_goCount = _goFrameX = _idleTime = 0;
	_wind = 0.f;
	_pm = new playerManager;	_pm->init(data);
	_um = new UIManager;		_um->init();
	_im = new itemManager;		_im->init();
	_bm = new bulletManager;	_bm->init();
	_em = new enemyManager;		_em->init(); // 매니저 혹사
	_pm->setImMemoryAddressLink(_im); // im의 함수로 아이템슬롯 상태 받아오기. 사용시 아이템 비우기. - 상호참조
	_pm->setBmMemoryAddressLink(_bm); // bm의 함수로 발사시키기 위해(pm의 각종 인자를 매개변수로 입력) - 상호참조
	_em->setBmMemoryAddressLink(_bm); // bm의 함수로 발사시키기 위해(em의 각종 인자를 매개변수로 입력) - 상호참조
	_em->setImMemoryAddressLink(_im); // im의 함수로 에너미의 위치에 아이템 드랍 함수를 쓰기 위해 - 단방향 참조
	_em->setPmMemoryAddressLink(_pm); // pm의 함수로 player위치를 감지하고 그에따라 공격방향 설정 - 단방향 참조
	_im->setPmMemoryAddressLink(_pm); // pm의 함수로 플레이어 rect값 받아오고 아이템 획득(충돌) 처리 - 상호참조
	_bm->setPmMemoryAddressLink(_pm); // pm의 함수로 rect값을 받아오고 충돌처리 - 상호참조
	_bm->setEmMemoryAddressLink(_em); // em의 함수로 rect값을 받아오고 충돌처리 - 상호참조

	return S_OK;
}

HRESULT playScene::init()
{
	CAMERAMANAGER->setCameraX(0);
	srand(time(NULL));
	_goCount = _goFrameX = _idleTime = 0;
	_wind = 0.f;
	_pm = new playerManager;	_pm->init(0);
	_um = new UIManager;		_um->init();
	_im = new itemManager;		_im->init();
	_bm = new bulletManager;	_bm->init();
	_em = new enemyManager;		_em->init(); // 매니저 혹사
	_pm->setImMemoryAddressLink(_im); // im의 함수로 아이템슬롯 상태 받아오기. 사용시 아이템 비우기. - 상호참조
	_pm->setBmMemoryAddressLink(_bm); // bm의 함수로 발사시키기 위해(pm의 각종 인자를 매개변수로 입력) - 상호참조
	_em->setBmMemoryAddressLink(_bm); // bm의 함수로 발사시키기 위해(em의 각종 인자를 매개변수로 입력) - 상호참조
	_em->setImMemoryAddressLink(_im); // im의 함수로 에너미의 위치에 아이템 드랍 함수를 쓰기 위해 - 단방향 참조
	_em->setPmMemoryAddressLink(_pm); // pm의 함수로 player위치를 감지하고 그에따라 공격방향 설정 - 단방향 참조
	_im->setPmMemoryAddressLink(_pm); // pm의 함수로 플레이어 rect값 받아오고 아이템 획득(충돌) 처리 - 상호참조
	_bm->setPmMemoryAddressLink(_pm); // pm의 함수로 rect값을 받아오고 충돌처리 - 상호참조
	_bm->setEmMemoryAddressLink(_em); // em의 함수로 rect값을 받아오고 충돌처리 - 상호참조

	return S_OK;
}


void playScene::release()
{
	if (_pm) { _pm->release();  SAFE_RELEASE(_pm);	SAFE_DELETE(_pm);}
	if (_um) { _um->release();  SAFE_RELEASE(_um);	SAFE_DELETE(_um); }
	if (_im) { _im->release();  SAFE_RELEASE(_im);	SAFE_DELETE(_im); }
	if (_bm) { _bm->release();  SAFE_RELEASE(_bm);	SAFE_DELETE(_bm); }
	if (_em) { _em->release();  SAFE_RELEASE(_em);	SAFE_DELETE(_em); }
}

void playScene::update()
{
	// _pm, _um 등등이 nullptr가 아닐때만 연산하도록
	if (_pm == nullptr || _um == nullptr || _im == nullptr || _bm == nullptr || _em == nullptr) return;
	if (_pm->getIsGameOver())
	{
		saveRecord();
		SCENEMANAGER->changeScene("게임오버씬");
		return; // 연산을 멈춰줘야 안 터지더라..
	}
	if (_em->getIsVictory())
	{
		saveRecord();
		SCENEMANAGER->changeScene("승리씬");
		return;
	}
	if (!(CAMERAMANAGER->getCameraLock()) && _goCount < 6) ++_goCount;
	if (_goCount >= 6)
	{ // 재촉하는거프레임 올려주기
		_goCount = 0;
		++_goFrameX;
		if (_goFrameX >= 16) _goFrameX = 0;
	}
	if (_idleTime < 1000) ++_idleTime;
	else _idleTime = 601; // 1000이면 601로 바꿔준다(어차피 600보다 크기때문에 재촉은 여전히 한다)
	if (CAMERAMANAGER->getCameraLock() || _pm->getRect().right >= GETCAM + WINSIZEX / 2 + 23) _idleTime = 0;
	_bm->setWind(_um->getWind());
	_im->setWind(_um->getWind()); // 바람값은 참조안하고 넣어주려고 여기서 갱신해줌
	_pm->update();
	_um->update();
	_im->update();
	_bm->update();
	_em->update();
}

void playScene::render()
{
	if (_pm == nullptr || _um == nullptr || _im == nullptr || _bm == nullptr || _em == nullptr) return;
	FINDIMG("맵")->render(getMemDC(), GETCAM, 0, GETCAM,0,WINSIZEX,WINSIZEY);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		FINDIMG("맵픽셀")->render(getMemDC(), GETCAM, 0, GETCAM, 0, WINSIZEX, WINSIZEY);
		TIMEMANAGER->render(getMemDC());
	}
	_um->render();
	_im->render();
	_em->render();
	_pm->render();
	_bm->render();
	interfaceRender();

}



void playScene::saveRecord() // 씬 넘어가기전 기록을 파일로 저장하는 함수
{	
	char temp[128];	ZeroMemory(temp, sizeof(temp));
	vector<string> vStr;
	
	if (_waccess_s(L"./기록.txt", 0) != 0) // 파일이 없으면 0,0으로 초기화해서 만듦
	{ // 없으면 만들어준다. 0, 0으로 자동저장됨.
		vStr.push_back(itoa(0, temp, 10));
		vStr.push_back(itoa(0, temp, 10));
		TXTDATA->txtSave("기록.txt", vStr);
	}
	vStr.clear();
	vStr = TXTDATA->txtLoad("기록.txt");
	_highScore = atoi(vStr[1].c_str());

	vStr.clear();
	vStr.push_back(itoa(_scoreSum, temp, 10));
	if (_scoreSum > _highScore)	vStr.push_back(itoa(_scoreSum, temp, 10));
	else vStr.push_back(itoa(_highScore, temp, 10));
	TXTDATA->txtSave("기록.txt", vStr);
}
