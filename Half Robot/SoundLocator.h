#pragma once
#include "Audio.h"
#include "NullAudio.h"
#include "SoundID.h"

class SoundLocator {
public:

	static void initialize() {
		service_ = &nullService_;
		active = true;
	}

	static bool isActive() {
		return active;
	}

	static void setActive(bool _active) {
		active = _active;
		if (active) {
			service_->resumeAllSounds();
		}
		else {
			service_->stopAllSounds();
		}

	}

	static Audio& getAudio() { 
		if (active)
			return *service_;
		else
			return nullService_;
	}
	
	static void provide(Audio* service) {
		if (service == nullptr)
			service = &nullService_;
		service_ = service;
	}

private:
	SoundLocator() {};
	static NullAudio nullService_;
	static Audio* service_;
	static bool active;
};