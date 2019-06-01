#pragma once
#include "Audio.h"

class NullAudio :public Audio {
public:
	virtual void playSound(int soundID) {};
	virtual void stopSound(int soundID) {};
	virtual void stopAllSounds() {};
	virtual void resumeAllSounds() {};
};