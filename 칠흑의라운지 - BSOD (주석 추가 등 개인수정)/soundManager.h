#pragma once
#include "singletonBase.h"
#include <map>
#include <vector>

#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex64_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 20
#define EXTRACHANNELBUFFER 20

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER


class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**>			arrSounds;
	typedef map<string, Sound**>::iterator	arrSoundsIter;

	typedef map<string, Channel**>				arrChannels;
	typedef map<string, Channel**>::iterator	arrChannelIter;

private:
	System*			_system;
	Sound**			_sound;
	Channel**		_channel;

	arrSounds		_mTotalSounds;

	vector<string> _vBgmKey;
	vector<string>::iterator _viBgmKey;

	string _latestAdded;
	float _bgmVolume;
	float _effectVolume;

public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();
	void update();

	//   사운드 추가함수(키 값, 음악파일명, 브금or효과음, 루프할껀지)
	void addSound(string keyName, string soundName, bool bgm, bool loop);

	// 볼륨은 bgm, 사운드 알아서 들어가게했음
	void play(string keyName);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	//호옥시이 몰라서 만들어둠
	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	void setBgmVolume(float volume);
	void setEffectVolume(float volume);
	float getBgmVolume() { return _bgmVolume; }
	float getEffectVolume() { return _effectVolume; }

	string getLatestAdded() { return _latestAdded; }
};

