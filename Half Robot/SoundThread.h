#pragma once
/*#include "SoundPlayer.h"
#include "SDL_mixer.h"
#include <iostream>
#include <thread>
#include "Audio.h"

#define MUS_PATH "bin/audio/test/battle.flac"
#define MUS_PATH2 "bin/audio/test/credits.flac"

class SoundThread {
public:

	SoundThread() {

	}

	~SoundThread() {
		t.join();
		Mix_FreeMusic(music);
		Mix_CloseAudio();
	}


	void run() {
		using namespace std;
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
		music = Mix_LoadMUS(MUS_PATH);
		music2 = Mix_LoadMUS(MUS_PATH2);



		t = std::thread(&SoundThread::start, this);
	}

	void loadmusic(int soundID) {

		if (soundID == 1) {
			Mix_PlayMusic(music, -1);

		}
		if (soundID == 2) {

			Mix_PlayMusic(music2, -1);
		}

	}

private:

	void start() {
		using namespace std;

		//music = Mix_LoadMUS(MUS_PATH);
		Mix_PlayMusic(music, -1);

		while (true) {

			Mix_PlayingMusic();
			//cout << "wlololo" << endl;
		}


	}

	Mix_Music *music = NULL;
	Mix_Music *music2 = NULL;

	std::thread t;
	SoundPlayer soundPlayer;
};