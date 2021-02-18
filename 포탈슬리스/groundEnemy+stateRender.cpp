#include "stdafx.h"
#include "groundEnemy.h"

void groundEnemy::stateRender()
{	
	if (_ID == 0 && _left > 0)
	{//_width = 37; _height = 46;
		switch (_state)
		{
		case IDLE:FINDIMG("적1대기")->alphaFrameRender(getMemDC(), _rc.left, _rc.top - 2, _frameX, 1, _alphaValue);	break;
		case WALK:FINDIMG("적1이동")->alphaFrameRender(getMemDC(), _rc.left, _rc.top - 3, _frameX, 1, _alphaValue);	break;
		case ATTACK:FINDIMG("적1공격")->alphaFrameRender(getMemDC(), _rc.left - 49, _rc.top, _frameX, 1, _alphaValue); break;
		}
	}
	else if (_ID == 0 && _left < 1)
	{
		switch (_state)
		{
		case IDLE:FINDIMG("적1대기")->alphaFrameRender(getMemDC(), _rc.left, _rc.top - 2, _frameX, 0, _alphaValue);	break;
		case WALK:FINDIMG("적1이동")->alphaFrameRender(getMemDC(), _rc.left, _rc.top - 3, _frameX, 0, _alphaValue);	break;
		case ATTACK:FINDIMG("적1공격")->alphaFrameRender(getMemDC(), _rc.left - 5, _rc.top, _frameX, 0, _alphaValue); break;
		}
	}
	else if (_ID == 1 && _left > 0)
	{
		//_width = 29; _height = 38;
		switch (_state)
		{
		case IDLE:FINDIMG("적2대기")->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _frameX, 1, _alphaValue);	break;
		case WALK:FINDIMG("적2이동")->alphaFrameRender(getMemDC(), _rc.left-5, _rc.top-4, _frameX, 1, _alphaValue);	break;
		case ATTACK:FINDIMG("적2공격")->alphaFrameRender(getMemDC(), _rc.left-25, _rc.top-3, _frameX, 1, _alphaValue); break;
		}
	}
	else if (_ID == 1 && _left < 1)
	{
		switch (_state)
		{
		case IDLE:FINDIMG("적2대기")->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0, _alphaValue);	break;
		case WALK:FINDIMG("적2이동")->alphaFrameRender(getMemDC(), _rc.left-2, _rc.top-4, _frameX, 0, _alphaValue);	break;
		case ATTACK:FINDIMG("적2공격")->alphaFrameRender(getMemDC(), _rc.left-3, _rc.top-3, _frameX, 0, _alphaValue); break;
		}
	}
}

