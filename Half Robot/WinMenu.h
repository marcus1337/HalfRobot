#pragma once
#include "Button.h"
#include <iostream>
#include "Window.h"
#include "MenuState.h"
#include "Menu.h"
#include "GameSave.h"
#include "IOStuff.h"
#include "Toast.h"
#include "LivesBar.h"
#include "SoundLocator.h"

class WinMenu{
public:
	WinMenu(GameSave _gamesave) : gamesave(_gamesave) {
		alpha = 255;
		addAlpha = false;
	}

	virtual int handleInput(Window& window, SDL_Event& ev) {

		if (ev.type == SDL_QUIT) {
			return -3;
		}

		switch (ev.type) {
		case SDL_MOUSEBUTTONDOWN:
	

			backbtn.clickPress(ev.motion.x, ev.motion.y);
			break;
		case SDL_MOUSEBUTTONUP:

			backbtn.clickRelease(ev.motion.x, ev.motion.y);
			break;

		case SDL_MOUSEMOTION:
			backbtn.hover(ev.motion.x, ev.motion.y);

			break;

		case SDL_WINDOWEVENT:
			if (ev.window.event == SDL_WINDOWEVENT_RESIZED) {
				initLoc(window);
			}
			break;

		}

		if (backbtn.isClicked()) {
			return -99;
		}

		return -100;
	}

	virtual void update(Window& window) {
		SDL_Renderer* r = window.getRenderer();
		SDL_RenderCopy(r, ShapeHandler::background4, NULL, NULL);
		backbtn.render(r);
		backTxt.render(r);

		winTxt.setColor(200, 200, 100, alpha);
		winTxt.reInit2(r, "Congrats, you have beaten the game. \n"
			"In order to celebrate, you wisely choose to eat a pizza."
			, window.getWidth() - 100);
		
		if (addAlpha) {
			alpha++;
			if (alpha == 255)
				addAlpha = false;
		}
		else {
			alpha--;
			if (alpha == 100)
				addAlpha = true;
		}

		winTxt.render(r);
	}

	void initLoc(Window& window) {
		winTxt = Text();
		backTxt = Text();

		int w = window.getWidth();
		int h = window.getHeight();
		SDL_Renderer* r = window.getRenderer();

		int hdown = h - (float)h / 5;
		int wnorm = (float)w / 10;

		SDL_Rect btnrct = { window.midX() - wnorm, hdown, wnorm * 2, wnorm };

		backbtn.setRect(btnrct);
		backTxt.setRect(btnrct);
		backTxt.init("BACK", r, 88);

		SDL_Rect winrct = { 0,0,0,0 };
		winrct.x = w / 2;
		winrct.h = h / 2;
		winTxt.setColor(200, 200, 100, 255);
		winTxt.setX(50);
		winTxt.setY(50);
		winTxt.init2(r, 50, "Congrats, you have beaten the game. \n"
			"In order to celebrate, you wisely choose to eat a pizza."
			, w - 100);
	}

	virtual void enter(Window& window) {
		SoundLocator::getAudio().playSound(MENU2);
		initLoc(window);

	}


private:
	GameSave gamesave;
	Button backbtn;
	Text backTxt;
	Text winTxt;
	int alpha;
	bool addAlpha;

};