#pragma once

#include <iostream>
#include "Window.h"
#include "ShapeFuncs.h"

class ShapeHandler : ShapeFuncs {
public:

	static std::string rpath;

	static std::string getrpath() {
		using namespace std;
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		string::size_type pos = string(buffer).find_last_of("\\/");
		string test = string(buffer).substr(0, pos);
		test += "\\res\\";
		return test;
	}

	ShapeHandler(SDL_Renderer* _renderer) : ShapeFuncs(_renderer) {
		using namespace std;
		rpath = getrpath();
	}

	void init() {
		using namespace std;

		mouseText = textureFromPath(rpath + "cursor.png");
		button = textureFromPath(rpath + "knapp1.png");
		buttonpress = textureFromPath(rpath + "knapp2.png");

		audioOn = textureFromPath(rpath + "audio1.png");
		audioOff = textureFromPath(rpath + "audio2.png");

		heroStill = textureFromPath(rpath + "unit\\player\\still\\1.png");
		heroJump = textureFromPath(rpath + "unit\\player\\jump\\1.png");
		heroLadder = textureFromPath(rpath + "unit\\player\\ladder\\1.png");

		heroFireStill = textureFromPath(rpath + "unit\\player\\fire\\full\\1.png");
		heroFireJump = textureFromPath(rpath + "unit\\player\\fire\\full\\5.png");
		heroFireLadder = textureFromPath(rpath + "unit\\player\\fire\\full\\6.png");
		heroHurt = textureFromPath(rpath + "unit\\player\\hurt\\1.png");

		for (int i = 1; i <= 3; i++) {
			string str = rpath + "unit\\player\\walking\\" + to_string(i) + ".png";
			heroWalk[i - 1] = textureFromPath(str);
			str = rpath + "unit\\player\\fire\\full\\" + to_string(i+1) + ".png";
			heroFireWalk[i - 1] = textureFromPath(str);
		}

		for (int i = 1; i <= 9; i++) {
			string str = rpath + "unit\\shots\\normal" + to_string(i) + ".png";
			bull1[i - 1] = textureFromPath(str);
		}

		tiles[0] = textureFromPath(rpath + "tiles\\block1.png");
		tiles[1] = textureFromPath(rpath + "tiles\\laddr1.png");
		tiles[2] = textureFromPath(rpath + "tiles\\spik1.png");

		health_bar = textureFromPath(rpath + "health_bar.png");
		health_bar_b = textureFromPath(rpath + "health_bar2.png");

		backbtn = textureFromPath(rpath + "backbtn.png");
		backbtn2 = textureFromPath(rpath + "backbtn2.png");

		sponsorimg = textureFromPath(rpath + "sponsor.png");


		background1 = textureFromPath(rpath + "bakgrund1.png");
		background2 = textureFromPath(rpath + "backg8.png");
		background3 = textureFromPath(rpath + "back88.png");
		background4 = textureFromPath(rpath + "backg225.png");
	}



	static void deleteVariables() {
		SDL_DestroyTexture(mouseText);
		SDL_DestroyTexture(buttonpress);
		SDL_DestroyTexture(button);

		for (int i = 0; i <= 8; i++)
			SDL_DestroyTexture(bull1[i]);

		SDL_DestroyTexture(heroLadder);
		SDL_DestroyTexture(heroJump);
		SDL_DestroyTexture(heroStill);

		for (int i = 0; i <= 2; i++) {
			SDL_DestroyTexture(heroWalk[i]);
			SDL_DestroyTexture(heroFireWalk[i]);
		}
		SDL_DestroyTexture(heroHurt);
		SDL_DestroyTexture(heroFireStill);
		SDL_DestroyTexture(heroFireJump);
		SDL_DestroyTexture(heroFireLadder);

		SDL_DestroyTexture(tiles[0]);
		SDL_DestroyTexture(tiles[1]);
		SDL_DestroyTexture(tiles[2]);
		delete[] tiles;

		SDL_DestroyTexture(health_bar);
		SDL_DestroyTexture(health_bar_b);

		SDL_DestroyTexture(audioOn);
		SDL_DestroyTexture(audioOff);

		SDL_DestroyTexture(backbtn);
		SDL_DestroyTexture(backbtn2);

		SDL_DestroyTexture(background1);
		SDL_DestroyTexture(background2);
		SDL_DestroyTexture(background3);
		SDL_DestroyTexture(background4);
		SDL_DestroyTexture(sponsorimg);

	}

	static SDL_Texture* mouseText; 
	static SDL_Texture* buttonpress; 
	static SDL_Texture* button;

	static SDL_Texture** bull1;

	static SDL_Texture* heroLadder;
	static SDL_Texture* heroJump;
	static SDL_Texture* heroStill;
	static SDL_Texture** heroWalk;
	static SDL_Texture* heroHurt;

	static SDL_Texture* heroFireStill;
	static SDL_Texture** heroFireWalk;
	static SDL_Texture* heroFireJump;
	static SDL_Texture* heroFireLadder;

	static SDL_Texture** tiles;

	static SDL_Texture* health_bar;
	static SDL_Texture* health_bar_b;

	static SDL_Texture* audioOn;
	static SDL_Texture* audioOff;

	static SDL_Texture* backbtn;
	static SDL_Texture* backbtn2;

	static SDL_Texture* background1;
	static SDL_Texture* background2;
	static SDL_Texture* background3;
	static SDL_Texture* background4;
	static SDL_Texture* background5;

	static SDL_Texture* sponsorimg;

private:

};