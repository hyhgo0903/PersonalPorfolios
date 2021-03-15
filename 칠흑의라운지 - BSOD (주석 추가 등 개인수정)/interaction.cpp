#include "stdafx.h"
#include "interaction.h"
#include "tile.h"

interaction::interaction()
{
}

interaction::~interaction()
{
}

void interaction::release()
{
}

HRESULT interaction::init()
{
	chanhoInit();	deokhoInit();	hyunjeongInit();
	yoonghoInit();	younghanInit();
	return S_OK;
}

void interaction::update()
{
	chanhoUpdate();	deokhoUpdate();	hyunjeongUpdate();
	yoonghoUpdate();	younghanUpdate();
}

void interaction::render()
{
	chanhoRender();	deokhoRender();	hyunjeongRender();
	yoonghoRender();	younghanRender();
}