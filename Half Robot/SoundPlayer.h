#pragma once
#include "Audio.h"
#include "SDL_mixer.h"
#include <iostream>
#include <thread>
#include "SoundID.h"
#include <vector>
#include <Windows.h>

#define MUS_PATH1 "test\\mountains.flac"
#define MUS_PATH2 "test\\credits.flac"
#define MUS_PATH3 "test\\shyzu.flac"
#define MUS_PATH4 "test\\underwater.flac"
#define MUS_PATH5 "test\\volcano.flac"
#define MUS_PATH6 "test\\castle.flac"
#define MUS_PATH7 "test\\chase.flac"
#define MUS_PATH8 "test\\beach.flac"

#define EFF1_PATH "space\\laser3.mp3"

#define MENU_PATH1 "test\\awesomeness.wav"
#define MENU_PATH2 "test\\tivoli.flac"

class SoundPlayer : public Audio {
public:

	SoundPlayer() {
		using namespace std;
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

		std::string bpath = audiPath();

		pMenu = Mix_LoadMUS(string(bpath).append(MENU_PATH1).c_str());
		pMenu2 = Mix_LoadMUS(string(bpath).append(MENU_PATH2).c_str());

		pMap1 = Mix_LoadMUS(string(bpath).append(MUS_PATH2).c_str());
		pMap2 = Mix_LoadMUS(string(bpath).append(MUS_PATH1).c_str());
		pMap3 = Mix_LoadMUS(string(bpath).append(MUS_PATH3).c_str());
		pMap4 = Mix_LoadMUS(string(bpath).append(MUS_PATH4).c_str());
		pMap5 = Mix_LoadMUS(string(bpath).append(MUS_PATH5).c_str());
		pMap6 = Mix_LoadMUS(string(bpath).append(MUS_PATH6).c_str());
		pMap7 = Mix_LoadMUS(string(bpath).append(MUS_PATH7).c_str());
		pMap8 = Mix_LoadMUS(string(bpath).append(MUS_PATH8).c_str());

		pBull1 = Mix_LoadWAV(string(bpath).append(EFF1_PATH).c_str());
		pBull2 = Mix_LoadWAV(string(bpath).append(EFF1_PATH).c_str());
		pBull3 = Mix_LoadWAV(string(bpath).append(EFF1_PATH).c_str());


		Mix_AllocateChannels(20);
		Mix_VolumeMusic(25);
		stop = false;
		hackHelpMenu = false;
	}

	~SoundPlayer() {

		Mix_FreeMusic(pMenu);
		Mix_FreeMusic(pMenu2);

		Mix_FreeMusic(pMap1);
		Mix_FreeMusic(pMap2);
		Mix_FreeMusic(pMap3);
		Mix_FreeMusic(pMap4);
		Mix_FreeMusic(pMap6);
		Mix_FreeMusic(pMap7);
		Mix_FreeMusic(pMap8);

		Mix_FreeChunk(pBull1);
		Mix_FreeChunk(pBull2);
		Mix_FreeChunk(pBull3);

		Mix_CloseAudio();
	}

	virtual void playSound(int soundID) {

		if (stop)
			return;

		if (hackHelpMenu) {
			hackHelpMenu = false;
			return;
		}

		if (soundID == 93752) {
			hackHelpMenu = true;
			return;
		}
		if (soundID == 93753) {
			hackHelpMenu = false;
			return;
		}

		switch (soundID) {
		case MAP1:
			Mix_PlayMusic(pMap1, 15);
			break;

		case MAP2:
			Mix_PlayMusic(pMap2, 15);
			break;

		case MAP3:
			Mix_PlayMusic(pMap3, 15);
			break;

		case MAP4:
			Mix_PlayMusic(pMap4, 15);
			break;

		case MAP5:
			Mix_PlayMusic(pMap5, 15);
			break;

		case MAP6:
			Mix_PlayMusic(pMap6, 15);
			break;

		case MAP7:
			Mix_PlayMusic(pMap7, 15);
			break;

		case MAP8:
			Mix_PlayMusic(pMap8, 15);
			break;

		case BULL1:
			//if (!Mix_Playing(2))
				Mix_PlayChannel(-1, pBull1, 0);
			break;

		case MENU1:
			Mix_PlayMusic(pMenu, 15);
			break;

		case MENU2:
			Mix_PlayMusic(pMenu2, 5);
			break;

		default:

			break;

		}


	}

	virtual void stopSound(int soundID) {

	}

	virtual void stopAllSounds() {
		stop = true;
		Mix_PauseMusic();

	}

	virtual void resumeAllSounds() {
		stop = false;
		Mix_ResumeMusic();
		//Mix_Resume(-1);
	}

private:

	static std::string audiPath() {
		using namespace std;
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		string::size_type pos = string(buffer).find_last_of("\\/");
		string test = string(buffer).substr(0, pos);
		test += "\\bin\\audio\\";
		return test;
	}

	Mix_Music *pMenu;
	Mix_Music *pMenu2;

	Mix_Music *pMap1;
	Mix_Music *pMap2;
	Mix_Music *pMap3;
	Mix_Music *pMap4;
	Mix_Music *pMap5;
	Mix_Music *pMap6;
	Mix_Music *pMap7;
	Mix_Music *pMap8;

	Mix_Chunk *pBull1;
	Mix_Chunk *pBull2;
	Mix_Chunk *pBull3;

	bool stop;
	bool hackHelpMenu;

};