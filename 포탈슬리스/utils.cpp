#include "stdafx.h"
#include "utils.h"

namespace TFIVE_UTIL
{
	float getDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return sqrtf(x * x + y * y);
	}

	// getAngle(시작점의 x, y좌표, 끝점의 x, y좌표)
	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;		
		float angle = -atan2f(y, x);
		return angle;
	}


}