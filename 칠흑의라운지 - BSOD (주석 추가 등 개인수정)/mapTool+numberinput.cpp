#include "stdafx.h"
#include "mapTool.h"

void mapTool::numberInput()
{
	if (_modifyingCount > 0) --_modifyingCount;
	if (_modifyingCount == 0 && _modifyingNum != 0)
	{
		_modifyingNum = 0;
	}

	if ((KEYMANAGER->isOnceKeyDown('0') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD0)) && _modifyingNum != 0)
	{
		switch (_modifyingNum)
		{
		case 1:	_isoTile[0].gold = _isoTile[0].gold % 1000;	_modifyingNum = 2;	break;
		case 2:	_isoTile[0].gold = _isoTile[0].gold / 1000*1000 + _isoTile[0].gold % 100;	_modifyingNum = 3;	break;
		case 3:	_isoTile[0].gold = _isoTile[0].gold / 100 * 100 + _isoTile[0].gold % 10;	_modifyingNum = 4;	break;
		case 4:	_isoTile[0].gold = _isoTile[0].gold / 10 * 10;	_modifyingNum = 0;	break;
		}
		_modifyingCount = 300;
	}
	if ((KEYMANAGER->isOnceKeyDown('1') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD1)) && _modifyingNum != 0)
	{
		switch (_modifyingNum)
		{
		case 1:	_isoTile[0].gold = 1000+ _isoTile[0].gold % 1000;	_modifyingNum = 2;	break;
		case 2:	_isoTile[0].gold = 100+ _isoTile[0].gold / 1000 * 1000 + _isoTile[0].gold % 100;	_modifyingNum = 3;	break;
		case 3:	_isoTile[0].gold = 10+ _isoTile[0].gold / 100 * 100 + _isoTile[0].gold % 10;	_modifyingNum = 4;	break;
		case 4:	_isoTile[0].gold = 1+ _isoTile[0].gold / 10 * 10;	_modifyingNum = 0;	break;
		}
		_modifyingCount = 300;
	}
	if ((KEYMANAGER->isOnceKeyDown('2') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD2)) && _modifyingNum != 0)
	{
		switch (_modifyingNum)
		{
		case 1:	_isoTile[0].gold = 2000 + _isoTile[0].gold % 1000;	_modifyingNum = 2;	break;
		case 2:	_isoTile[0].gold = 200 + _isoTile[0].gold / 1000 * 1000 + _isoTile[0].gold % 100;	_modifyingNum = 3;	break;
		case 3:	_isoTile[0].gold = 20 + _isoTile[0].gold / 100 * 100 + _isoTile[0].gold % 10;	_modifyingNum = 4;	break;
		case 4:	_isoTile[0].gold = 2 + _isoTile[0].gold / 10 * 10;	_modifyingNum = 0;	break;
		}
		_modifyingCount = 300;
	}
	if ((KEYMANAGER->isOnceKeyDown('3') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD3)) && _modifyingNum != 0)
	{
		switch (_modifyingNum)
		{
		case 1:	_isoTile[0].gold = 3000 + _isoTile[0].gold % 1000;	_modifyingNum = 2;	break;
		case 2:	_isoTile[0].gold = 300 + _isoTile[0].gold / 1000 * 1000 + _isoTile[0].gold % 100;	_modifyingNum = 3;	break;
		case 3:	_isoTile[0].gold = 30 + _isoTile[0].gold / 100 * 100 + _isoTile[0].gold % 10;	_modifyingNum = 4;	break;
		case 4:	_isoTile[0].gold = 3 + _isoTile[0].gold / 10 * 10;	_modifyingNum = 0;	break;
		}
		_modifyingCount = 300;
	}
	if ((KEYMANAGER->isOnceKeyDown('4') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD4)) && _modifyingNum != 0)
	{
		switch (_modifyingNum)
		{
		case 1:	_isoTile[0].gold = 4000 + _isoTile[0].gold % 1000;	_modifyingNum = 2;	break;
		case 2:	_isoTile[0].gold = 400 + _isoTile[0].gold / 1000 * 1000 + _isoTile[0].gold % 100;	_modifyingNum = 3;	break;
		case 3:	_isoTile[0].gold = 40 + _isoTile[0].gold / 100 * 100 + _isoTile[0].gold % 10;	_modifyingNum = 4;	break;
		case 4:	_isoTile[0].gold = 4 + _isoTile[0].gold / 10 * 10;	_modifyingNum = 0;	break;
		}
		_modifyingCount = 300;
	}
	if ((KEYMANAGER->isOnceKeyDown('5') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD5)) && _modifyingNum != 0)
	{
		switch (_modifyingNum)
		{
		case 1:	_isoTile[0].gold = 5000 + _isoTile[0].gold % 1000;	_modifyingNum = 2;	break;
		case 2:	_isoTile[0].gold = 500 + _isoTile[0].gold / 1000 * 1000 + _isoTile[0].gold % 100;	_modifyingNum = 3;	break;
		case 3:	_isoTile[0].gold = 50 + _isoTile[0].gold / 100 * 100 + _isoTile[0].gold % 10;	_modifyingNum = 4;	break;
		case 4:	_isoTile[0].gold = 5 + _isoTile[0].gold / 10 * 10;	_modifyingNum = 0;	break;
		}
		_modifyingCount = 300;
	}
	if ((KEYMANAGER->isOnceKeyDown('6') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD6)) && _modifyingNum != 0)
	{
		switch (_modifyingNum)
		{
		case 1:	_isoTile[0].gold = 6000 + _isoTile[0].gold % 1000;	_modifyingNum = 2;	break;
		case 2:	_isoTile[0].gold = 600 + _isoTile[0].gold / 1000 * 1000 + _isoTile[0].gold % 100;	_modifyingNum = 3;	break;
		case 3:	_isoTile[0].gold = 60 + _isoTile[0].gold / 100 * 100 + _isoTile[0].gold % 10;	_modifyingNum = 4;	break;
		case 4:	_isoTile[0].gold = 6 + _isoTile[0].gold / 10 * 10;	_modifyingNum = 0;	break;
		}
		_modifyingCount = 300;
	}
	if ((KEYMANAGER->isOnceKeyDown('7') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD7)) && _modifyingNum != 0)
	{
		switch (_modifyingNum)
		{
		case 1:	_isoTile[0].gold = 7000 + _isoTile[0].gold % 1000; // 천의 자릿수를 7로 바꾸는 과정
			_modifyingNum = 2;	break; // 다음 자릿수로 옮겨줌(백의자릿수 수정하도록)
		case 2:	_isoTile[0].gold = 700 + _isoTile[0].gold / 1000 * 1000 + _isoTile[0].gold % 100; // 백의 자릿수를 7로 바꾸는 과정
			_modifyingNum = 3;	break; // 다음 자릿수로 옮겨줌(백의자릿수 수정하도록)
		case 3:	_isoTile[0].gold = 70 + _isoTile[0].gold / 100 * 100 + _isoTile[0].gold % 10; // 십의 자릿수를 7로 바꾸는 과정
			_modifyingNum = 4;	break; // 다음 자릿수로 옮겨줌(백의자릿수 수정하도록)
		case 4:	_isoTile[0].gold = 7 + _isoTile[0].gold / 10 * 10; // 일의 자릿수를 7로 바꾸는 과정
			_modifyingNum = 0;	break; // 수치를 수정하지 않는 상태가 됨(완료)
		}
		_modifyingCount = 300; // 수치 수정하는 대기값 초기화
	}
	if ((KEYMANAGER->isOnceKeyDown('8') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD8)) && _modifyingNum != 0)
	{
		switch (_modifyingNum)
		{
		case 1:	_isoTile[0].gold = 8000 + _isoTile[0].gold % 1000;	_modifyingNum = 2;	break;
		case 2:	_isoTile[0].gold = 800 + _isoTile[0].gold / 1000 * 1000 + _isoTile[0].gold % 100;	_modifyingNum = 3;	break;
		case 3:	_isoTile[0].gold = 80 + _isoTile[0].gold / 100 * 100 + _isoTile[0].gold % 10;	_modifyingNum = 4;	break;
		case 4:	_isoTile[0].gold = 8 + _isoTile[0].gold / 10 * 10;	_modifyingNum = 0;	break;
		}
		_modifyingCount = 300;
	}
	if ((KEYMANAGER->isOnceKeyDown('9') || KEYMANAGER->isOnceKeyDown(VK_NUMPAD9)) && _modifyingNum != 0)
	{
		switch (_modifyingNum)
		{
		case 1:	_isoTile[0].gold = 9000 + _isoTile[0].gold % 1000;	_modifyingNum = 2;	break;
		case 2:	_isoTile[0].gold = 900 + _isoTile[0].gold / 1000 * 1000 + _isoTile[0].gold % 100;	_modifyingNum = 3;	break;
		case 3:	_isoTile[0].gold = 90 + _isoTile[0].gold / 100 * 100 + _isoTile[0].gold % 10;	_modifyingNum = 4;	break;
		case 4:	_isoTile[0].gold = 9 + _isoTile[0].gold / 10 * 10;	_modifyingNum = 0;	break;
		}
		_modifyingCount = 300;
	}
}