#include "stdafx.h"
#include "collision.h"

collision::collision()
{
}

collision::~collision()
{
}
void collision::release()
{
}
HRESULT collision::init()
{
	chanhoInit();	deokhoInit();	hyunjungInit();
	yoonghoInit();	younghanInit();
	return S_OK;
}

void collision::update()
{
	chanhoUpdate();	deokhoUpdate();	hyunjungUpdate();
	yoonghoUpdate();	younghanUpdate();
}

void collision::render()
{
	chanhoRender();	deokhoRender();	hyunjungRender();
	yoonghoRender();	younghanRender();
}
