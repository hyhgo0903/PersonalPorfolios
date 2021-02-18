#include "stdafx.h"
#include "playerManager.h"

//픽셀 정밀조정용으로 따로 떼냈습니다 (복잡하기도 하고)

void playerManager::stateRender()
{
	switch (_tank.type)
	{
	case CANNON:
		switch (_tank.state)
		{
		case RIGHTIDLE:FINDIMG("캐논아이들")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 19, _tank.rc.top - 68, _tank.frameX, 0, _alphaValue);		break;
		case LEFTIDLE:FINDIMG("캐논아이들")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 15, _tank.rc.top - 68, _tank.frameX, 1, _alphaValue);		break;
		case RIGHTRUN:FINDIMG("캐논이동")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 44, _tank.rc.top - 10 , _tank.frameX, 0, _alphaValue);		break;
		case LEFTRUN:FINDIMG("캐논이동")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 17, _tank.rc.top - 10 , _tank.frameX, 1, _alphaValue);		break;
		case RIGHTATTACK:FINDIMG("캐논공격")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 60, _tank.rc.top - 35, _tank.frameX, 0, _alphaValue);		break;
		case LEFTATTACK:FINDIMG("캐논공격")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 62, _tank.rc.top - 35, _tank.frameX, 1, _alphaValue);		break;
		}
		break;
	case MISSILE:
		switch (_tank.state)
		{
		case RIGHTIDLE:FINDIMG("미탱아이들")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 27, _tank.rc.top - 22, _tank.frameX, 0, _alphaValue);		break;
		case LEFTIDLE:FINDIMG("미탱아이들")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 4, _tank.rc.top - 22, _tank.frameX, 1, _alphaValue);		break;
		case RIGHTRUN:FINDIMG("미탱이동")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 55, _tank.rc.top - 22, _tank.frameX, 0, _alphaValue);		break;
		case LEFTRUN:FINDIMG("미탱이동")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 47, _tank.rc.top - 22, _tank.frameX, 1, _alphaValue);		break;
		case RIGHTATTACK:FINDIMG("미탱공격")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 53, _tank.rc.top - 47, _tank.frameX, 0, _alphaValue);		break;
		case LEFTATTACK:FINDIMG("미탱공격")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 30, _tank.rc.top - 47, _tank.frameX, 1, _alphaValue);		break;
		}
		break;
	case MULTI:
		switch (_tank.state)
		{
		case RIGHTIDLE:FINDIMG("멀탱아이들")->alphaFrameRender(getMemDC(),
			_tank.rc.left-2, _tank.rc.top-10, _tank.frameX, 0, _alphaValue);		break;
		case LEFTIDLE:FINDIMG("멀탱아이들")->alphaFrameRender(getMemDC(),
			_tank.rc.left, _tank.rc.top-10, _tank.frameX, 1, _alphaValue);			break;
		case RIGHTRUN:FINDIMG("멀탱이동")->alphaFrameRender(getMemDC(),
			_tank.rc.left-2, _tank.rc.top-5, _tank.frameX, 0, _alphaValue);			break;
		case LEFTRUN:FINDIMG("멀탱이동")->alphaFrameRender(getMemDC(),
			_tank.rc.left, _tank.rc.top-5, _tank.frameX, 1, _alphaValue);			break;
		case RIGHTATTACK:FINDIMG("멀탱공격")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 3, _tank.rc.top - 32, _tank.frameX, 0, _alphaValue);	break;
		case LEFTATTACK:FINDIMG("멀탱공격")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 2, _tank.rc.top - 32, _tank.frameX, 1, _alphaValue);	break;
		}
		break;
	case SUPER:
		switch (_tank.state)
		{
		case RIGHTIDLE:FINDIMG("슈탱아이들")->alphaFrameRender(getMemDC(),
			_tank.rc.left+3, _tank.rc.top, _tank.frameX, 0, _alphaValue);			break;
		case LEFTIDLE:FINDIMG("슈탱아이들")->alphaFrameRender(getMemDC(),
			_tank.rc.left+3, _tank.rc.top, _tank.frameX, 1, _alphaValue);			break;
		case RIGHTRUN:FINDIMG("슈탱이동")->alphaFrameRender(getMemDC(),
			_tank.rc.left+3, _tank.rc.top, _tank.frameX, 0, _alphaValue);			break;
		case LEFTRUN:FINDIMG("슈탱이동")->alphaFrameRender(getMemDC(),
			_tank.rc.left+3, _tank.rc.top, _tank.frameX, 1, _alphaValue);			break;
		case RIGHTATTACK:FINDIMG("슈탱공격")->alphaFrameRender(getMemDC(),
			_tank.rc.left +3 , _tank.rc.top - 28, _tank.frameX, 0, _alphaValue);	break;
		case LEFTATTACK:FINDIMG("슈탱공격")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 15 , _tank.rc.top - 28, _tank.frameX, 1, _alphaValue);	break;
		}
		break;
	} // 후아..
}