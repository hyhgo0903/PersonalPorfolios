#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(int width, int height)
{ // 바 너비 높이만 입력받고 어차피 setX setY setPoint함수 쓸거니 매개변수 줄였음
	_width = width;
	_height = height;
	_progressBarFront = IMAGEMANAGER->addImage("frontBar", "image/interface/barhpup.bmp", width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage("backBar", "image/interface/barhpback.bmp", width, height, true, RGB(255, 0, 255));

	_rcProgress = RectMake(-_width, -_height, _width, _height); // 처음엔 화면 밖에다 그려준다음 이동시키려고
	if (width == _progressBarBack->getWidth() &&
		height == _progressBarBack->getHeight()) _needToBeResized = false;
	else _needToBeResized = true;
	// 이게 참이면 렌더를 다르게하는데 솔직히 엥간하면 참일거임


	return S_OK;
}

void progressBar::release()
{

}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _width, _height);
}

void progressBar::render()
{
	if (!_needToBeResized) // 크기 조정할 필요가 없다면 원래 그리던 것처럼 그립니다.
	{
		IMAGEMANAGER->render("backBar", getMemDC(),
			_rcProgress.left, _rcProgress.top, 0, 0,
			_width, _height);

		IMAGEMANAGER->render("frontBar", getMemDC(),
			_rcProgress.left, _rcProgress.top, 0, 0,
			_currentHPWidth, _height);
	}
	else
	{ // 크기 조정할 필요가 있다면 투명도 되면서
	// 사이즈 변경도 지원되는 TransparentBlt으로 렌더링합니다.
	// 잡소리 : 애초에 그냥 저걸로 하면 되지않나 생각도 했는데
	// 기능이 많다 -> 느리다고 하신게 마음에 걸려서그만..
		IMAGEMANAGER->resizedRender("backBar", getMemDC(),
			_rcProgress.left, _rcProgress.top, _width, _height);

		IMAGEMANAGER->resizedRender("frontBar", getMemDC(),
			_rcProgress.left, _rcProgress.top, _currentHPWidth, _height);
	}
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{ // 프론트바(현재 체력)의 너비를 조정
	_currentHPWidth = (currentGauge / maxGauge) * _width;
}