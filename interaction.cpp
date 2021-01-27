#include "stdafx.h"
#include "interaction.h"

interaction::interaction()
{
}

interaction::~interaction()
{
}

HRESULT interaction::init()
{
	chanhoInit();
	deokhoInit();
	hyunjeongInit();
	yoonghoInit();
	younghanInit();
	return S_OK;
}

void interaction::release()
{
}

void interaction::update()
{
	chanhoUpdate();
	deokhoUpdate();
	hyunjeongUpdate();
	yoonghoUpdate();
	younghanUpdate();
}

void interaction::render()
{
	chanhoRender();
	deokhoRender();
	hyunjeongRender();
	yoonghoRender();
	younghanRender();
}