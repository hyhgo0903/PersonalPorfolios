#include "stdafx.h"
#include "mapTool.h"

//얘는 마우스랑 오브젝트의 샘플렉트의 충돌 + 어떤 메뉴가 열려있는지 검사해서 결과값을 주는거에요
void mapTool::ptInObj()
{
	if (PtInRect(&_tree1, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE1;
	else if (PtInRect(&_tree2, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE2;
	else if (PtInRect(&_tree3, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE3;
	else if (PtInRect(&_tree4, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE4;
	else if (PtInRect(&_tree5, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE5;
	else if (PtInRect(&_icZergling, _cameraPtMouse) && _menuNum == THREE)	_objName = ZERGLING;
}

//얘는 선택된 오브젝트가 어떤건지 판단해서 선택한 타일에 그 오브젝트 값을 부여해주는겁니다
void mapTool::createObj()
{
	//여기서 이제 담아둔 오브젝트 이름을 부여해서 타일위에 나무뜨게할꺼임
	if (!_menuInPt)
	{
		if (_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = NONE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE1 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE1;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE2 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE2;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE3 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE3;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE4 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE4;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE5 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE5;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == ZERGLING && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = ZERGLING;
			InvalidateRect(_hWnd, NULL, false);
		}
	}
}